#include "convex.hpp"
#import <AppKit/AppKit.h>
#include <Foundation/Foundation.h>

void convex::open_app() {
    @autoreleasepool {
        [NSApplication sharedApplication];

        NSRect frame = NSMakeRect(0, 0, 800, 600);
        NSWindow* window = [[NSWindow alloc] initWithContentRect:frame
                                                        styleMask:(NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskResizable)
                                                          backing:NSBackingStoreBuffered
                                                            defer:NO];
        [window setTitle:@"Stash Rendering Motor"];
        [window makeKeyAndOrderFront:nil];

        [NSApp run];
    }
}
