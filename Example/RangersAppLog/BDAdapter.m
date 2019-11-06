//
//  BDAdapter.m
//  RangersAppLog
//
//  Created by bob on 2019/9/9.
//  Copyright © 2019 Bytedance. All rights reserved.
//

#import "BDAdapter.h"
#import <RangersAppLog/RangersAppLogCore.h>

static NSString * const TestAPPID = @"159486";

@interface BDAdapter ()


@property (nonatomic, strong) BDAutoTrack *track;

@end

@implementation BDAdapter

- (instancetype)init {
    self = [super init];
    if (self) {
        NSNotificationCenter *center = [NSNotificationCenter defaultCenter];

        [center addObserver:self
                   selector:@selector(onDidFinishLaunchingNotification:)
                       name:UIApplicationDidFinishLaunchingNotification
                     object:nil];
        [center addObserver:self
                   selector:@selector(onWillEnterForegroundNotification:)
                       name:UIApplicationWillEnterForegroundNotification
                     object:nil];
        [center addObserver:self
                   selector:@selector(onDidBecomeActiveNotification:)
                       name:UIApplicationDidBecomeActiveNotification
                     object:nil];

        [center addObserver:self
                   selector:@selector(onWillResignActiveNotification:)
                       name:UIApplicationWillResignActiveNotification
                     object:nil];
        [center addObserver:self
                   selector:@selector(onDidEnterBackgroundNotification:)
                       name:UIApplicationDidEnterBackgroundNotification
                     object:nil];
        [center addObserver:self
                   selector:@selector(onWillTerminateNotification:)
                       name:UIApplicationWillTerminateNotification
                     object:nil];


        [self startAppLog];
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

- (void)startAppLog {
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{

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

        self.track = track;
    });
}

+ (void)startAppLog {
    [BDAdapter sharedInstance];
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

}

+ (BOOL)handleURL:(NSURL *)URL scene:(id)scene {
    if ([[BDAutoTrackSchemeHandler sharedHandler] handleURL:URL appID:TestAPPID scene:scene]) {
        return YES;
    }

    return NO;
}

+ (void)trackCallback:(NSString *)method state:(NSInteger)state {
    [[BDAdapter sharedInstance] trackCallback:method state:state];
}

- (void)trackCallback:(NSString *)method state:(NSInteger)state {
    NSDictionary *param = @{@"method":method,
                            @"state":@(state),

    };
    [self.track eventV3:@"application" params:param];
}

#pragma mark - Notification

- (void)onDidFinishLaunchingNotification:(NSNotification *)not  {
    [self trackCallback:NSStringFromSelector(_cmd)
                  state:[UIApplication sharedApplication].applicationState];
}

- (void)onWillEnterForegroundNotification:(NSNotification *)not  {
    [self trackCallback:NSStringFromSelector(_cmd)
                  state:[UIApplication sharedApplication].applicationState];
}

- (void)onDidBecomeActiveNotification:(NSNotification *)not  {
    [self trackCallback:NSStringFromSelector(_cmd)
                  state:[UIApplication sharedApplication].applicationState];
}

- (void)onWillResignActiveNotification:(NSNotification *)not  {
    [self trackCallback:NSStringFromSelector(_cmd)
                  state:[UIApplication sharedApplication].applicationState];
}

- (void)onDidEnterBackgroundNotification:(NSNotification *)not  {
    [self trackCallback:NSStringFromSelector(_cmd)
                  state:[UIApplication sharedApplication].applicationState];
}

- (void)onWillTerminateNotification:(NSNotification *)not  {
    [self trackCallback:NSStringFromSelector(_cmd)
                  state:[UIApplication sharedApplication].applicationState];
}

@end
