# RangersAppLog

数据采集上报SDK。具体支持功能见官网 https://datarangers.com.cn/。

## Demo演示

**Example工程1**
1. `git clone git@github.com:bytedance/RangersAppLog.git`
2. `cd RangersAppLog/Example`
3. `pod install`
4. `open Example.xcworkspace`

**Example工程2**
1. `git clone git@github.com:bytedance/RangersAppLog.git`
2. `cd RangersAppLog/ObjCExample`
3. `pod install`
4. `open ObjCExample.xcworkspace`

## 开发环境要求

特别说明，只支持XCode 11+ 打包开发。若使用的Xcode版本为11以下，请单独联系开发提供SDK包

* iOS 9.0+
* XCode 11.0+

目前了解到使用XCode12开发可能存在一些问题（不是仅仅本SDK的单独存在的问题，而是XCode12的问题）。如在升级到XCode12后开发遇到问题，请反馈给您对接的技术支持同学，也可以提个issue。

## 版本说明

1. Lite版，埋点版本，即 `subspecs => ['Core','Log', 'Host/CN']`,如果需要采集IDFA,子库需要添加`Unique`
3. 圈选版本，即 `subspecs => ['Picker', 'Host/CN']`如果需要采集IDFA,子库需要添加`Unique`

## 集成方式

建议使用Cocoapods接入。可以参照下面的实例和Demo工程中的Podfile。

```ruby
# cdn trunk
source 'https://cdn.cocoapods.org/'
## or use ssh
# source 'git@github.com:CocoaPods/Specs.git'

source 'git@github.com:bytedance/cocoapods_sdk_source_repo.git'

# 接入无埋点版本
target 'YourTarget' do
    pod 'RangersAppLog', '~> 5.6.3',:subspecs => [
        'Picker',
        'Unique',  # 若需要采集IDFA，则引入Unique子库
        'Host/CN'  # 若您的APP的数据存储在中国, 则选择 Host/CN。否则请根据地域选择相应 Host 子库
    ]
end

# 接入埋点版本 
target 'YourTarget' do
    pod 'RangersAppLog', '~> 5.6.3',:subspecs => [
      'Core',
      'Log',
      'Unique',  # 若需要采集IDFA，则引入Unique子库
      'Host/CN'  # 若您的APP的数据存储在中国, 则选择 Host/CN。否则请根据地域选择相应 Host 子库
    ]
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

/// 如果是iOS 13中重写UISceneDelegate的回调，则参考以下code
- (void)scene:(UIScene *)scene openURLContexts:(NSSet<UIOpenURLContext *> *)URLContexts {
    for (UIOpenURLContext *context in URLContexts) {
        NSURL *URL = context.URL;
        if ([[BDAutoTrackSchemeHandler sharedHandler] handleURL:URL appID:@"appid" scene:scene]) {
            continue;
        }

        /// your handle code for the URL
    }
}

/// 如果是系统版本小于iOS 13，需要重写UIApplicationDelegate的回调方法，参考以下code
- (BOOL)application:(UIApplication *)app openURL:(NSURL *)url options:(NSDictionary<UIApplicationOpenURLOptionsKey, id> *)options {
    if ([[BDAutoTrackSchemeHandler sharedHandler] handleURL:url appID:@"appid" scene:nil]) {
        return YES;
    }

    /// your handle code

    return NO;
}

```

## 版本更新记录
### 5.6.4
- 支持bitcode
- 支持platform端属性

### 5.6.3
- 上报流量优化
- 支持在开发调试阶段清除缓存。见`BDAutoTrackCacheRemover.h` (生产环境请勿使用)
- bugfix

### 5.6.1
- bugfix: 修复激活url_safe base64相关问题

### 5.6.0（有bug，请使用5.6.1+）

- 新增 profile API. 详见头文件`BDAutoTrack+Profile.h`
- 移除移动端圈选。服务端圈选功能不受影响。建议您在平台的圈选页面上进行圈选，更加快捷方便。

### 5.5.0（有bug，请使用5.6.1+）

- 加密开关支持加密query字段
- 数据库文件夹移动到`Library/`目录并改名
- 上报URL隔离到`Host/XX`子库中
- 适配iOS14注册需求
- 增加用户触点(touchPoint)功能和`setTouchPoint`等接口
- 新增一个Objective-C Example工程

### 5.4.1

- 修复私有化配置且打开加密开关的场景下，客户端尝试解密服务器明文回包从而导致未获取到回包数据的问题

### 5.4.0

- 默认移除IDFA，IDFA放到了子库`Unique`中

### 5.3.1

- 修复UUID变化上报不及时问题
- 新增接口


## 证书

本项目使用[MIT 证书](LICENSE)。详细内容参见[证书](LICENSE)文件。
