//
//  BDAdapter.m
//  RangersAppLog
//
//  Created by bob on 2019/9/9.
//  Copyright © 2019 Bytedance. All rights reserved.
//

#import "BDAdapter.h"
#import <RangersAppLog/RangersAppLogUITrack.h>
#import <RangersAppLog/BDUIEventPicker.h>

static NSString * const TestAPPID = @"159486";

@interface BDAdapter ()


@property (nonatomic, strong) BDAutoTrack *track;

@end

@implementation BDAdapter

- (instancetype)init {
    self = [super init];
    if (self) {
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
    }

    return self;
}

+ (instancetype)sharedInstance {
    static BDAdapter *sharedInstance = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        sharedInstance = [self new];
    });

    return sharedInstance;
}

+ (void)startAppLog {
    [BDAdapter sharedInstance];
    BDAutoTrackConfig *config = [BDAutoTrackConfig new];
    config.appID = TestAPPID;
    config.channel = @"App Store";
    config.appName = @"dp_tob_sdk_test2";

    /// show debug log
    config.showDebugLog = YES;
    config.logNeedEncrypt = NO;
    config.logger = ^(NSString * _Nullable log) {
        NSLog(@"%@",log);
    };

    BDAutoTrack *track = [BDAutoTrack trackWithConfig:config];
    /// change to your UserUniqueID if now is loged in
    NSString *uniqueID = @"12345";
    [track setCurrentUserUniqueID:uniqueID];
    [track startTrack];

    [BDAdapter sharedInstance].track = track;
}

+ (id)ABTestValue {
    /// change to your key
    NSString *key = @"experiment-no2";
    return [[BDAdapter sharedInstance].track ABTestConfigValueForKey:key defaultValue:nil];
}

+ (void)logout {
    [[BDAdapter sharedInstance].track clearUserUniqueID];
}

+ (void)login {
    /// change to your UserUniqueID
    NSString *uniqueID = @"12345";
    [[BDAdapter sharedInstance].track setCurrentUserUniqueID:uniqueID];
}

+ (void)eventV3:(NSString *)event params:(NSDictionary *)params {

    [[BDAdapter sharedInstance].track eventV3:event params:params];
}

+ (void)trackKeyWindow:(UIWindow *)keyWindow {
    [BDKeyWindowTracker sharedInstance].keyWindow = keyWindow;
}

+ (BOOL)handleURL:(NSURL *)URL scene:(id)scene {
    if ([[BDAutoTrackSchemeHandler sharedHandler] handleURL:URL appID:TestAPPID scene:scene]) {
        return YES;
    }

    return NO;
}

+ (void)showPicker {
    #if 0
        NSURL *URL = [NSURL URLWithString:@"rangersapplog.xxx://rangersapplog/picker?aid=159486"];
        id scene = nil;
        #ifdef __IPHONE_13_0
        if (@available(iOS 13.0, *)) {
            scene = [UIApplication sharedApplication].keyWindow.windowScene;
        }
        #endif
        [[BDAutoTrackSchemeHandler sharedHandler] handleURL:URL appID:TestAPPID scene:scene];
    #else
        BDUIEventPicker *picker = [BDUIEventPicker pickerWithAppID:TestAPPID];
        [picker showPicker];
//        #ifdef __IPHONE_13_0
//            if (@available(iOS 13.0, *)) {
//                dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(1 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
//                    id scene = nil;
//                    scene = [UIApplication sharedApplication].keyWindow.windowScene;
//                    picker.exposedWrapper.windowScene = scene;
//                    picker.exposedPickerButton.window.windowScene = scene;
//                });
//            }
//        #endif
    #endif
}

#pragma mark - Notification

- (void)onRegisterSuccess:(NSNotification *)not  {
    NSLog(@"onRegisterSuccess %@",not.userInfo);
}

- (void)onActiveSuccess:(NSNotification *)not  {
    NSLog(@"onActiveSuccess %@",not.userInfo);
}

- (void)onABTestSuccess:(NSNotification *)not  {
    NSLog(@"onABTestSuccess %@",not.userInfo);
}

@end
