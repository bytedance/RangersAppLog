//
//  LocalPush.m
//  RangersAppLog
//
//  Created by bob on 2019/11/8.
//  Copyright © 2019 Bytedance. All rights reserved.
//

#import "LocalPush.h"
#import <UserNotifications/UserNotifications.h>
#import <UIKit/UIKit.h>
#import "BDAdapter.h"

@interface LocalPush ()<UNUserNotificationCenterDelegate>

@end

@implementation LocalPush

- (void)dealloc {
    [[NSNotificationCenter defaultCenter] removeObserver:self];
}

- (void)onDidEnterBackground {
    if (!self.enabled) {
        return;
    }

    [self scheduleLocalNotification];
}

- (instancetype)init {
    self = [super init];
    if (self) {
        [[NSNotificationCenter defaultCenter] addObserver:self
                                                 selector:@selector(onDidEnterBackground)
                                                     name:UIApplicationDidEnterBackgroundNotification
                                                   object:nil];
    }

    return self;
}

+ (instancetype)sharedInstance {
    static LocalPush *_sharedInstance = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        _sharedInstance = [self new];
    });

    return _sharedInstance;
}

- (void)registerUserNotification {
    [UNUserNotificationCenter currentNotificationCenter].delegate = self;
    UNAuthorizationOptions opt = UNAuthorizationOptionBadge | UNAuthorizationOptionSound | UNAuthorizationOptionAlert ;
    [[UNUserNotificationCenter currentNotificationCenter] requestAuthorizationWithOptions:opt
                                                                        completionHandler:^(BOOL granted, NSError* error) {
    }];
}

- (void)scheduleLocalNotification {
    UNMutableNotificationContent *content = [UNMutableNotificationContent new];
    content.title = @"title";
    content.subtitle = @"subtitle";
    content.body = @"body";
    content.badge = @1;
    content.launchImageName = @"test_song.jpg";
    content.sound = [UNNotificationSound defaultSound];;

    UNTimeIntervalNotificationTrigger *trigger = [UNTimeIntervalNotificationTrigger triggerWithTimeInterval:5 repeats:NO];

    UNNotificationRequest *request = [UNNotificationRequest requestWithIdentifier:@"scheduleLocalNotification"
                                                                          content:content
                                                                          trigger:trigger];

    [[UNUserNotificationCenter currentNotificationCenter] removeAllDeliveredNotifications];
    [[UNUserNotificationCenter currentNotificationCenter] addNotificationRequest:request
                                                           withCompletionHandler:^(NSError * error) {
    }];
}

#pragma mark - UNUserNotificationCenterDelegate

/// if the application is in the foreground
- (void)userNotificationCenter:(UNUserNotificationCenter *)center
       willPresentNotification:(UNNotification *)notification
         withCompletionHandler:(void (^)(UNNotificationPresentationOptions options))completionHandler {
    [BDAdapter trackCallback:NSStringFromSelector(_cmd) state:[UIApplication sharedApplication].applicationState];
    completionHandler(UNNotificationPresentationOptionAlert);
}

- (void)userNotificationCenter:(UNUserNotificationCenter *)center
didReceiveNotificationResponse:(UNNotificationResponse *)response
         withCompletionHandler:(void(^)(void))completionHandler {
    [BDAdapter trackCallback:NSStringFromSelector(_cmd) state:[UIApplication sharedApplication].applicationState];
    completionHandler();
}

- (void)userNotificationCenter:(UNUserNotificationCenter *)center
   openSettingsForNotification:(UNNotification *)notification  {
    [BDAdapter trackCallback:NSStringFromSelector(_cmd) state:[UIApplication sharedApplication].applicationState];
}

@end
