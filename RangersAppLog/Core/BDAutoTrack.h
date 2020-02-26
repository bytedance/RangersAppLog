//
//  BDTracker.h
//  Applog
//
//  Created by bob on 2019/1/20.
//

#import <Foundation/Foundation.h>
#import "BDAutoTrackConfig.h"

NS_ASSUME_NONNULL_BEGIN

/*!
 请求URL type
 */
typedef NSInteger BDAutoTrackRequestURLType NS_TYPED_ENUM;

FOUNDATION_EXTERN BDAutoTrackRequestURLType const BDAutoTrackRequestURLRegister; /// 注册
FOUNDATION_EXTERN BDAutoTrackRequestURLType const BDAutoTrackRequestURLActivate; /// 激活
FOUNDATION_EXTERN BDAutoTrackRequestURLType const BDAutoTrackRequestURLSettings; /// 基本配置
FOUNDATION_EXTERN BDAutoTrackRequestURLType const BDAutoTrackRequestURLABTest;   /// ABTest配置
FOUNDATION_EXTERN BDAutoTrackRequestURLType const BDAutoTrackRequestURLLog;      /// 日志上报
FOUNDATION_EXTERN BDAutoTrackRequestURLType const BDAutoTrackRequestURLLogBackup;/// 日志上报备用

/*! @abstract 自定义请求链接，把相关请求发送到对应的自定义的URL上
 @param vendor 地区
 @param requestURLType 上面的六个枚举值
 @discussion 一般情况不需要实现；如果实现，针对想改变的枚举值返回一个准确的URL，其他不想修改的返回nil即可
 @result 返回自定义的URL
 */
typedef NSString * _Nullable (^BDAutoTrackRequestURLBlock)(BDAutoTrackServiceVendor vendor, BDAutoTrackRequestURLType requestURLType);

/*! @abstract 自定义上报信息
 @discussion 每次上报都会回调，设置一次即可，格式要求同日志要求，需要可序列化；如果无法序列化，会被丢弃
 @result NSDictionary custom数据
 */
typedef NSDictionary<NSString*, id> *_Nonnull (^BDAutoTrackCustomHeaderBlock)(void);

/*! @abstract
BDAutoTrack 增加多实例支持
 使用示例1：
  BDAutoTrackConfig *config = [BDAutoTrackConfig new];
  config.xxx = xxx;
  ...
 // 初始化完成之后，可以调用其他接口
 BDAutoTrack *track = [BDAutoTrack trackWithConfig:config]

 // 设置一些属性等配置
 [track setCurrentUserUniqueID:@"123"];

 // 开始上报
 [track satrtTrack];

 // 用变量引用住track用于上报
 [track eventV3:xxx params:xxx];
 */
/*!
 BDAutoTrack日志上报功能的类
 */
@interface BDAutoTrack : NSObject

/*! @abstract
SDK版本号.
 */
@property (class, nonatomic, copy, readonly) NSString *sdkVersion;

/*! @abstract
 针对每个AppID 设备唯一rangers Device ID. 非数字，随机字符串，一般情况请不要存储，从SDK接口获取即可。
 @discussion 特别说明，rangersDeviceID是字符串，不是数字
 */
@property (nonatomic, copy, readonly, nullable) NSString *rangersDeviceID;

/*! @abstract
 安装ID，是数字字符串，可以转化为数字。
 */
@property (nonatomic, copy, readonly, nullable) NSString *installID;

/*! @abstract
 数说ID，一般情况下，一个自然人的ssid是一致的。
 */
@property (nonatomic, copy, readonly, nullable) NSString *ssID;

/*! @abstract
 通过[BDAutoTrack setCurrentUserUniqueID:]接口传入到SDK内部的uuid
 */
@property (nonatomic, copy, readonly, nullable) NSString *userUniqueID;

/*! @abstract 初始化的AppID
 */
@property (nonatomic, copy, readonly) NSString *appID;

/*! @abstract 初始化方法，初始化一个Track实例
 @param config 初始化配置，AppID AppName Channel是必须的
 @discussion 初始化接口可以重复调用，会返回同一个实例，推荐返回之后，引用住这个实例，下次上报方便使用。
 @result 一个Track实例
 */
+ (nullable instancetype)trackWithConfig:(BDAutoTrackConfig *)config;

/*! @abstract 根据App ID获取一个已经初始化过的Track实例
 @param appID AppID
 @discussion 此接口需要先调用 `[BDAutoTrack trackWithConfig:]`初始化过实例，才能获取到
 @result 一个Track实例
 */
+ (nullable instancetype)trackWithAppID:(NSString *)appID;

/*! @abstract 开始埋点和无埋点上报
 @discussion 需要在`[BDAutoTrack trackWithConfig:]`初始化之后手动调用此方法。调用此方法之前，可以做一些额外的配置
 */
