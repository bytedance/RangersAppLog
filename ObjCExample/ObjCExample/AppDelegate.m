//
//  AppDelegate.m
//  ObjCExample
//
//  Created by 朱元清 on 2020/8/21.
//  Copyright © 2020 bytedance. All rights reserved.
//

#import "AppDelegate.h"
#import "BDAdapter.h"
#import "BDTestIntroducerViewController.h"
#import <mach/mach.h>


/// 只输出Log，不会抑制异常继续抛出
void globalNSExceptionHandler(NSException *exception) {
    NSLog(@"\n名字：%@",exception.name);
    NSLog(@"\n原因：%@",exception.reason);
    NSLog(@"\n用户信息：%@",exception.userInfo);
    NSLog(@"\n栈内存地址：%@",exception.callStackReturnAddresses);
//    NSLog(@"栈描述：%@",exception.callStackSymbols);
}

@interface AppDelegate ()

@end

@implementation AppDelegate

#pragma mark - leftcycle
- (BOOL)application:(UIApplication *)application willFinishLaunchingWithOptions:(NSDictionary<UIApplicationLaunchOptionsKey,id> *)launchOptions {
    NSLog(@"%@ %zd",NSStringFromSelector(_cmd),application.applicationState);
    return YES;
}

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    // Override point for customization after application launch.
    NSSetUncaughtExceptionHandler(&globalNSExceptionHandler);
    [BDAdapter startAutoTracker];
    
    self.window = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
    BDTestIntroducerViewController *intro = [[BDTestIntroducerViewController alloc] init];
    UINavigationController *nav = [[UINavigationController alloc] initWithRootViewController:intro];
    self.window.rootViewController = nav;
    [self.window makeKeyAndVisible];
    
    [BDAdapter trackKeyWindow:self.window];
    return YES;
}

- (void)applicationDidBecomeActive:(UIApplication *)application {
    NSLog(@"%@ %zd", NSStringFromSelector(_cmd), [UIApplication sharedApplication].applicationState);
}

- (void)applicationWillResignActive:(UIApplication *)application {
    NSLog(@"%@ %zd", NSStringFromSelector(_cmd), [UIApplication sharedApplication].applicationState);
}

- (void)applicationWillEnterForeground:(UIApplication *)application {
    NSLog(@"%@ %zd", NSStringFromSelector(_cmd), [UIApplication sharedApplication].applicationState);
}

- (void)applicationDidEnterBackground:(UIApplication *)application {
    NSLog(@"%@ %zd", NSStringFromSelector(_cmd), [UIApplication sharedApplication].applicationState);
}

- (BOOL)application:(UIApplication *)app openURL:(NSURL *)url options:(NSDictionary<UIApplicationOpenURLOptionsKey, id> *)options {
//    if([BDAdapter handleURL:url scene:nil]) {
//        return YES;
//    }

    /// your handle code

    return NO;
}


#ifdef __IPHONE_13_0
//- (UISceneConfiguration *)application:(UIApplication *)application configurationForConnectingSceneSession:(UISceneSession *)connectingSceneSession options:(UISceneConnectionOptions *)options API_AVAILABLE(ios(13.0)) {
//    UISceneConfiguration *config = [[UISceneConfiguration alloc] initWithName:@"Default Configuration" sessionRole:connectingSceneSession.role];
//    config.delegateClass = [BDSceneDelegate class];
//    return config;
//}
#endif

@end
