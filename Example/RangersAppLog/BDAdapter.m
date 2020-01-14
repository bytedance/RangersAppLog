//
//  BDAdapter.m
//  RangersAppLog
//
//  Created by bob on 2019/9/9.
//  Copyright © 2019 Bytedance. All rights reserved.
//

#import "BDAdapter.h"
#import "BDFeedModel.h"
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
        self.events = [NSMutableArray new];
        [self startAppLog];
        [[NSNotificationCenter defaultCenter] addObserver:self
                                                 selector:@selector(onWillEnterForeground)
                                                     name:UIApplicationWillEnterForegroundNotification
                                                   object:nil];

        [[NSNotificationCenter defaultCenter] addObserver:self
                                                 selector:@selector(onDidBecomeActive)
                                                     name:UIApplicationDidBecomeActiveNotification
                                                   object:nil];
        
        [[NSNotificationCenter defaultCenter] addObserver:self
                                                 selector:@selector(onRegisterSuccess:)
                                                     name:BDAutoTrackNotificationRegisterSuccess
                                                   object:nil];
        [[NSNotificationCenter defaultCenter] addObserver:self
                                                 selector:@selector(onABTestSuccess)
                                                     name:BDAutoTrackNotificationABTestSuccess
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

- (void)startAppLog {
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{

        BDAutoTrackConfig *config = [BDAutoTrackConfig new];
        config.appID = TestAPPID;
        config.channel = @"App Store";
        config.appName = @"dp_tob_sdk_test2";

        /// show debug log
        config.showDebugLog = YES;
        config.logNeedEncrypt = YES;
        config.logger = ^(NSString * _Nullable log) {
            NSLog(@"%@",log);
        };

        BDAutoTrack *track = [BDAutoTrack trackWithConfig:config];
        /// change to your UserUniqueID if now is loged in
        NSString *uniqueID = @"12345679";
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
    BDFeedModel *model = [BDFeedModel modelWithIndex:self.eventIndex method:method state:state];
    [self.events addObject:model];
    self.eventIndex += 1;
    [self.track eventV3:@"application" params:param];
}

- (void)onDidBecomeActive {
    NSLog(@"app %@ %zd", NSStringFromSelector(_cmd), [UIApplication sharedApplication].applicationState);
}

- (void)onWillEnterForeground {
    NSLog(@"app %@ %zd", NSStringFromSelector(_cmd), [UIApplication sharedApplication].applicationState);
}

- (void)onRegisterSuccess:(NSNotification *)not  {
    NSLog(@"NSNotification onRegisterSuccess did = %@",self.track.rangersDeviceID);
    NSLog(@"NSNotification onRegisterSuccess iid = %@",self.track.installID);
    NSLog(@"NSNotification onRegisterSuccess uuid = %@",self.track.userUniqueID);
    NSLog(@"NSNotification onRegisterSuccess ssid = %@",self.track.ssID);
}

- (void)onABTestSuccess  {
    NSLog(@"NSNotification onABTestSuccess");
}

@end
