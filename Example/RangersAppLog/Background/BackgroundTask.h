//
//  BackgroundTask.h
//  RangersAppLog
//
//  Created by bob on 2019/11/6.
//  Copyright © 2019 Bytedance. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface BackgroundTask : NSObject

- (void)beginBackgroundTask;
- (void)endBackgroundTask;

+ (BOOL)backgroundAbility;

@end

NS_ASSUME_NONNULL_END
