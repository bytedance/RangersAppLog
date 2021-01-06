//
//  BDAutoTrack+SharedInstance.h
//  Pods
//
//  Created by 朱元清 on 2020/9/11.
//

#import <Foundation/Foundation.h>
#import "BDCommonDefine.h"

NS_ASSUME_NONNULL_BEGIN
/// 以下是单例方法
#pragma mark - SharedInstance

/*! @abstract
BDAutoTrack 里面引用住一个BDAutoTrack单例，方便通过类名来调用SDK方法。
特别说明：先调用`[BDAutoTrack startTrackWithConfig:config];`再调用BDAutoTrack的其他 类方法接口

使用示例：
BDAutoTrackConfig *config = [BDAutoTrackConfig new];
config.xxx = xxx;
...
// 初始化
[BDAutoTrack startTrackWithConfig:config]

// 初始化完成之后，再调用其他接口进一步设置user unique ID等属性
[BDAutoTrack setCurrentUserUniqueID:@"123"];
*/

/*! @discussion 设置注册成功和ABTest拉取成功回调，推荐使用通知方法。可以参考 <RangersAppLog/BDAutoTrackNotifications.h>注释。
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

#pragma mark - 初始化与启动单例
/*!
 * @abstract 初始化并启动SDK单例。
 * @param config 配置对象。其中AppID AppName Channel是必须的。
 * @discussion
 * 调用时机:
 *    1、必须在应用启动时调用，即在 application:didFinishLaunchingWithOptions: 中调用，
 *    2、必须在主线程中调用
 *    3、必须在 SDK 其他方法调用之前调用
 * 本方法是一个便捷方法，相当于下面两个调用:
 * @code
 * [BDAutoTrack sharedTrackWithConfig:config];
 * [BDAutoTrack startTrack];
*/
+ (void)startTrackWithConfig:(BDAutoTrackConfig *)config;

/*!
 * @abstract 初始化单例。
 * @param config 配置对象。其中AppID AppName Channel是必须的。
 * @discussion
 * 调用时机:
 *    1、必须在应用启动时调用，即在 application:didFinishLaunchingWithOptions: 中调用，
 *    2、必须在主线程中调用
 *    3、必须在 SDK 其他方法调用之前调用
 * 一般与`+ [BDAutoTrack startTrack]`一起使用。
 * @code
 * [BDAutoTrack sharedTrackWithConfig:config];
 * [BDAutoTrack startTrack];
 */
+ (void)sharedTrackWithConfig:(BDAutoTrackConfig *)config;

/*!
 * @abstract 启动SDK单例。
 * @discussion
 * 调用时机:
 *    1、必须在应用启动时调用，即在 application:didFinishLaunchingWithOptions: 中调用，
 *    2、必须在主线程中调用
 *    3、必须在 SDK 其他方法调用之前调用
 */
+ (void)startTrack;

/**
 * @abstract
 * 若已初始化，则返回之前初始化好的单例；否则返回nil。（本身不会做初始化）
 *
 * @discussion
 * 调用这个方法之前，必须先调用 `+ [BDAutoTrack sharedTrackWithConfig:]`
 *
 * @return 返回之前初始化好的单例
 */
+ (instancetype)sharedTrack;

#pragma mark -
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

/*! @abstract 重新发起注册请求
 @discussion v5.6.3 提供的新接口
 @discussion
 SDK在以下情况会自动调用此方法:
 1. 初始化阶段
 2. 用户通过`setServiceVendor:`方法更改serviceVendor
 3. 用户通过`setCurrentUserUniqueID:`更改userUniqueID
 
 @discussion 用户一般可在以下情况手动调用此方法:
 1. 初始化阶段注册请求失败，需要重新发起注册请求
 */
+ (void)sendRegisterRequest APPLOG_API_AVALIABLE(5.6.3);

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

/*! @abstract 设置自定义的URL回调
 @param requestHostBlock 回调block，设置一次即可，不需要多次设置
 @discussion requestHostBlock 会覆盖之前的初始化或者上一次设置的回调，如果为nil会清空回调
 @discussion requestURLBlock会优先于requestHostBlock
 */
+ (void)setRequestHostBlock:(nullable BDAutoTrackRequestHostBlock)requestHostBlock;

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

/*! @abstract 用户触点 在初始化之后设置
@discussion 如果设置过，会保存值，直到下次改变或者清空
@discussion 如果没有值，或值为空字符串，则不会上报
@discussion 发生变化时候请调用 `+[BDAutoTrack setAppTouchPoint:]`更新值
*/
+ (void)setAppTouchPoint:(NSString *)appTouchPoint;

/**
 @abstract 添加自定义上报信息
 @param value 自定义上报value，一般需要传NSString或者数字，或者nil
 @param key 自定义上报key
 @discussion customHeaderBlock 的SDK不会持久化，下面两个接口，SDK会持久化
 
 /// 新增或者修改，仅发生变化的时候使用
 [BDAutoTrack setCustomHeaderValue:@"male" forKey:@"gender"];
 [BDAutoTrack setCustomHeaderValue:@(29) forKey:@"age"];

 /// 删除
 [BDAutoTrack removeCustomHeaderValueForKey:@"gender"];
 [BDAutoTrack removeCustomHeaderValueForKey:@"age"];
 */
+ (void)setCustomHeaderValue:(nullable id)value forKey:(NSString *)key;
+ (void)removeCustomHeaderValueForKey:(NSString *)key;

/*! @abstract 添加自定义上报信息
 @param customHeaderBlock 自定义上报信息
 @discussion customHeaderBlock 一次App启动设置一次即可；App重启需要重新设置，因为SDK不会保存上次设置的值；会覆盖之前的初始化的或者上一次设置的，如果为nil会清空回调
 @discussion block在初始化之后设置一次即可，每次都会回调，不会把block返回参数保存，而导致获取不到变化的值，请勿一直重复设置
 
  [BDAutoTrack setCustomHeaderBlock:^NSDictionary<NSString *,id> * _Nonnull{
     return @{@"gender":[UserInfo GetGender],
            @"age":@([UserInfo GetAge]),
            };
  }];
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

/*! @abstract 获取ABTest 额外的vids
@param versions 额外的vids。格式比如 @"1,2,3"。是逗号（英文）分割，逗号之间是数字
@discussion 如果要清空上次设置，直接传nil；每次设置都会覆盖上次设置
*/
+ (void)setExternalABVersion:(nullable NSString *)versions;

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

#pragma mark - main app only

/*! @abstract 主动触发上报。SDK有频率限制，每10s最多可以触发一次
*/
+ (void)flush;

#pragma mark - private API

/*! @abstract 调用用户激活接口，在初始化之后设置才能调用
 一般情况下，请勿调用，除非知晓调用可能的问题
 */
+ (void)activeUser;

@end

NS_ASSUME_NONNULL_END
