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

FOUNDATION_EXTERN BDAutoTrackRequestURLType const BDAutoTrackRequestURLRegister; // 注册
FOUNDATION_EXTERN BDAutoTrackRequestURLType const BDAutoTrackRequestURLActivate; // 激活
FOUNDATION_EXTERN BDAutoTrackRequestURLType const BDAutoTrackRequestURLSettings; // 基本配置
FOUNDATION_EXTERN BDAutoTrackRequestURLType const BDAutoTrackRequestURLABTest;   // ABTest配置
FOUNDATION_EXTERN BDAutoTrackRequestURLType const BDAutoTrackRequestURLLog;      // 日志上报
FOUNDATION_EXTERN BDAutoTrackRequestURLType const BDAutoTrackRequestURLLogBackup;// 日志上报备用

/*! @abstract 自定义请求链接，把相关请求发送到对应的自定义的URL上
 @param vendor 地区
 @param requestURLType 上面的六个枚举值
 @discussion 一般情况不需要实现；如果实现，针对想改变的枚举值返回一个准确的URL，其他不想修改的返回nil即可
 @result 返回自定义的URL
 */
typedef NSString * _Nullable (^BDAutoTrackRequestURLBlock)(BDAutoTrackServiceVendor vendor, BDAutoTrackRequestURLType requestURLType);

/*!
 BDAutoTrack日志上报功能的类
 */
@interface BDAutoTrack : NSObject

/*! @abstract The SDK version. */
@property (class, nonatomic, copy, readonly) NSString *sdkVersion;

/*! @abstract The unique device ID that get from register server. */
@property (class, nonatomic, copy, readonly, nullable) NSString *deviceID;

/*! @abstract The unique install ID that get from register server. */
@property (class, nonatomic, copy, readonly, nullable) NSString *installID;

/*! @abstract The unique ssID that get from register server. */
@property (class, nonatomic, copy, readonly, nullable) NSString *ssID;

/*! @abstract 如果当前已经初始化过，返回AppID 否则返回nil
 */
@property (class, nonatomic, copy, readonly, nullable) NSString *currentAppID;

/*! @abstract 通过 BDAutoTrackConfig 设置的 user_unique_id，可能为空。 */
@property (class, nonatomic, copy, readonly, nullable) NSString *userUniqueID;

/*! @abstract 初始化注册
 @param config 初始化配置，AppID AppName Channel是必须的
 @discussion 初始化接口可以重复调用，但是AppID必须相同且只有一个。
 */
+ (void)startTrackWithConfig:(BDAutoTrackConfig *)config;

/*! @abstract 手动触发获取SDK上报配置值请求
 @discussion 手动触发请求
 */
+ (void)startFetchTrackerConfiguration;

/*! @abstract UserUniqueID发生变化时设置
 @discussion 有值，则设置为ID值；登出，可以设置为nil
 @param uniqueID 用户id
 @param didRetriveBlock 请求回调。
 @discussion didRetriveBlock 会覆盖之前的初始化或者上一次设置的回调，如果为nil会清空回调
 @discussion 请分别依次调用`[BDAutoTrack setRegisterFinishBlock:]` 和 `[BDAutoTrack setCurrentUserUniqueID:]`
 @discussion 先设置回调`[BDAutoTrack setRegisterFinishBlock:]` 后设置uid `[BDAutoTrack setCurrentUserUniqueID:]`
 */
+ (void)setCurrentUserUniqueID:(nullable NSString *)uniqueID
           didRetriveSSIDBlock:(nullable BDAutoTrackRegisterFinishBlock)didRetriveBlock DEPRECATED_MSG_ATTRIBUTE("deprecated, 请分别单独调用`[BDAutoTrack setCurrentUserUniqueID:]` or `[BDAutoTrack setRegisterFinishBlock:]`");

/*! @abstract userAgent
 @discussion 每次启动SDK的时候设置一次，发生变化的时候设置即可。一般不会发生变化，只需要设置一次即可
 @param userAgent 日志上报HTTP/HTTPS 请求里面的 userAgent
 */
+ (void)setUserAgent:(nullable NSString *)userAgent;

/*! @abstract UserUniqueID发生变化时设置
 @discussion 有值，则设置为ID值；登出 请调用 [BDAutoTrack clearUserUniqueID] 或者传 nil
 @discussion SDK会保存，因此只需要变化的时候设置。
 @param uniqueID 用户id，如无特殊需求，请勿传 空字符串 或者 全是空格的字符串
 */
+ (void)setCurrentUserUniqueID:(nullable NSString *)uniqueID;

/*! @abstract 登出 logout
 @discussion 登出 logout
 */
+ (void)clearUserUniqueID;

/*! @abstract 设置上报Host地区，有国内、新加坡、美东三个选项
 @discussion 发生变化可以更新，不需要一直重复设置
 @param serviceVendor 地区
 */
+ (void)setServiceVendor:(BDAutoTrackServiceVendor)serviceVendor;

/*! @abstract 设置自定义的URL回调
 @param requestURLBlock 回调block，设置一次即可，不需要多次设置
 @discussion requestURLBlock 会覆盖之前的初始化或者上一次设置的回调，如果为nil会清空回调
 @discussion block在初始化之前 设置一次即可，每次拉取请求都会回调，请勿一直重复设置
 */
