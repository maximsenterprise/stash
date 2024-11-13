/*
 app.mm
 As part of the Stash project
 Created by Maxims Enterprise in 2024
 --------------------------------------------------
 Description: Application entry point for macOS
 Copyright (c) 2024 Maxims Enterprise
*/

#include "convex.hpp"
#include "platforms/macos.hpp"
#include "utils.hpp"
#include <AppKit/AppKit.h>
#import <Cocoa/Cocoa.h>
#import <Foundation/Foundation.h>
#include <Foundation/NSObjCRuntime.h>
#include <dispatch/dispatch.h>
#include <iostream>
#include <vector>

@interface ContainerView : NSView
- (BOOL)isFlipped;
@end

@implementation ContainerView
- (BOOL)isFlipped {
    return YES;
}

@end

std::vector<NSView *> MainApplication::mainViews = {};
NSWindow *MainApplication::window = nil;
NSRect *MainApplication::frame = nil;

void convex::open_app(std::vector<HTMLComponent *> components) {
    stash::log("convex", "Opening app");
    @autoreleasepool {
        NSApplication *app = [NSApplication sharedApplication];

        NSRect frame = NSMakeRect(0, 0, 800, 600);
        NSWindow *window =
            [[NSWindow alloc] initWithContentRect:frame
                                        styleMask:(NSWindowStyleMaskTitled |
                                                   NSWindowStyleMaskClosable |
                                                   NSWindowStyleMaskResizable)
                                          backing:NSBackingStoreBuffered
                                            defer:NO];
        [window setTitle:@"Stash"];
        [window makeKeyAndOrderFront:nil];

        MainApplication::window = window;
        MainApplication::frame = &frame;
        ContainerView *documentView =
            [[ContainerView alloc] initWithFrame:frame];
        [documentView setTranslatesAutoresizingMaskIntoConstraints:NO];

        NSStackView *stackView = [[NSStackView alloc] init];
        [stackView setOrientation:NSUserInterfaceLayoutOrientationVertical];
        [stackView setAlignment:NSLayoutAttributeLeading];
        [stackView setSpacing:10];
        [stackView setTranslatesAutoresizingMaskIntoConstraints:NO];
        stackView.edgeInsets = NSEdgeInsetsMake(0, 20, 10, 20);

        [documentView addSubview:stackView];

        NSScrollView *scrollView = [[NSScrollView alloc] initWithFrame:frame];
        [scrollView setDocumentView:documentView];
        [scrollView setHasVerticalScroller:YES];
        [scrollView setHasHorizontalScroller:NO];
        [scrollView
            setAutoresizingMask:(NSViewWidthSizable | NSViewHeightSizable)];

        // NSClipView *clipView = scrollView.contentView;
        // [clipView scrollToPoint:NSMakePoint(0, stackView.frame.size.height -
        //                                            clipView.frame.size.height)];

        for (auto component : components) {
            if (TextHTMLComponent *text =
                    dynamic_cast<TextHTMLComponent *>(component)) {
                render_text(*text);
            }
        }

        for (auto view : MainApplication::mainViews) {
            [stackView addArrangedSubview:view];
            [NSLayoutConstraint activateConstraints:@[
                [view.widthAnchor
                    constraintEqualToAnchor:stackView.widthAnchor],
            ]];
        }

        [window setContentView:scrollView];
        [scrollView
            setAutoresizingMask:NSViewWidthSizable | NSViewHeightSizable];

        [NSLayoutConstraint activateConstraints:@[
            [stackView.heightAnchor
                constraintEqualToAnchor:documentView.heightAnchor],
        ]];

        [NSLayoutConstraint activateConstraints:@[
            [scrollView.widthAnchor
                constraintEqualToAnchor:window.contentView.widthAnchor],
            [scrollView.heightAnchor
                constraintEqualToAnchor:window.contentView.heightAnchor],
        ]];

        [[NSNotificationCenter defaultCenter]
            addObserverForName:NSWindowDidResizeNotification
                        object:window
                         queue:nil
                    usingBlock:^(NSNotification *note) {
                      NSRect new_frame = window.frame;

                      for (NSView *view in stackView.views) {
                          for (NSLayoutConstraint *constraint in view
                                   .constraints) {
                              if (constraint.firstAttribute ==
                                  NSLayoutAttributeWidth) {
                                  [view removeConstraint:constraint];
                              }
                          }
                          [view.widthAnchor
                              constraintEqualToConstant:new_frame.size.width]
                              .active = YES;
                      }
                    }];

        auto now = std::chrono::high_resolution_clock::now();
        auto elapsed = now - started_render;
        std::string elapsed_time =
            std::to_string(
                std::chrono::duration_cast<std::chrono::milliseconds>(elapsed)
                    .count()) +
            "ms";
        stash::log("convex:macOS", "Parsed and rendered in: " + elapsed_time);

        [app run];

        return;
    }
}