- (void)startTrack;

/*! @abstract 手动触发获取SDK上报配置值请求
 @discussion 手动触发请求
 */
- (void)startFetchTrackerConfiguration __attribute__((deprecated("SDK会自动拉取，此接口是内部开发过程中开发调试。后续会移除")));

/*! @abstract userAgent
 @discussion 每次启动SDK的时候设置一次，发生变化的时候设置即可。一般不会发生变化，只需要设置一次即可
 @param userAgent 日志上报HTTP/HTTPS 请求里面的 userAgent
 */
- (void)setUserAgent:(nullable NSString *)userAgent;

/*! @abstract UserUniqueID发生变化时设置
 @discussion 有值，则设置为ID值；登出 请调用 [BDAutoTrack clearUserUniqueID] 或者传 nil
 @discussion SDK会保存，因此只需要变化的时候设置。
 @param uniqueID 用户id，如无特殊需求，请勿传 空字符串 或者 全是空格的字符串
 */
- (void)setCurrentUserUniqueID:(nullable NSString *)uniqueID;

/*! @abstract 登出 logout
 @discussion 登出 logout
 */
- (void)clearUserUniqueID;

/*! @abstract 设置上报Host地区，有国内、新加坡、美东三个选项
 @discussion 发生变化可以更新，不需要一直重复设置
 @param serviceVendor 地区
 */
- (void)setServiceVendor:(BDAutoTrackServiceVendor)serviceVendor;

/*! @abstract 设置自定义的URL回调
 @param requestURLBlock 回调block，设置一次即可，不需要多次设置
 @discussion requestURLBlock 会覆盖之前的初始化或者上一次设置的回调，如果为nil会清空回调
 @discussion block在初始化之前 设置一次即可，每次拉取请求都会回调，请勿一直重复设置
 */
- (void)setRequestURLBlock:(nullable BDAutoTrackRequestURLBlock)requestURLBlock;

/*! @abstract 地区
 @discussion 如果设置过，会保存值，直到下次改变或者清空
 @discussion 如果没有值，默认会读取 `[[NSLocale currentLocale] objectForKey:NSLocaleCountryCode]`
 @discussion 发生变化时候请调用 `+[BDAutoTrack setAppRegion:]`更新值
 */
- (void)setAppRegion:(nullable NSString *)appRegion;

/*! @abstract 语言
 @discussion 如果设置过，会保存值，直到下次改变或者清空
 @discussion 如果没有值，默认会读取 `[[NSLocale currentLocale] objectForKey:NSLocaleLanguageCode]`
 @discussion 发生变化时候请调用 `+[BDAutoTrack setAppLauguage:]`更新值
 */
- (void)setAppLauguage:(nullable NSString *)appLauguage;


/*! @abstract 添加自定义上报信息
 @param customHeaderBlock 自定义上报信息
 @discussion customHeaderBlock 一次App启动设置一次即可；App重启需要重新设置，因为SDK不会保存上次设置的值；会覆盖之前的初始化的或者上一次设置的，如果为nil会清空回调
 @discussion block在初始化之前设置一次即可，每次都会回调，不会把block返回参数保存，而导致获取不到变化的值，请勿一直重复设置
 */
- (void)setCustomHeaderBlock:(nullable BDAutoTrackCustomHeaderBlock)customHeaderBlock;

/*! @abstract 日志上报
 @param event 事件名称，不能为nil或空字符串
 @param params 事件参数。可以为空或者nil，但是param如果非空，需要可序列化成json
 @discussion params 请参考文档中的日志格式要求，或者使用 [NSJSONSerialization isValidJSONObject:] 来检查params是否可序列化
 @result 是否成功，如果失败，则表示此日志不会被上报。原因是无法序列化。
 */
- (BOOL)eventV3:(NSString *)event params:(nullable NSDictionary *)params;

/*! @abstract 日志上报
@param event 事件名称，不能为nil或空字符串
@result 是否成功
*/
- (BOOL)eventV3:(NSString *)event;

#pragma mark - ABTest

/*! @abstract 获取ABTest的配置值
 @param key ABTest的key
 @param defaultValue 默认值，如果没有配置，或者未开启ABTest则返回默认值
 @discussion 未开启ABTest或者ABTest配置了默认值，都是返回默认值，因此建议监听ABTestFinishBlock来判断是否开启了ABTest
 @discussion 通过此接口读取会触发曝光统计
 @result 返回ABTest的配置值
 */
- (nullable id)ABTestConfigValueForKey:(NSString *)key defaultValue:(nullable id)defaultValue;

/*! @abstract 获取ABTest相关配置
@result 返回ABTest的vids值
 @discussion 此值不需要设置到上报的event中，SDK会自动给每个event添加
 */
