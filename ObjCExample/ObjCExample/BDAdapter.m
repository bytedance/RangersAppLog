//
//  BDAdapter.m
//  BDAutoTracker_Example
//
//  Created by bob on 2019/8/19.
//  Copyright © 2019 ByteDance. All rights reserved.
//

#import "BDAdapter.h"
#import "BDFeedModel.h"
#import <RangersAppLog/BDKeyWindowTracker.h>
#import <RangersAppLog/RangersAppLog.h>
#import <RangersAppLog/BDAutoTrackURLHostItemCN.h>

static NSString *const BDDebugAppID = @"12345678";

@implementation BDAdapter

#pragma mark - start track
+ (void)startAutoTracker {
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        NSNotificationCenter *center = [NSNotificationCenter defaultCenter];
        [center addObserver:self selector:@selector(onABTestSuccess:)
                       name:BDAutoTrackNotificationABTestSuccess
                     object:nil];
        [center addObserver:self selector:@selector(onRegisterSuccess:)
                       name:BDAutoTrackNotificationRegisterSuccess
                     object:nil];
        [center addObserver:self selector:@selector(onActiveSuccess:)
                       name:BDAutoTrackNotificationActiveSuccess
                     object:nil];

        CFTimeInterval current = CFAbsoluteTimeGetCurrent(); // 计算初始化时间
        
        BDAutoTrackConfig *config = [BDAutoTrackConfig configWithAppID:BDDebugAppID];
//        config.appName = @"yq_rangers_applog_test";
        config.showDebugLog = YES;  /* 开启调试Log */
        config.logger = ^(NSString * _Nullable log) {
            NSLog(@"applog -- %@", log);
        };
        
        /* 生产环境打开加密 */
        config.logNeedEncrypt = !NO;
        config.serviceVendor = BDAutoTrackServiceVendorCN;  /* 设置上报服务器域名 */
        
        config.autoTrackEnabled = YES;  // 开启无埋点
        
        /* 配置私有化 */
//        config.serviceVendor = BDAutoTrackServiceVendorPrivate;
//        BDAutoTrackRequestHostBlock block =
//                  ^NSString *(BDAutoTrackServiceVendor vendor, BDAutoTrackRequestURLType requestURLType) {
//                      return @"http://10.10.10.10:8080";
//                   };
//        [BDAutoTrack setRequestHostBlock:block];
        
        [BDAutoTrack startTrackWithConfig:config];
        [BDAutoTrack setAppTouchPoint:@"iOS APP端"];
        [BDAutoTrack setCustomHeaderBlock:^NSDictionary<NSString *,id> * _Nonnull{
            NSInteger level = [[NSUserDefaults standardUserDefaults] integerForKey:@"Demo_GameLevel"];
            return @{@"level":@(level)};
        }];
        [BDAutoTrack setRequestURLBlock:^NSString *(BDAutoTrackServiceVendor vendor, BDAutoTrackRequestURLType requestURLType) {
            return nil;
        }];
        
        [BDAutoTrack setCurrentUserUniqueID:@"123"];

        CFTimeInterval initTimeCost = CFAbsoluteTimeGetCurrent() - current;
        NSLog(@"startAutoTracker.initTimeCost: (%.6f)",initTimeCost);
    });

    // [self showPicker];
    [BDAutoTrack setCustomHeaderBlock:^NSDictionary<NSString *,id> * _Nonnull{
        return @{
            @"level": @(1)
        };
    }];
}

+ (void)trackKeyWindow:(UIWindow *)keyWindow {
    [BDKeyWindowTracker sharedInstance].keyWindow = keyWindow;
}

#pragma mark - eventV3
+ (BOOL)eventV3:(NSString *)event params:(NSDictionary *)param {
    return [BDAutoTrack eventV3:event params:param];
}

#pragma mark - Notification handlers
+ (void)onRegisterSuccess:(NSNotification *)not  {
    NSLog(@"onRegisterSuccess %@",not.userInfo);
}

+ (void)onActiveSuccess:(NSNotification *)not  {
    NSLog(@"onActiveSuccess %@",not.userInfo);
}

+ (void)onABTestSuccess:(NSNotification *)not  {
    NSLog(@"onABTestSuccess %@",not.userInfo);
}

