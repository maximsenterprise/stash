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

namespace convex {

void render_text(TextHTMLComponent component) {
    // Create the NSTextField
    NSTextField *textField = [[NSTextField alloc]
        initWithFrame:NSMakeRect(0, 0, MainApplication::frame->size.width,
                                 600)];

    // Set the text for the NSTextField
    textField.stringValue =
        [NSString stringWithUTF8String:component.text.c_str()];
    textField.editable = NO;
    textField.bezeled = NO;
    textField.drawsBackground = NO;
    textField.selectable = NO;
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

    // Size the text field to fit its content
    [textField sizeToFit];

    // // Add Auto Layout constraint to ensure width matches the window's width
    [textField.widthAnchor
        constraintEqualToConstant:MainApplication::frame->size.width]
        .active = YES;

    // Add the text field to your views
    MainApplication::mainViews.push_back(textField);
}
} // namespace convex