+ (void)setRequestURLBlock:(nullable BDAutoTrackRequestURLBlock)requestURLBlock;

/*! @abstract 地区
 @discussion 如果设置过，会保存值，直到下次改变或者清空
 @discussion 如果没有值，默认会读取 `[[NSLocale currentLocale] objectForKey:NSLocaleCountryCode]`
 @discussion 发生变化时候请调用 `+[BDAutoTrack setAppRegion:]`更新值
 */
+ (void)setAppRegion:(nullable NSString *)appRegion;

/*! @abstract 语言
 @discussion 如果设置过，会保存值，直到下次改变或者清空
 @discussion 如果没有值，默认会读取 `[[NSLocale currentLocale] objectForKey:NSLocaleLanguageCode]`
 @discussion 发生变化时候请调用 `+[BDAutoTrack setAppLauguage:]`更新值
 */
+ (void)setAppLauguage:(nullable NSString *)appLauguage;

/*! @abstract 设置注册成功回调
 @param registerFinishBlock id发生变化可能重新触发请求，请求回调。
 @discussion registerFinishBlock 会覆盖之前的初始化或者上一次设置的回调，如果为nil会清空回调
 @discussion block在初始化之前设置一次即可，每次拉取成功都会回调，请勿一直重复设置
 */
+ (void)setRegisterFinishBlock:(nullable BDAutoTrackRegisterFinishBlock)registerFinishBlock;

/*! @abstract 添加自定义上报信息
 @param customHeaderBlock 自定义上报信息
 @discussion customHeaderBlock 一次App启动设置一次即可；App重启需要重新设置，因为SDK不会保存上次设置的值；会覆盖之前的初始化的或者上一次设置的，如果为nil会清空回调
 @discussion block在初始化之前设置一次即可，每次都会回调，不会把block返回参数保存，而导致获取不到变化的值，请勿一直重复设置
 */
+ (void)setCustomHeaderBlock:(nullable BDAutoTrackCustomHeaderBlock)customHeaderBlock;

/*! @abstract 日志上报
 @param event 事件名称，不能为nil或空字符串
 @param params 事件参数。可以为空或者nil，但是param如果非空，需要可序列化成json
 @discussion params 请参考文档中的日志格式要求，或者使用 [NSJSONSerialization isValidJSONObject:] 来检查params是否可序列化
 @result 是否成功，如果失败，则表示此日志不会被上报。原因是无法序列化。
 */
+ (BOOL)eventV3:(NSString *)event params:(nullable NSDictionary *)params;

#pragma mark - ABTest

/*! @abstract 设置注册成功回调
 @param ABTestFinishBlock ABTest配置拉取，请求回调。回调在子线程，不是主线程
 @discussion ABTestFinishBlock 会覆盖之前的初始化或者上一次设置的回调，如果为nil会清空回调
 @discussion block在初始化之前设置一次即可，每次拉取成功都会回调，请勿一直重复设置。此回调会定时回调，并非一次性回调
 */
+ (void)setABTestFinishBlock:(nullable BDAutoTrackABTestFinishBlock)ABTestFinishBlock;

/*! @abstract 手动触发获取ABTest的配置值请求
 @discussion 手动触发请求
 */
+ (void)startFetchABTestConfiguration;

/*! @abstract 获取ABTest的配置值
 @param key ABTest的key
 @param defaultValue 默认值，如果没有配置，或者未开启ABTest则返回默认值
 @discussion 未开启ABTest或者ABTest配置了默认值，都是返回默认值，因此建议监听ABTestFinishBlock来判断是否开启了ABTest
 @result 返回ABTest的配置值
 */
+ (nullable id)ABTestConfigValueForKey:(NSString *)key defaultValue:(nullable id)defaultValue;

/*! @abstract 设置日志上报ABTest属性
 @param versions 设置完versions且ABTest开启的状态下，每条日志都会带上这个属性
 @discussion 和 [BDAutoTrack setABSDKVersions:] 是同一个接口，请改用 [BDAutoTrack setABSDKVersions:]
 */
+ (void)setServerVersions:(nullable NSString *)versions DEPRECATED_MSG_ATTRIBUTE("Use `+[BDAutoTrack setABSDKVersions:]` instead");

/*! @abstract 设置日志上报ABTest属性
@param versions 设置完versions且ABTest开启的状态下，每条日志都会带上这个属性,对应ab_sdk_version字段
*/
+ (void)setABSDKVersions:(nullable NSString *)versions;

/*! @abstract 获取ABTest相关配置
 @result 返回ABTest的abServerVersions值，此值就是之前接口设置进来的
 @discussion 此值不需要设置到上报的event中，SDK会自动给每个event添加
 */
+ (nullable NSString *)abServerVersions;

/*! @abstract 获取ABTest相关配置
@result 返回ABTest的abVersions值
 @discussion 此值不需要设置到上报的event中，SDK会自动给每个event添加
 */
+ (nullable NSString *)abVersions;

#pragma mark - private API

/*! @abstract 调用用户激活接口。一般情况下，请勿调用，除非知晓调用可能的问题。预留给内部CP接口使用
 */
+ (void)activeUser;

@end

NS_ASSUME_NONNULL_END