#pragma mark - picker
+ (NSString *)qrParam {
    return @"eQC71-Kr_PleWCN_yG4XhUMp1dgS2qKy1PMHZGIEoNRQno4AUp29Le5P_c6wep39zKNrqKehLfKOXJZErLc6cu5oLWrXN972HJlVPSqzHWqYhN6CHujmWsovCUcnIjD2Nkb8U6dXJI0cDmS2BZUC7A";
}

+ (void)showPicker {
    NSString *URL = [NSString stringWithFormat:@"rangersapplog.byAx6uYt://rangersapplog/picker?time=%f&aid=%@&type=bind_query&qr_param=%@",[NSDate date].timeIntervalSince1970 + 300, BDDebugAppID, [self qrParam]];
    id scene = nil;
    #ifdef __IPHONE_13_0
    if (@available(iOS 13.0, *)) {
        scene = [UIApplication sharedApplication].keyWindow.windowScene;
    }
    #endif
    [[BDAutoTrackSchemeHandler sharedHandler] handleURL:[NSURL URLWithString:URL]
                                                  appID:BDDebugAppID
                                                  scene:scene];
}

+ (void)upload {
    NSString *URL = [NSString stringWithFormat:@"rangersapplog.byAx6uYt://rangersapplog/picker?time=%f&aid=%@&type=sync_query&qr_param=%@",[NSDate date].timeIntervalSince1970 + 300, BDDebugAppID, [self qrParam]];
    id scene = nil;
    #ifdef __IPHONE_13_0
    if (@available(iOS 13.0, *)) {
        scene = [UIApplication sharedApplication].keyWindow.windowScene;
    }
    #endif
    [[BDAutoTrackSchemeHandler sharedHandler] handleURL:[NSURL URLWithString:URL]
                                                  appID:BDDebugAppID
                                                  scene:scene];
 }

+ (void)log {
   NSString *URL = [NSString stringWithFormat:@"rangersapplog.byAx6uYt://rangersapplog/picker?time=%f&aid=%@&type=debug_log&qr_param=%@",[NSDate date].timeIntervalSince1970 + 300, BDDebugAppID, [self qrParam]];
   id scene = nil;
   #ifdef __IPHONE_13_0
   if (@available(iOS 13.0, *)) {
       scene = [UIApplication sharedApplication].keyWindow.windowScene;
   }
   #endif
   [[BDAutoTrackSchemeHandler sharedHandler] handleURL:[NSURL URLWithString:URL]
                                                 appID:BDDebugAppID
                                                 scene:scene];
}

#pragma mark - handle URL
+ (BOOL)handleURL:(NSURL *)URL scene:(id)scene {
    if ([[BDAutoTrackSchemeHandler sharedHandler] handleURL:URL appID:BDDebugAppID scene:scene]) {
        return YES;
    }

    if ([URL.scheme.lowercaseString isEqualToString:@"rangersapplog"]) {
        return YES;
    }

    return NO;
}

#pragma mark - config overlaping window
+ (void)addTestButtonInWindow:(UIWindow *)window {
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(1 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        CGFloat top = window.bounds.size.height - 144;
        CGFloat left = (window.bounds.size.width - 200)/2;
        UIButton *button = [[UIButton alloc] initWithFrame:CGRectMake(left, top, 200, 44)];
        button.backgroundColor = [UIColor blueColor];
        [button setTitle:@"showPicker" forState:(UIControlStateNormal)];
        [button addTarget:self action:@selector(showPicker) forControlEvents:(UIControlEventTouchUpInside)];
        [window addSubview:button];

        top -= 60;
        button = [[UIButton alloc] initWithFrame:CGRectMake(left, top, 200, 44)];
        button.backgroundColor = [UIColor blueColor];
        [button setTitle:@"upload" forState:(UIControlStateNormal)];
        [button addTarget:self action:@selector(upload) forControlEvents:(UIControlEventTouchUpInside)];
        [window addSubview:button];
        
        top -= 60;
        button = [[UIButton alloc] initWithFrame:CGRectMake(left, top, 200, 44)];
        button.backgroundColor = [UIColor blueColor];
        [button setTitle:@"log" forState:(UIControlStateNormal)];
        [button addTarget:self action:@selector(log) forControlEvents:(UIControlEventTouchUpInside)];
        [window addSubview:button];
    });
}

@end