- (nullable NSString *)abVids;

/*! @abstract 获取ABTest相关配置
 @result 返回ABTest的所有的vids值
 @discussion 此接口不会触发曝光，可以随意读取
 */
- (nullable NSString *)allAbVids;

/*! @abstract 获取ABTest相关配置
 @result 返回ABTest的所有的Configs值
 @discussion 此接口不会触发曝光，可以随意读取。
 @discussion 如果正常为了做实验，请勿使用此接口，请使用-[BDAutoTrack ABTestConfigValueForKey:defaultValue:]接口
 */
- (nullable NSDictionary *)allABTestConfigs;

#pragma mark - private API

/*! @abstract 调用用户激活接口。一般情况下，请勿调用，除非知晓调用可能的问题。
 */
- (void)activeUser;

@end

/// 以下是单例方法
#pragma mark - SharedInstance 推荐使用多实例方式上报，参考前面的使用示例

/*! @abstract
BDAutoTrack 里面引用住一个BDAutoTrack单例，方便过渡期使用。推荐统一修改到实例方法。
 特别说明：
    1. 先调用[BDAutoTrack startTrackWithConfig:config];
       之后调用BDAutoTrack的其他 类方法接口

 使用示例1：
  BDAutoTrackConfig *config = [BDAutoTrackConfig new];
  config.xxx = xxx;
  ...
 // 初始化完成之后，可以调用其他接口
 [BDAutoTrack startTrackWithConfig:config]

 // 设置一些属性等配置
 [BDAutoTrack setCurrentUserUniqueID:@"123"];

 */

/*! @discussion 设置注册成功和ABTest拉取成功回调，推荐使用通知方法。
@discussion 请参考 <RangersAppLog/BDAutoTrackNotifications.h>注释。
@discussion 建议采用 <RangersAppLog/BDAutoTrack.h> 里面的实例方法接口，类方法接口不推荐使用
*/
@interface BDAutoTrack (SharedInstance)

/*! @abstract
针对每个AppID 设备唯一rangers Device ID. 非数字，随机字符串，一般情况请不要存储，从SDK接口获取即可。
@discussion 特别说明，rangersDeviceID是字符串，不是数字
*/
@property (class, nonatomic, copy, readonly, nullable) NSString *rangersDeviceID;

/*! @abstract
 安装ID，是数字字符串，可以转化为数字。
 */
@property (class, nonatomic, copy, readonly, nullable) NSString *installID;

/*! @abstract
 数说ID，一般情况下，一个自然人的ssid是一致的。
 */
@property (class, nonatomic, copy, readonly, nullable) NSString *ssID;

/*! @abstract
 通过[BDAutoTrack setCurrentUserUniqueID:]接口传入到SDK内部的uuid
 */
@property (class, nonatomic, copy, readonly, nullable) NSString *userUniqueID;

/*! @abstract 初始化的AppID
 */
@property (class, nonatomic, copy, readonly) NSString *appID;

/*! @abstract 初始化方法，初始化一个Track实例，BDAutoTrack 会引用住该实例方便调用
@param config 初始化配置，AppID AppName Channel是必须的
@discussion 初始化并启动SDK。相当于 下面两个调用加起来一次
 [BDAutoTrack sharedTrackWithConfig:config]
 [BDAutoTrack startTrack]
*/
+ (void)startTrackWithConfig:(BDAutoTrackConfig *)config;

/*! @abstract userAgent 在初始化之后设置
 @discussion 每次启动SDK的时候设置一次，发生变化的时候设置即可。一般不会发生变化，只需要设置一次即可
 @param userAgent 日志上报HTTP/HTTPS 请求里面的 userAgent
 */
+ (void)setUserAgent:(nullable NSString *)userAgent;

/*! @abstract UserUniqueID发生变化时设置 在初始化之后设置
 @discussion 有值，则设置为ID值；登出 请调用 [BDAutoTrack clearUserUniqueID] 或者传 nil
 @discussion SDK会保存，因此只需要变化的时候设置。
 @param uniqueID 用户id，如无特殊需求，请勿传 空字符串 或者 全是空格的字符串
 */
+ (void)setCurrentUserUniqueID:(nullable NSString *)uniqueID;

/*! @abstract 登出 logout
 @discussion 登出 logout
 */
+ (void)clearUserUniqueID;

/*! @abstract 设置上报Host地区，在初始化之后设置，初始化之前请在config中设置
 @discussion 发生变化可以更新，不需要一直重复设置
 @param serviceVendor 地区
 */
+ (void)setServiceVendor:(BDAutoTrackServiceVendor)serviceVendor;

