/*
 text_rendering.mm
 As part of the Stash project
 Created by Maxims Enterprise in 2024
 --------------------------------------------------
 Description: Text rendering capabilities
 Copyright (c) 2024 Maxims Enterprise
*/

#include "convex.hpp"
#include "platforms/macos.hpp"
#import <AppKit/AppKit.h>
#import <Cocoa/Cocoa.h>
#import <Foundation/Foundation.h>
#include <Foundation/NSObjCRuntime.h>
#include <objc/NSObject.h>
#include <objc/objc.h>

@interface AnchorHandler : NSObject
@end

@implementation AnchorHandler

- (void)buttonClicked:(id)sender {
    NSButton *button = (NSButton *)sender;
    NSLog(@"Button clicked: %@", button.title);
}

@end

@interface AnchorButton : NSButton
@end

@implementation AnchorButton

- (void)updateTrackingAreas {
    [super updateTrackingAreas];

    for (NSTrackingArea *area in self.trackingAreas) {
        [self removeTrackingArea:area];
    }

    NSTrackingArea *trackingArea = [[NSTrackingArea alloc]
        initWithRect:self.bounds
             options:NSTrackingMouseEnteredAndExited | NSTrackingCursorUpdate |
                     NSTrackingActiveInKeyWindow
               owner:self
            userInfo:nil];
    [self addTrackingArea:trackingArea];
    [self setTarget:[AnchorHandler new]];
    [self setAction:@selector(buttonClicked:)];
}

- (void)mouseEntered:(NSEvent *)event {
    [super mouseEntered:event];
    [[NSCursor pointingHandCursor] set];
}

- (void)mouseExited:(NSEvent *)event {
    [super mouseExited:event];
    [[NSCursor arrowCursor] set];
}

@end

@interface StashTextField : NSTextField
@end

@implementation StashTextField
- (void)updateTrackingAreas {
    [super updateTrackingAreas];

    for (NSTrackingArea *area in self.trackingAreas) {
        [self removeTrackingArea:area];
    }

    NSTrackingArea *trackingArea = [[NSTrackingArea alloc]
        initWithRect:self.bounds
             options:NSTrackingMouseEnteredAndExited | NSTrackingCursorUpdate |
                     NSTrackingActiveInKeyWindow
               owner:self
            userInfo:nil];
    [self addTrackingArea:trackingArea];
    [self setTarget:[AnchorHandler new]];
    [self setAction:@selector(buttonClicked:)];
}

- (void)mouseEntered:(NSEvent *)event {
    [super mouseEntered:event];
    [[NSCursor IBeamCursor] set];
}

- (void)mouseExited:(NSEvent *)event {
    [super mouseExited:event];
    [[NSCursor arrowCursor] set];
}
@end

namespace convex {

void render_anchor(AnchorHTMLComponent component) {
    // Create the button
    AnchorButton *button = [[AnchorButton alloc]
        initWithFrame:NSMakeRect(0, 0, MainApplication::frame->size.width,
                                 600)];
    [button setBordered:NO];
    button.title = [NSString stringWithUTF8String:component.text.c_str()];
    button.layer.backgroundColor = [NSColor clearColor].CGColor;
    button.translatesAutoresizingMaskIntoConstraints = NO;
    button.lineBreakMode = NSLineBreakByWordWrapping;
    button.usesSingleLineMode = NO;

    button.bezelStyle = NSBezelStyleInline;

    NSFont *font = [NSFont
        fontWithName:[NSString stringWithUTF8String:component.font.c_str()]
                size:component.size];
    if (component.bold) {
        font = [NSFontManager.sharedFontManager convertFont:font
                                                toHaveTrait:NSFontBoldTrait];
    }
    button.font = font;
    button.alignment = NSTextAlignmentLeft;

    [button sizeToFit];

    [button.widthAnchor
        constraintEqualToConstant:MainApplication::frame->size.width]
        .active = YES;

    MainApplication::mainViews.push_back(button);
}

void render_text(TextHTMLComponent component) {
    // Create the NSTextField
    StashTextField *textField = [[StashTextField alloc]
        initWithFrame:NSMakeRect(0, 0, MainApplication::frame->size.width,
                                 600)];

    // Set the text for the NSTextField
    textField.stringValue =
        [NSString stringWithUTF8String:component.text.c_str()];
    textField.editable = NO;
    textField.bezeled = NO;
    textField.drawsBackground = NO;
    textField.selectable = YES;
    textField.lineBreakMode = NSLineBreakByWordWrapping;
    textField.usesSingleLineMode = NO;
    textField.translatesAutoresizingMaskIntoConstraints = NO;

    // Set the font
    NSFont *font = [NSFont
        fontWithName:[NSString stringWithUTF8String:component.font.c_str()]
                size:component.size];
    if (component.bold) {
        font = [NSFontManager.sharedFontManager convertFont:font
                                                toHaveTrait:NSFontBoldTrait];
    }
    textField.font = font;
    textField.alignment = NSTextAlignmentLeft;

    NSView *margins = nullptr;

    if (component.type == HTMLType::H1 || component.type == HTMLType::H2 ||
        component.type == HTMLType::H3 || component.type == HTMLType::H4 ||
        component.type == HTMLType::H5 || component.type == HTMLType::H6) {
        margins = [[NSView alloc] initWithFrame:NSMakeRect(0, 0, 0, 10)];
        [margins setTranslatesAutoresizingMaskIntoConstraints:NO];
    }

    // Size the text field to fit its content
    [textField sizeToFit];

    // // Add Auto Layout constraint to ensure width matches the window's width
    [textField.widthAnchor
        constraintEqualToConstant:MainApplication::frame->size.width]
        .active = YES;

    // Add the text field to your views
    MainApplication::mainViews.push_back(textField);

    if (margins) {
        MainApplication::mainViews.push_back(margins);
    }
}
} // namespace convex
