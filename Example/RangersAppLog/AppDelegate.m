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

@interface AppDelegate ()

@end

@implementation AppDelegate


- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {

    self.window = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
    UINavigationController *nav = [[UINavigationController alloc] initWithRootViewController:[BDDemoViewController new]];
    self.window.rootViewController = nav;
    [self.window makeKeyAndVisible];
    [BDAdapter startAppLog];
    [BDAdapter trackKeyWindow:self.window];

    return YES;
}

- (BOOL)application:(UIApplication *)app openURL:(NSURL *)url options:(NSDictionary<UIApplicationOpenURLOptionsKey, id> *)options {
    if([BDAdapter handleURL:url scene:nil]) {
        return YES;
    }

    /// your handle code

    return NO;
}

@end