/*! @abstract 设置自定义的URL回调 在初始化之后设置
 @param requestURLBlock 回调block，设置一次即可，不需要多次设置
 @discussion requestURLBlock 会覆盖之前的初始化或者上一次设置的回调，如果为nil会清空回调
 @discussion block在初始化之后 设置一次即可，每次拉取请求都会回调，请勿一直重复设置
 */
+ (void)setRequestURLBlock:(nullable BDAutoTrackRequestURLBlock)requestURLBlock;

/*! @abstract 地区 在初始化之后设置
 @discussion 如果设置过，会保存值，直到下次改变或者清空
 @discussion 如果没有值，默认会读取 `[[NSLocale currentLocale] objectForKey:NSLocaleCountryCode]`
 @discussion 发生变化时候请调用 `+[BDAutoTrack setAppRegion:]`更新值
 */
+ (void)setAppRegion:(nullable NSString *)appRegion;

/*! @abstract 语言 在初始化之后设置
 @discussion 如果设置过，会保存值，直到下次改变或者清空
 @discussion 如果没有值，默认会读取 `[[NSLocale currentLocale] objectForKey:NSLocaleLanguageCode]`
 @discussion 发生变化时候请调用 `+[BDAutoTrack setAppLauguage:]`更新值
 */
+ (void)setAppLauguage:(nullable NSString *)appLauguage;

/*! @abstract 添加自定义上报信息
 @param customHeaderBlock 自定义上报信息
 @discussion customHeaderBlock 一次App启动设置一次即可；App重启需要重新设置，因为SDK不会保存上次设置的值；会覆盖之前的初始化的或者上一次设置的，如果为nil会清空回调
 @discussion block在初始化之后设置一次即可，每次都会回调，不会把block返回参数保存，而导致获取不到变化的值，请勿一直重复设置
 */
+ (void)setCustomHeaderBlock:(nullable BDAutoTrackCustomHeaderBlock)customHeaderBlock;

/*! @abstract 日志上报，在初始化之后设置才能调用
 @param event 事件名称，不能为nil或空字符串
 @param params 事件参数。可以为空或者nil，但是param如果非空，需要可序列化成json
 @discussion params 请参考文档中的日志格式要求，或者使用 [NSJSONSerialization isValidJSONObject:] 来检查params是否可序列化
 @result 是否成功，如果失败，则表示此日志不会被上报。原因是无法序列化。
 */
+ (BOOL)eventV3:(NSString *)event params:(nullable NSDictionary *)params;

#pragma mark - ABTest

/*! @abstract 获取ABTest的配置值，在初始化之后设置才能调用
 @param key ABTest的key
 @param defaultValue 默认值，如果没有配置，或者未开启ABTest则返回默认值
 @discussion 未开启ABTest或者ABTest配置了默认值，都是返回默认值，因此建议监听ABTestFinishBlock来判断是否开启了ABTest
 @discussion 通过此接口读取会触发曝光统计
 @discussion 推荐使用通知来监听ABTest配置是否拉取成功，请参考 <RangersAppLog/BDAutoTrackNotifications.h>注释
 @result 返回ABTest的配置值
 */
+ (nullable id)ABTestConfigValueForKey:(NSString *)key defaultValue:(nullable id)defaultValue;

/*! @abstract 获取ABTest相关配置，在初始化之后设置才能调用
@result 返回ABTest的vid值
 @discussion 此值不需要设置到上报的event中，SDK会自动给每个event添加
 */
+ (nullable NSString *)abVids;

/*! @abstract 获取ABTest相关配置，在初始化之后设置才能调用
 @result 返回ABTest的所有的vids值
 @discussion 此接口不会触发曝光，可以随意读取
 */
+ (nullable NSString *)allAbVids;

/*! @abstract 获取ABTest相关配置，在初始化之后设置才能调用
 @result 返回ABTest的所有的Configs值
 @discussion 此接口不会触发曝光，可以随意读取。
 @discussion 如果正常为了做实验，请勿使用此接口，请使用-[BDAutoTrack ABTestConfigValueForKey:defaultValue:]接口
 */
+ (nullable NSDictionary *)allABTestConfigs;

#pragma mark - private API

/*! @abstract 调用用户激活接口，在初始化之后设置才能调用
 一般情况下，请勿调用，除非知晓调用可能的问题
 */
+ (void)activeUser;

@end


#pragma mark - Special 推荐使用多实例方式上报，参考前面的使用示例

@interface BDAutoTrack (SharedSpecial)

+ (BOOL)eventV3:(NSString *)event params:(nullable NSDictionary *)params specialParams:(NSDictionary *)specialParams __attribute__((deprecated("过期方法，推荐使用多实例的方式")));

+ (BOOL)customEvent:(NSString *)category params:(NSDictionary *)params __attribute__((deprecated("过期方法，推荐使用多实例的方式")));

@end


NS_ASSUME_NONNULL_END
