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

1. Lite版，埋点版本，即 `subspecs => ['Core','Log']`,如果需要采集IDFA,子库需要添加`Unique`
3. 圈选版本，即 `subspecs => ['Picker']`如果需要采集IDFA,子库需要添加`Unique`

## 集成方式


或者参照Demo工程的Podfile

```Rbuy
# cdn trunk
source 'https://cdn.cocoapods.org/'

## or use ssh
source 'git@github.com:bytedance/cocoapods_sdk_source_repo.git'
source 'git@github.com:CocoaPods/Specs.git'

# 接入无埋点版本
target 'YourTarget' do
  pod 'RangersAppLog', '~> 5.4',:subspecs => ['Picker','Unique']
end

# 接入埋点版本 
target 'YourTarget' do
  pod 'RangersAppLog', '~> 5.4',:subspecs => ['Core','Log','Unique']
end

```

## 集成指南

更多接口参见头文件，和Demo工程.

### 初始化SDK

```Objective-C

#import <RangersAppLog/RangersAppLog.h>

- (void)startAppLog {
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
    /// change to your UserUniqueID if now is loged in
    NSString *uniqueID = @"12345";
    BDAutoTrack *track = [BDAutoTrack trackWithConfig:config];
    /// change to your UserUniqueID if now is loged in
    NSString *uniqueID = @"12345";
    [track setCurrentUserUniqueID:uniqueID];
    [track startTrack];
    
    self.track = track;
}

```

### 用户态变化

```Objective-C

- (void)logout {
    [self.track clearUserUniqueID];
}

- (void)login {
    /// change to your UserUniqueID
    NSString *uniqueID = @"12345";
    [self.track setCurrentUserUniqueID:uniqueID];
}

```

### 埋点事件上报

```Objective-C

+ (void)eventV3:(NSString *)event params:(NSDictionary *)params {
    [self.track eventV3:event params:params];
}

```

### Scheme上报

```Objective-C

#import <RangersAppLog/RangersAppLog.h>

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

### 5.4.1

- 修复私有化配置且打开加密开关的场景下，客户端尝试解密服务器明文回包从而导致未获取到回包数据的问题

### 5.4.0

- 默认移除IDFA，IDFA放到了子库`Unique`中

### 5.3.1

- 修复UUID变化上报不及时问题
- 新增接口


## 证书

本项目使用[MIT 证书](LICENSE)。详细内容参见[证书](LICENSE)文件。
