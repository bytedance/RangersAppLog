//
//  BDColors.m
//  ObjCExample
//
//  Created by 朱元清 on 2020/8/24.
//  Copyright © 2020 bytedance. All rights reserved.
//

#import "BDColors.h"

@implementation BDColors

+ (instancetype)sharedInstance {
    static BDColors *shared;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        shared = [self new];
    });
    return shared;
}

#pragma mark - colors
- (UIColor *)lightGreen {
    return [UIColor colorWithRed:100.0/255 green:155.0/255 blue:100.0/255 alpha:1.0];
}

- (UIColor *)lightRed {
    return [UIColor colorWithRed:155.0/255 green:100.0/255 blue:100.0/255 alpha:1.0];
}

- (UIColor *)lightBlue {
    return [UIColor colorWithRed:100.0/255 green:100.0/255 blue:155.0/255 alpha:1.0];
}

@end
