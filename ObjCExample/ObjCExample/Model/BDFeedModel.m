//
//  BDFeedModel.m
//  BDAutoTracker_Example
//
//  Created by bob on 2019/4/17.
//  Copyright © 2019 ByteDance. All rights reserved.
//

#import "BDFeedModel.h"

@implementation BDFeedModel

- (instancetype)init {
    self = [super init];
    if (self) {
        self.cellType = 0;
    }
    
    return self;
}

- (instancetype)initWithTitle:(NSString *)title actionBlock:(dispatch_block_t)actionBlock {
    self = [self init];
    if (self) {
        self.title = title;
        self.actionBlock = actionBlock;
    }
    return self;
}

@end
