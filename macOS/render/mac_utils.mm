/*
 utils.mm
 As part of the Stash project
 Created by Maxims Enterprise in 2024
 --------------------------------------------------
 Description: Utilities for rendering
 Copyright (c) 2024 Maxims Enterprise
*/

#include "convex.hpp"
#include "platforms/macos.hpp"
#import <Foundation/Foundation.h>
#include <string>

NSString *stdToNSString(std::string str) {
    return [NSString stringWithUTF8String:str.c_str()];
}
