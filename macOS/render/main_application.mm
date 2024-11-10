#include "convex.hpp"
#import "platforms/macos.hpp"
#include "utils.hpp"
#import <AppKit/AppKit.h>
#include <Foundation/Foundation.h>
#include <chrono>
#include <iostream>
#include <vector>

NSWindow *MainApplication::window = nullptr;
NSRect *MainApplication::frame = nullptr;
NSStackView *MainApplication::stackView = nullptr;
std::vector<NSView *> MainApplication::mainViews = {};

void convex::open_app(std::vector<HTMLComponent *> components) {
    stash::log("convex:macOS", "Creating macOS Application Window");
    @autoreleasepool {
        // Initialize the application
        [NSApplication sharedApplication];

        // Create a window with a fixed layout but resizable by the user
        NSWindow *window =
            [[NSWindow alloc] initWithContentRect:NSMakeRect(0, 0, 800, 600)
                                        styleMask:(NSWindowStyleMaskTitled |
                                                   NSWindowStyleMaskClosable |
                                                   NSWindowStyleMaskResizable)
                                          backing:NSBackingStoreBuffered
                                            defer:NO];
        [window setTitle:@"Stash"];
        [window makeKeyAndOrderFront:nil];

        // Create a vertical stack view to hold the labels, aligned to the left
        NSStackView *stackView =
            [[NSStackView alloc] initWithFrame:NSMakeRect(0, 0, 800, 600)];
        stackView.orientation = NSUserInterfaceLayoutOrientationVertical;
        stackView.spacing = 10;                      // Space between labels
        stackView.alignment = NSLayoutAttributeLeft; // Align to the left
        stackView.distribution =
            NSStackViewDistributionFillProportionally; // Fill space
                                                       // proportionally

        NSScrollView *scrollView =
            [[NSScrollView alloc] initWithFrame:NSMakeRect(0, 0, 800, 600)];
        [scrollView setDocumentView:stackView];   // Set the stack view as the
                                                  // scrollable content
        [scrollView setHasVerticalScroller:YES];  // Enable vertical scrolling
        [scrollView setHasHorizontalScroller:NO]; // Disable horizontal
                                                  // scrolling (if desired)
        [scrollView
            setAutoresizingMask:NSViewWidthSizable |
                                NSViewHeightSizable]; // Allow resizing of the
                                                      // scroll view

        // Add the scroll view to the window's content view
        [window.contentView addSubview:scrollView];

        // Set constraints to keep the scroll view aligned to the top-left
        // corner of the window
        [scrollView.topAnchor
            constraintEqualToAnchor:window.contentView.topAnchor]
            .active = YES;
        [scrollView.leadingAnchor
            constraintEqualToAnchor:window.contentView.leadingAnchor]
            .active = YES;
        [scrollView.trailingAnchor
            constraintEqualToAnchor:window.contentView.trailingAnchor]
            .active = YES;
        [scrollView.bottomAnchor
            constraintEqualToAnchor:window.contentView.bottomAnchor]
            .active = YES;

        // Set the stack view's layout anchor to ensure the content sticks to
        // the top
        stackView.translatesAutoresizingMaskIntoConstraints = NO;

        // Add the stack view to the window's content view
        [window.contentView addSubview:stackView];

        // Set constraints to keep the stack view aligned to the top of the
        // window
        [stackView.topAnchor
            constraintEqualToAnchor:window.contentView.topAnchor
                           constant:10]
            .active = YES;
        [stackView.leadingAnchor
            constraintEqualToAnchor:window.contentView.leadingAnchor
                           constant:10]
            .active = YES;

        for (auto component : components) {
            if (TextHTMLComponent *textComponent =
                    dynamic_cast<TextHTMLComponent *>(component)) {
                render_text(*textComponent);
            }
        }

        for (auto view : MainApplication::mainViews) {
            [stackView addView:view inGravity:NSStackViewGravityTop];
        }

        auto now = std::chrono::high_resolution_clock::now();
        auto elapsed = now - started_render;
        std::string elapsed_time =
            std::to_string(
                std::chrono::duration_cast<std::chrono::milliseconds>(elapsed)
                    .count()) +
            "ms";
        stash::log("convex:macOS", "Parsed and rendered in: " + elapsed_time);

        // Run the application loop
        [NSApp run];
    }
}
