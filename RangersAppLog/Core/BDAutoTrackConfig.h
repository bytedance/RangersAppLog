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



/*! @abstract 日志上报地区属性
 @discussion 上报地区请勿擅自选择，需要与申请服务的地区一致，或者咨询接口人确认
 */
typedef NS_ENUM(NSInteger, BDAutoTrackServiceVendor) {
    BDAutoTrackServiceVendorCN = 0x010, // 国内 中国
    BDAutoTrackServiceVendorSG,         // 新加坡
    BDAutoTrackServiceVendorVA,         // 美东
    BDAutoTrackServiceVendorPrivate,    // 私有化，此时一定要设置BDAutoTrackRequestURLBlock
};

NS_ASSUME_NONNULL_BEGIN

/*!
 BDAutoTrack日志上报配置
 */
@interface BDAutoTrackConfig : NSObject

/*! @abstract channel默认 @"App Store", Release版本只有 @"App Store"， debug版本可以任意设置. */
@property (nonatomic, copy) NSString *channel;

/*! @abstract 申请appID时候填写的英文名称 */
@property (nonatomic, copy, nullable) NSString *appName;

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

/*! @abstract 是否自动拉配置。默认YES，一般情况请不要修改。仅私有化部署情况，可能不需要自动拉取配置 */
@property (nonatomic, assign) BOOL autoFetchSettings;

/*! @abstract 根据App ID获取一个config
@param appID AppID
@result 一个config实例, 其他参数非必填，或者有默认值，可以直接通过setter 设置
*/
+ (instancetype)configWithAppID:(NSString *)appID;


/*!
 使用示例1：
  BDAutoTrackConfig *config = [BDAutoTrackConfig configWithSecondAppID:appid];
 // 初始化完成之后，可以调用其他接口
 BDAutoTrack *track = [BDAutoTrack trackWithConfig:config]

 // 设置一些属性等配置
 [track setCurrentUserUniqueID:@"123"];

 // 开始上报
 [track satrtTrack];

 // 用变量引用住track用于上报
 [track eventV3:xxx params:xxx];
 */

/*! @abstract 根据App ID获取一个config
@param appID AppID
@result 一个config实例, 此config默认设置了不会激活和拉取settings。可用于第三方SDK需要上报一些事件，但是不需要激活等
*/
+ (instancetype)configWithSecondAppID:(NSString *)appID;

@end

NS_ASSUME_NONNULL_END
