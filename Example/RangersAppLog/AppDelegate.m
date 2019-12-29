//
//  AppDelegate.m
//  RangersAppLog
//
//  Created by bob on 2019/9/9.
//  Copyright © 2019 Bytedance. All rights reserved.
//

#import "AppDelegate.h"
#import "BDDemoViewController.h"
#import "BDAdapter.h"
#import "BackgroundTask.h"
#import "LocationTracker.h"
#import "BackgroundDownload.h"
#import "LocalPush.h"

#import <RangersAppLog/RangersAppLogCore.h>

@interface AppDelegate ()

@end

@implementation AppDelegate

- (BOOL)application:(UIApplication *)application willFinishLaunchingWithOptions:(NSDictionary<UIApplicationLaunchOptionsKey,id> *)launchOptions {
    [BDAdapter trackCallback:NSStringFromSelector(_cmd) state:application.applicationState];
    return YES;
}

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    [BDAdapter trackCallback:NSStringFromSelector(_cmd) state:application.applicationState];
    [application setMinimumBackgroundFetchInterval:UIApplicationBackgroundFetchIntervalMinimum];
    [[LocalPush sharedInstance] registerUserNotification];
    application.applicationIconBadgeNumber = 0;

    self.window = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
    UINavigationController *nav = [[UINavigationController alloc] initWithRootViewController:[BDDemoViewController new]];
    self.window.rootViewController = nav;
    [self.window makeKeyAndVisible];

    
    if ([BackgroundTask backgroundAbility] && [LocationTracker checkLocationAbility]) {
        dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(3 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
            [[LocationTracker sharedInstance] requestAuthorization];
        });
    }

    return YES;
}

- (BOOL)application:(UIApplication *)application
            openURL:(NSURL *)url
            options:(NSDictionary<UIApplicationOpenURLOptionsKey, id> *)options {

    [BDAdapter trackCallback:NSStringFromSelector(_cmd) state:application.applicationState];
    
    if ([[BDAutoTrackSchemeHandler sharedHandler] handleURL:url appID:@"159486" scene:nil]) {
        return YES;
    }

    return NO;
}

- (void)applicationDidBecomeActive:(UIApplication *)application {
    [BDAdapter trackCallback:NSStringFromSelector(_cmd) state:application.applicationState];
}

- (void)applicationWillResignActive:(UIApplication *)application {
    [BDAdapter trackCallback:NSStringFromSelector(_cmd) state:application.applicationState];
}

- (void)applicationWillEnterForeground:(UIApplication *)application {
    [BDAdapter trackCallback:NSStringFromSelector(_cmd) state:application.applicationState];
}

- (void)applicationDidEnterBackground:(UIApplication *)application {
    [BDAdapter trackCallback:NSStringFromSelector(_cmd) state:application.applicationState];
}

- (void)applicationWillTerminate:(UIApplication *)application {
    [BDAdapter trackCallback:NSStringFromSelector(_cmd) state:application.applicationState];
}

#pragma mark - background fetch
/// background fetch 30s
- (void)application:(UIApplication *)application performFetchWithCompletionHandler:(void (^)(UIBackgroundFetchResult))completionHandler {
    [BDAdapter trackCallback:NSStringFromSelector(_cmd) state:application.applicationState];

    NSURLSessionConfiguration *sessionConfiguration = [NSURLSessionConfiguration defaultSessionConfiguration];
    NSURLSession *session = [NSURLSession sessionWithConfiguration:sessionConfiguration];

    NSURL *url = [[NSURL alloc] initWithString:@"https://www.baidu.com"];
    NSURLSessionDataTask *task = [session dataTaskWithURL:url
                                        completionHandler:^(NSData *data, NSURLResponse *response, NSError *error) {
        completionHandler(UIBackgroundFetchResultNewData);
    }];

    // 开始任务
    [task resume];
}

#pragma mark - backgroundDonwload

- (void)application:(UIApplication *)application handleEventsForBackgroundURLSession:(NSString *)identifier completionHandler:(void (^)(void))completionHandler {
    [BDAdapter trackCallback:NSStringFromSelector(_cmd) state:application.applicationState];
    [[BackgroundDownload sharedInstance] addBackgroundHandler:completionHandler forSession:identifier];
}

#pragma mark - 远程通知

- (void)set {

    [[UIApplication sharedApplication] registerForRemoteNotifications];
}

- (void)application:(UIApplication *)application didReceiveRemoteNotification:(NSDictionary *)userInfo fetchCompletionHandler:(void (^)(UIBackgroundFetchResult result))completionHandler {
    [BDAdapter trackCallback:NSStringFromSelector(_cmd) state:application.applicationState];
    completionHandler(UIBackgroundFetchResultNewData);
}

@end
