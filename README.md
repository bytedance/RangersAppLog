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
2. 无埋点版本，即 `subspecs => ['Core', 'UITracker']`
3. 圈选Debug版本，即 `subspecs => ['Core', 'UITracker','Picker']`

## 集成方式

### Xcode 11

或者参照Demo工程的Podfile

```Rbuy
source 'https://cdn.cocoapods.org/'

# 接入无埋点版本
target 'YourTarget' do
  pod 'RangersAppLog', '~> 3.2.7'
end

# 接入埋点版本
target 'YourTarget' do
  pod 'RangersAppLog/Core', '~> 3.2.7'
end

# 接入埋点版本 
target 'YourTarget' do
  pod 'RangersAppLog', '~> 3.2.7',:subspecs => ['Core']
end

```

### Xcode 10

后缀-rc作为Xcode 10 打包的二进制版本

```Rbuy
source 'https://cdn.cocoapods.org/'

# 接入无埋点版本
target 'YourTarget' do
  pod 'RangersAppLog', '3.2.7-rc.0'
end

# 接入埋点版本 
target 'YourTarget' do
  pod 'RangersAppLog/Core', '3.2.7-rc.0'
end

# 接入埋点版本 
target 'YourTarget' do
  pod 'RangersAppLog', '3.2.7-rc.0',:subspecs => ['Core']
end

```

**特别说明：Xcode10和Xcode11的二进制不兼容，不能相互使用**

- `@available`在Xcode10和Xcode11打包的二进制中不一样
- UIWindowScene等特性需要使用iOS 13，即要求Xcode11打包
- 应苹果爸爸要求，大家还是推荐升级到Xcode 11

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

#### 3.2.7
包括 3.27-rc.0

- 增加预置性能埋点事件
- 优化SDK启动性能
- 新增简化初始化接口
- 优化Reachability卡顿问题

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