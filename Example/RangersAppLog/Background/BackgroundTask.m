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

- (void)dealloc {
    [[NSNotificationCenter defaultCenter] removeObserver:self];
}

- (void)onDidEnterBackground {
    if (!self.enabled) {
        return;
    }
    self.enabled = NO;
    [self beginBackgroundTask];
    BDWeakSelf;
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(10 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        BDStrongSelf;
        [self endBackgroundTask];
    });
}

- (instancetype)init {
    self = [super init];
    if (self) {
        self.taskID = UIBackgroundTaskInvalid;
        [[NSNotificationCenter defaultCenter] addObserver:self
                                                 selector:@selector(onDidEnterBackground)
                                                     name:UIApplicationDidEnterBackgroundNotification
                                                   object:nil];
    }

    return self;
}

+ (instancetype)sharedInstance {
    static BackgroundTask *_sharedInstance = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        _sharedInstance = [self new];
    });

    return _sharedInstance;
}

- (void)beginBackgroundTask {
    if (self.taskID != UIBackgroundTaskInvalid) {
        return;
    }
    BDWeakSelf;
    self.taskID = [[UIApplication sharedApplication] beginBackgroundTaskWithExpirationHandler:^{
        dispatch_async(dispatch_get_main_queue(), ^{
            BDStrongSelf;
            [self endBackgroundTask];
        });
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
