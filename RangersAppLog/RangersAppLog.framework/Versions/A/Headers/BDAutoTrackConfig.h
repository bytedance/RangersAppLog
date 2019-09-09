//
//  BDAutoTrackConfig.h
//  Applog
//
//  Created by bob on 2019/1/29.
//

#import <Foundation/Foundation.h>

/*! @abstract 日志输出
 @param log 输出的日志
 @discussion 请使用自己的日志SDK输出日志
 */
typedef void(^BDAutoTrackLogger)(NSString * _Nullable log);

/*! @abstract ABTest配置拉取回调
 @param ABTestEnabled ABTest是否开启
 @param allConfigs 后台返回的全部配置
 @discussion ABTestEnabled如果未开启，则，即使有config，SDK也会返回默认值；如果无网络或者其他原因注册失败，不会回调
 */
typedef void(^BDAutoTrackABTestFinishBlock)(BOOL ABTestEnabled, NSDictionary * _Nullable  allConfigs);

/*! @abstract 设备注册回调
 @param deviceID did
 @param installID iid
 @param ssID ssid
 @param userUniqueID userUniqueID
 @discussion 可能为空，如果无网络或者其他原因注册失败，不会回调
 */
typedef void(^BDAutoTrackRegisterFinishBlock)(NSString * _Nullable deviceID, NSString * _Nullable installID, NSString * _Nullable ssID, NSString *_Nullable userUniqueID);

/*! @abstract 自定义上报信息
 @discussion 每次上报都会回调，设置一次即可，格式要求同日志要求，需要可序列化；如果无法序列化，会被丢弃
@result NSDictionary custom数据
 */
typedef NSDictionary<NSString*, id> *_Nonnull (^BDAutoTrackCustomHeaderBlock)(void);

/*! @abstract 日志上报地区属性
 @discussion 上报地区请求擅自选择，需要与申请服务的地区一致，或者咨询接口人确认
 */
typedef NS_ENUM(NSInteger, BDAutoTrackServiceVendor) {
    BDAutoTrackServiceVendorCN = 0x010, // 国内 中国
    BDAutoTrackServiceVendorSG,         // 新加坡
    BDAutoTrackServiceVendorVA,         // 美东
};

NS_ASSUME_NONNULL_BEGIN

/*!
 BDAutoTrack日志上报配置
 */
@interface BDAutoTrackConfig : NSObject

/*! @abstract channel要求非空，必须设置， Release版本只有 @"App Store"， debug版本可以任意设置. */
@property (nonatomic, copy) NSString *channel;

/*! @abstract 申请appID时候填写的英文名称，非空，必须设置 */
@property (nonatomic, copy) NSString *appName;

/*! @abstract AppID，非空，必须设置 */
@property (nonatomic, copy) NSString *appID;

/*! @abstract 默认国内,初始化时一定要传正确的值
 @discussion 发生变化时候请调用 `+[BDAutoTrack setServiceVendor:]`更新值
 @discussion 会影响注册和日志上报。所以如果发生变化后，下次启动初始化请传入正确的值
 */
@property (nonatomic, assign) BDAutoTrackServiceVendor serviceVendor;

/*! @abstract 是否开启无埋点。同时需要在Tea配置。
 @discussion 如果设置NO且Tea平台配置NO，则不会采集无埋点事件
 @discussion 如果设置NO且Tea平台配置YES，则拉取配置成功后开始采集无埋点事件
 @discussion 如果设置YES且Tea平台配置NO，则拉取配置成功后停止采集无埋点事件
 @discussion 如果设置YES且Tea平台配置YES，则采集无埋点事件
 */
@property (nonatomic, assign) BOOL autoTrackEnabled;

/*! @abstract 游戏模式，开启游戏模式会默认上报游戏心跳事件 */
@property (nonatomic, assign) BOOL gameModeEnable;

/*! @abstract 是否自动激活。默认YES，一般情况请不要修改 */
@property (nonatomic, assign) BOOL autoActiveUser;

/*! @abstract 采集事件的时候输出日志，在控制台中可以查看
 @discussion 需要同时设置logger，因为NSLog低效，且在iOS 13中有问题。release版本请设置为NO
 */
@property (nonatomic, assign) BOOL showDebugLog;

/*! @abstract 采集事件的时候输出日志，在控制台中可以查看
 @discussion logger为nil，则不会输出日志
 */
@property (nonatomic, copy, nullable) BDAutoTrackLogger logger;

/*! @abstract 日志上报是否加密。用于debug情况可以抓包调试 */
@property (nonatomic, assign) BOOL logNeedEncrypt;

/*! @abstract 语言
 @discussion 如果设置过，会保存值，直到下次改变或者清空
 @discussion 如果没有值，默认会读取 `[[NSLocale currentLocale] objectForKey:NSLocaleLanguageCode]`
 @discussion 发生变化时候请调用 `+[BDAutoTrack setAppLauguage:]`更新值
 @discussion 初始值也 请改用 +[BDAutoTrack setAppLauguage:]
 */
@property (nonatomic, copy, nullable) NSString *appLauguage DEPRECATED_MSG_ATTRIBUTE("Use `+[BDAutoTrack setAppLauguage:]` instead");

/*! @abstract 地区
 @discussion 如果设置过，会保存值，直到下次改变或者清空
 @discussion 如果没有值，默认会读取 `[[NSLocale currentLocale] objectForKey:NSLocaleCountryCode]`
 @discussion 发生变化时候请调用 `+[BDAutoTrack setAppRegion:]`更新值
 @discussion 初始值也 请改用 +[BDAutoTrack setAppRegion:]
 */
@property (nonatomic, copy, nullable) NSString *appRegion DEPRECATED_MSG_ATTRIBUTE("Use `+[BDAutoTrack setAppRegion:]` instead");

/*! @abstract 用户ID。如果初始化的时候有值，可以初始化的时候设置。无，则不需要设置。
 @discussion 发生变化时候，请调用 `+[BDAutoTrack setCurrentUserUniqueID:]`更新值
 */
@property (nonatomic, copy, nullable) NSString *userUniqueID;

/*! @abstractABTest相关值
 @discussion 发生变化时候，请调用 `+[BDAutoTrack setServerVersions:]`更新值
 @discussion 初始值也 请改用 +[BDAutoTrack setServerVersions:]
 */
@property (nonatomic, copy, nullable) NSString *abServerVersions DEPRECATED_MSG_ATTRIBUTE("Use `+[BDAutoTrack setServerVersions:]` instead");

/*! @abstract ABTest配置拉取回调
 @discussion 请改用 +[BDAutoTrack setRegisterFinishBlock:]
 */
@property (nonatomic, copy, nullable) BDAutoTrackABTestFinishBlock ABTestFinishBlock DEPRECATED_MSG_ATTRIBUTE("Use `+[BDAutoTrack setABTestFinishBlock:]` instead");

/*! @abstract 注册回调.
 @discussion 请改用 +[BDAutoTrack setRegisterFinishBlock:]
 */
@property (nonatomic, copy, nullable) BDAutoTrackRegisterFinishBlock registerFinishBlock DEPRECATED_MSG_ATTRIBUTE("Use `+[BDAutoTrack setRegisterFinishBlock:]` instead");

/*! @abstract 自定义上报信息.
@discussion 请改用 +[BDAutoTrack setCustomHeaderBlock:]
 */
@property (nonatomic, copy, nullable) BDAutoTrackCustomHeaderBlock customHeaderBlock DEPRECATED_MSG_ATTRIBUTE("Use `+[BDAutoTrack setCustomHeaderBlock:]` instead");

@end

NS_ASSUME_NONNULL_END
