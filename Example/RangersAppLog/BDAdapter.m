//
//  BDAdapter.m
//  RangersAppLog
//
//  Created by bob on 2019/9/9.
//  Copyright © 2019 Bytedance. All rights reserved.
//

#import "BDAdapter.h"
#import <RangersAppLog/BDAutoTrack.h>
#import <RangersAppLog/BDAutoTrackConfig.h>

@implementation BDAdapter

+ (void)startAppLog {
    BDAutoTrackConfig *config = [BDAutoTrackConfig new];
    config.appID = @"159486";
    config.channel = @"App Store";
    config.appName = @"dp_tob_sdk_test2";

    /// show debug log
    config.showDebugLog = YES;
    config.autoTrackEnabled = YES;
    config.logger = ^(NSString * _Nullable log) {
        NSLog(@"%@",log);
    };
//    config.autoActiveUser = NO;
    config.logNeedEncrypt = NO;
    [BDAutoTrack setABTestFinishBlock:^(BOOL ABTestEnabled, NSDictionary * allConfigs) {
        
    }];
    /// change to your UserUniqueID if now is loged in
    NSString *uniqueID = @"12345";
    [BDAutoTrack setCurrentUserUniqueID:uniqueID];
    [BDAutoTrack startTrackWithConfig:config];
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(3 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
//        [BDAutoTrack activeUser];
    });
}

+ (id)ABTestValue {
    /// change to your key
    NSString *key = @"experiment-no2";
    return [BDAutoTrack ABTestConfigValueForKey:key defaultValue:nil];
}

+ (void)logout {
    [BDAutoTrack clearUserUniqueID];
}

+ (void)login {
    /// change to your UserUniqueID
    NSString *uniqueID = @"12345";
    [BDAutoTrack setCurrentUserUniqueID:uniqueID];
}

+ (void)eventV3:(NSString *)event params:(NSDictionary *)params {
    [BDAutoTrack eventV3:event params:params];
}

@end
