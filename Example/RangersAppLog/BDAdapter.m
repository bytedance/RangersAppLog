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
@property (nonatomic, assign) NSUInteger eventIndex;

@end

@implementation BDAdapter

- (instancetype)init {
    self = [super init];
    if (self) {
        self.eventIndex = 0;
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
        NSString *uniqueID = @"123456789";
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
    NSString *uniqueID = @"123456789";
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
                            @"index":@(self.eventIndex),

    };
    self.eventIndex += 1;
    [self.track eventV3:@"application" params:param];
}

@end
