//
//  BDConfigViewModel.m
//  ObjCExample
//
//  Created by 朱元清 on 2020/8/25.
//  Copyright © 2020 bytedance. All rights reserved.
//

#import "BDConfigViewModel.h"

@implementation BDConfigViewModel

- (instancetype)initWithConfigKey:(NSString *)configKey value:(NSString *)value {
    self = [super init];
    if (self) {
        self.configKey = configKey;
        self.configValue = value;
    }
    return self;
}

@end
