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

## 集成方式

1. 直接下载podspec和Framework文件，按照Demo示例放到工程目录中，并引用

```
RangersAppLog/RangersAppLog.Framework
RangersAppLog.podspec
```

2. pod

或者参照Demo工程的Podfile

```Rbuy
source 'https://cdn.cocoapods.org/'

target 'YourTarget' do
  pod 'RangersAppLog', '~> 3.2.6'
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


#### 3.2.6

- 修复日志重复多报问题
- 修复多AppID时Session事件异常问题
- AppLog支持多AppID实例
- 修复写数据库trackGlobalEventID卡顿问题
- 修复 OpenUdid 初始化性能问题
- 新增Universal Link上报接口
- 移除对 UIWebView 无埋点支持
- 移除UIAlertView和UIActionSheet的无埋点支持
- 修复`cydia.app` 敏感字符串检测
- 增加subspec
	- Core模块是埋点事件
	- UITracker模块包含无埋点事件采集，依赖 Core
	- Picker模块是圈选SDK，依赖 UITracker



## 证书

本项目使用[MIT 证书](LICENSE)。详细内容参见[证书](LICENSE)文件。