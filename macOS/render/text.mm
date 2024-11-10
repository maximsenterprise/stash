/*
 text.mm
 As part of the Stash project
 Created by Maxims Enterprise in 2024
 --------------------------------------------------
 Description: Text rendering
 Copyright (c) 2024 Maxims Enterprise
*/

#import "convex.hpp"
#include "platforms/macos.hpp"
#import <AppKit/AppKit.h>
#import <Foundation/Foundation.h>
#include <_wchar.h>
#include <iostream>

namespace convex {
void render_text(TextHTMLComponent component) {
    NSTextField *label1 =
        [[NSTextField alloc] initWithFrame:NSMakeRect(0, 0, 280, 30)];
    [label1 setStringValue:stdToNSString(component.text)];
    NSFont *font = [NSFont fontWithName:stdToNSString(component.font)
                                   size:component.size];
    if (component.bold) {
        font = [NSFontManager.sharedFontManager convertFont:font
                                                toHaveTrait:NSFontBoldTrait];
    }
    [label1 setFont:font];
    [label1 setEditable:NO];
    [label1 setBezeled:NO];
    [label1 setBackgroundColor:[NSColor clearColor]];
    MainApplication::mainViews.push_back(label1);
}

} // namespace convex
