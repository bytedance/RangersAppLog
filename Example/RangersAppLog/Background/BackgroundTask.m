//
//  BackgroundTask.m
//  RangersAppLog
//
//  Created by bob on 2019/11/6.
//  Copyright © 2019 Bytedance. All rights reserved.
//

#import "BackgroundTask.h"
#import <UIKit/UIKit.h>

#define BDWeakSelf __weak typeof(self) wself = self
#define BDStrongSelf __strong typeof(wself) self = wself


@interface BackgroundTask ()

@property (assign) UIBackgroundTaskIdentifier taskID;

@end

@implementation BackgroundTask

- (instancetype)init {
    self = [super init];
    if (self) {
        self.taskID = UIBackgroundTaskInvalid;
    }

    return self;
}

- (void)beginBackgroundTask {
    if (self.taskID != UIBackgroundTaskInvalid) {
        return;
    }
    BDWeakSelf;
    self.taskID = [[UIApplication sharedApplication] beginBackgroundTaskWithExpirationHandler:^{
        BDStrongSelf;
        if (self.taskID != UIBackgroundTaskInvalid) {
            return;
        }
        [[UIApplication sharedApplication] endBackgroundTask:self.taskID];
        self.taskID = UIBackgroundTaskInvalid;
    }];
}

- (void)endBackgroundTask {
    if (self.taskID != UIBackgroundTaskInvalid) {
        return;
    }
    [[UIApplication sharedApplication] endBackgroundTask:self.taskID];
    self.taskID = UIBackgroundTaskInvalid;
}

+ (BOOL)backgroundAbility {
    UIBackgroundRefreshStatus status = [UIApplication sharedApplication].backgroundRefreshStatus;
    return status == UIBackgroundRefreshStatusAvailable;
}

@end
