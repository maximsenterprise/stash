/*
 (Objective-C++)

 macos.hmm
 As part of the Stash project
 Created by Maxims Enterprise in 2024
 --------------------------------------------------
 Description: MacOS Objective-C++ header
 Copyright (c) 2024 Maxims Enterprise
*/

#ifndef MACOS_HMM
#define MACOS_HMM

#include <string>
#include <vector>
#ifdef __cplusplus
extern "C" {
#endif
#import <AppKit/AppKit.h>
#import <Foundation/Foundation.h>
#ifdef __cplusplus
}
#endif

class MainApplication {
  public:
    static NSWindow *window;
    static NSRect *frame;
    static NSStackView *stackView;
    static std::vector<NSView *> mainViews;
};

NSString *stdToNSString(std::string str);

#endif
