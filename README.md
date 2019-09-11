# RangersAppLog

## Demo演示

1. `git clone git@github.com:bytedance/RangersAppLog.git`
2. `cd RangersAppLog/Eample`
3. `pod install`
4. `open RangersAppLog.xcworkspace`


## 要求

* iOS 8.0+

## 集成方式

1. 直接下载podspec和Framework文件，按照Demo示例放到工程目录中，并引用

```
RangersAppLog/RangersAppLog.Framework
RangersAppLog.podspec
```

2. pod

或者参照Demo工程的Podfile

```Rbuy
source 'https://github.com/CocoaPods/Specs.git'

target 'YourTarget' do
  pod 'RangersAppLog', '3.2.5'
end
```

## 集成指南

更多接口参见头文件，或者[接入文档](https://bytedance.feishu.cn/space/doc/doccnM5AI18azkKxasnNrP).

### 初始化SDK

```Objective-C
#import <RangersAppLog/BDAutoTrack.h>
#import <RangersAppLog/BDAutoTrackConfig.h>

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
    [BDAutoTrack setCurrentUserUniqueID:uniqueID];
    [BDAutoTrack startTrackWithConfig:config];
}

```

### 用户态变化

```Objective-C

+ (void)logout {
    [BDAutoTrack clearUserUniqueID];
}

+ (void)login {
    /// change to your UserUniqueID
    NSString *uniqueID = @"12345";
    [BDAutoTrack setCurrentUserUniqueID:uniqueID];
}

```

### 埋点事件上报

```Objective-C

+ (void)eventV3:(NSString *)event params:(NSDictionary *)params {
    [BDAutoTrack eventV3:event params:params];
}

```

## 版本更新记录

#### 最新稳定版本

- 3.2.5 


## 证书

本项目使用[MIT 证书](LICENSE)。详细内容参见[证书](LICENSE)文件。