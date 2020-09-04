//
//  BDModelSectionHeader.m
//  ObjCExample
//
//  Created by 朱元清 on 2020/8/22.
//  Copyright © 2020 bytedance. All rights reserved.
//

#import "BDModelSectionHeader.h"

@implementation BDModelSectionHeader

- (instancetype)initWithSectionName:(NSString *)name desc:(NSString *)desc {
    self = [super init];
    if (self) {
        self.sectionName = name;
        self.sectionDescription = desc;
    }
    return self;
}

@end
