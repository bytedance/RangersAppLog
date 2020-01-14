# RangersAppLog

## Demo演示

1. `git clone git@github.com:bytedance/RangersAppLog.git`
2. `cd RangersAppLog/Eample`
3. `pod install`
4. `open RangersAppLog.xcworkspace`


## 要求

特别说明，只支持Xcode 11 打包开发，Xcode 11以下，请单独联系开发提供SDK包

* iOS 8.0+
* Xcode 11

## 版本说明

1. Lite版，埋点版本，即 `subspecs => ['Core']`
2. 无埋点版本，即 `subspecs => ['UITracker']`
3. 圈选Debug版本，即 `subspecs => ['Picker']`

## 集成方式


或者参照Demo工程的Podfile

```Rbuy
source 'https://cdn.cocoapods.org/'

# 接入无埋点版本
target 'YourTarget' do
  pod 'RangersAppLog', '~> 4.2.0'
end

# 接入埋点版本 
target 'YourTarget' do
  pod 'RangersAppLog', '~> 4.2.0',:subspecs => ['Core']
end

```

## 集成指南

更多接口参见头文件，和Demo工程.

### 初始化SDK

```Objective-C

#import <RangersAppLog/RangersAppLogUITrack.h>

+ (void)startAppLog {
    BDAutoTrackConfig *config = [BDAutoTrackConfig new];
    config.appID = @"159486";
    config.channel = @"App Store";
    config.appName = @"dp_tob_sdk_test2";
	 config.autoTrackEnabled = YES;
    /// show debug log
    config.showDebugLog = YES;
    config.logger = ^(NSString * _Nullable log) {
        NSLog(@"%@",log);
    };

    [BDAutoTrack setABTestFinishBlock:^(BOOL ABTestEnabled, NSDictionary * allConfigs) {
        NSLog(@"-- ABTestEnabled(%tu)",ABTestEnabled);
    }];
    /// change to your UserUniqueID if now is loged in
    NSString *uniqueID = @"12345";
    BDAutoTrack *track = [BDAutoTrack trackWithConfig:config];
    /// change to your UserUniqueID if now is loged in
    NSString *uniqueID = @"12345";
    [track setCurrentUserUniqueID:uniqueID];
    [track startTrack];
}

```

### 用户态变化

```Objective-C

+ (void)logout {
    [track clearUserUniqueID];
}

+ (void)login {
    /// change to your UserUniqueID
    NSString *uniqueID = @"12345";
    [track setCurrentUserUniqueID:uniqueID];
}

```

### 埋点事件上报

```Objective-C

+ (void)eventV3:(NSString *)event params:(NSDictionary *)params {
    [track eventV3:event params:params];
}

```

### Scheme上报

```Objective-C

#import <RangersAppLog/RangersAppLogCore.h>

/// 如果是iOS 13中重写UISceneDelegate的回调，则按照i以下code
- (void)scene:(UIScene *)scene openURLContexts:(NSSet<UIOpenURLContext *> *)URLContexts {
    for (UIOpenURLContext *context in URLContexts) {
        NSURL *URL = context.URL;
        if ([[BDAutoTrackSchemeHandler sharedHandler] handleURL:URL appID:@"appid" scene:scene]) {
            continue;
        }

        /// your handle code for the URL
    }
}

/// 如果是iOS 13一下，重写UIApplicationDelegate的回调方法，则参考以下code
- (BOOL)application:(UIApplication *)app openURL:(NSURL *)url options:(NSDictionary<UIApplicationOpenURLOptionsKey, id> *)options {
    if ([[BDAutoTrackSchemeHandler sharedHandler] handleURL:url appID:@"appid" scene:nil]) {
        return YES;
    }

    /// your handle code

    return NO;
}

```

## 版本更新记录

### 4.2.0

- 调整游戏预置埋点，接口不与上个版本兼容

### 4.1.0

- 通过Scheme打开圈选开关
- 默认subspec集成所有功能
- 去掉did接口，新增BytedanceDeviceID接口
- 安装包 795.99 KB

### 3.2.10

- 优化多线程卡顿问题
- 修复序列化crash问题



## 证书

本项目使用[MIT 证书](LICENSE)。详细内容参见[证书](LICENSE)文件。