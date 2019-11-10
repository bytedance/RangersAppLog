//
//  BDFeedModel.m
//  RangersAppLog
//
//  Created by bob on 2019/9/9.
//  Copyright © 2019 Bytedance. All rights reserved.
//

#import "BDFeedModel.h"

@implementation BDFeedModel

+ (instancetype)modelWithIndex:(NSInteger)index
                        method:(NSString *)method
                         state:(NSInteger)state {
    BDFeedModel *model = [self new];
    model.eventIndex = index;
    model.methodName = method;
    model.state = state;

    return model;
}

@end
