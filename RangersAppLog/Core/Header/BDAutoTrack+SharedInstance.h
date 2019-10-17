//
//  BDAutoTrackHolder.h
//  RangersAppLog
//
//  Created by bob on 2019/10/12.
//

#import <Foundation/Foundation.h>
#import "BDAutoTrack.h"
#import "BDAutoTrackConfig.h"

NS_ASSUME_NONNULL_BEGIN


/*! @abstract
BDAutoTrack 里面引用住一个BDAutoTrack单例，是为外部客户提供接口调用。
 特别说明：
    1. 先调用[BDAutoTrack sharedTrackWithConfig:config];
        之后调用BDAutoTrack的其他 类方法接口
    2. 先调用[BDAutoTrack startTrackWithConfig:config];
    之后调用BDAutoTrack的其他 类方法接口

 使用示例1：
     BDAutoTrackConfig *config = [BDAutoTrackConfig new];
     config.xxx = xxx;
     ...
    // 初始化完成之后，可以调用其他接口
    [BDAutoTrack sharedTrackWithConfig:config]

    // 设置一些属性等配置
    [BDAutoTrack setCurrentUserUniqueID:@"123"];

    // 最后启动track
    [BDAutoTrack startTrack]

 使用示例2：
  BDAutoTrackConfig *config = [BDAutoTrackConfig new];
  config.xxx = xxx;
  ...
 // 初始化完成之后，可以调用其他接口
 [BDAutoTrack startTrackWithConfig:config]

 // 设置一些属性等配置
 [BDAutoTrack setCurrentUserUniqueID:@"123"];
 */


#pragma mark - Track

/*! @discussion 设置注册成功和ABTest拉取成功回调，推荐使用通知方法。
@discussion 请参考 <RangersAppLog/BDAutoTrackNotifications.h>注释。
@discussion 建议采用 <RangersAppLog/BDAutoTrack.h> 里面的实例方法接口，类方法接口不推荐使用
*/
@interface BDAutoTrack (SharedInstance)

/*! @abstract
 针对每个AppID 设备唯一device ID. 非数字，随机字符串，一般情况请不要存储，从SDK接口获取即可。
 */
@property (class, nonatomic, copy, readonly, nullable) NSString *deviceID __attribute__((deprecated("过期属性，后续版本可能不会再提供此接口")));;

///*! @abstract
// 针对每个AppID 设备唯一bytedance device ID. 非数字，随机字符串，一般情况请不要存储，从SDK接口获取即可。
// @discussion 针对不同的AppID如果是同一个集团，则有可能是一样的。原来的device ID已经废弃移除
// @discussion 特别说明，bytedanceDeviceID和deviceID不是一个值，可能是不一样的
// */
//@property (class, nonatomic, copy, readonly, nullable) NSString *bytedanceDeviceID;

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
 */
+ (void)sharedTrackWithConfig:(BDAutoTrackConfig *)config;

/*! @abstract 开始埋点和无埋点上报 在初始化之后调用
 @discussion 需要在`[BDAutoTrack sharedTrackWithConfig:]`初始化之后手动调用此方法。调用此方法之前，可以做一些额外的配置
 */
+ (void)startTrack;

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

/*! @abstract 设置注册成功回调
 @param ABTestFinishBlock ABTest配置拉取，请求回调。回调在子线程，不是主线程
 @discussion ABTestFinishBlock 会覆盖之前的初始化或者上一次设置的回调，如果为nil会清空回调
 @discussion block在startTrack 之前 设置一次即可，每次拉取成功都会回调，请勿一直重复设置。此回调会定时回调，并非一次性回调
 @discussion 推荐使用通知，请参考 <RangersAppLog/BDAutoTrackNotifications.h>注释，后续版本可能会移除此block
 */
+ (void)setABTestFinishBlock:(nullable BDAutoTrackABTestFinishBlock)ABTestFinishBlock __attribute__((deprecated("请使用通知来监听回调")));

/*! @abstract 获取ABTest的配置值，在初始化之后设置才能调用
 @param key ABTest的key
 @param defaultValue 默认值，如果没有配置，或者未开启ABTest则返回默认值
 @discussion 未开启ABTest或者ABTest配置了默认值，都是返回默认值，因此建议监听ABTestFinishBlock来判断是否开启了ABTest
 @discussion 通过此接口读取会触发曝光统计
 @discussion 推荐使用通知来监听ABTest配置是否拉取成功，请参考 <RangersAppLog/BDAutoTrackNotifications.h>注释
 @result 返回ABTest的配置值
 */
+ (nullable id)ABTestConfigValueForKey:(NSString *)key defaultValue:(nullable id)defaultValue;

/*! @abstract 设置日志上报ABTest属性，在初始化之后设置才能调用
 @param versions 设置完versions且ABTest开启的状态下，每条日志都会带上这个属性,对应ab_sdk_version字段
 @discussion 原来接口 +[BDAutoTrack setABServerVersions]
*/
+ (void)setABSDKVersions:(nullable NSString *)versions;

/*! @abstract 获取ABTest相关配置，在初始化之后设置才能调用
 @result 返回ABTest的abServerVersions值，此值就是之前setABSDKVersions:接口设置进来的
 @discussion 此值不需要设置到上报的event中，SDK会自动给每个event添加
 */
+ (nullable NSString *)abSDKVersions;

/*! @abstract 获取ABTest相关配置，在初始化之后设置才能调用
@result 返回ABTest的abVersions值
 @discussion 此值不需要设置到上报的event中，SDK会自动给每个event添加
 */
+ (nullable NSString *)abVersions;

/*! @abstract 获取ABTest相关配置，在初始化之后设置才能调用
 @result 返回ABTest的所有的abVersions值
 @discussion 此接口不会触发曝光，可以随意读取
 */
+ (nullable NSString *)allAbVersions;

/*! @abstract 获取ABTest相关配置，在初始化之后设置才能调用
 @result 返回ABTest的所有的Configs值
 @discussion 此接口不会触发曝光，可以随意读取。
 @discussion 如果正常为了做实验，请勿使用此接口，请使用-[BDAutoTrack ABTestConfigValueForKey:defaultValue:]接口
 */
+ (nullable NSDictionary *)allABTestConfigs;

#pragma mark - private API

/*! @abstract 调用用户激活接口，在初始化之后设置才能调用
 一般情况下，请勿调用，除非知晓调用可能的问题。预留给内部CP接口使用
 */
+ (void)activeUser;

@end

#pragma mark - Game

@interface BDAutoTrack (SharedGame)

/*! @abstract 初始化注册
 @param method 注册方式，@"wechat"、@"qq"，强制添加
 @param isSuccess 状态，强制添加
 @discussion 上报参数：@{@"method":method,@"is_success":@(isSuccess)}
 */
+ (void)registerEventByMethod:(NSString *)method
                    isSuccess:(BOOL)isSuccess;

/*! @abstract 初始化登录
 @param method 登录方式，@"wechat"、@"qq"
 @param isSuccess 状态
 @discussion 上报参数：@{@"method":method,@"is_success":@(isSuccess)}
 */
+ (void)loginEventByMethod:(NSString *)method
                 isSuccess:(BOOL)isSuccess;

/*! @abstract 绑定社交账号
 @param type 账号类型
 @param isSuccess 状态
 @discussion 上报参数：@{@"account_type":type,@"is_success":@(isSuccess)}
 */
+ (void)accessAccountEventByType:(NSString *)type
                       isSuccess:(BOOL)isSuccess;

/*! @abstract 进行任务
 @param questID 任务id
 @param type 任务类型
 @param name 教学/任务/副本名
 @param number 第几个任务
 @param desc 其他描述
 @param isSuccess 状态
 @discussion 上报参数：@{@"quest_id":questID,
                     @"quest_type":type,
                     @"quest_name":name,
                     @"quest_no":@(number),
                     @"description":desc,
                     @"is_success":@(isSuccess)}
 */
+ (void)questEventWithQuestID:(NSString *)questID
                    questType:(NSString *)type
                    questName:(NSString *)name
                   questNumer:(NSUInteger)number
                  description:(NSString *)desc
                    isSuccess:(BOOL)isSuccess;

/*! @abstract 升级
 @param level 当前等级
 @discussion 上报参数：@{@"level":@(level)}
 */
+ (void)updateLevelEventWithLevel:(NSUInteger)level;

/*! @abstract 创建角色
 @param roleID 角色id
 @discussion 上报参数：@{@"gamerole_id":roleID}
 */
+ (void)createGameRoleEventByID:(NSString *)roleID;

/*! @abstract 查看内容/商品详情
 @param type 内容类型
 @param name 内容名
 @param contentID 内容id
 @discussion 上报参数：@{@"content_type":type,
                         @"content_name":name,
                         @"content_id":contentID}
 */
+ (void)viewContentEventWithContentType:(NSString *)type
                            contentName:(NSString *)name
                              contentID:(NSString *)contentID;

/*! @abstract 加入购买/购物车
 @param type 内容类型
 @param name 内容名
 @param contentID 内容id
 @param number 内容数量
 @param isSuccess 是否成功
 @discussion 上报参数：@{@"content_type":type,
                     @"content_name":name,
                     @"content_id":contentID,
                     @"content_num":number,
                     @"is_success":@(isSuccess)}
 */
+ (void)addCartEventWithContentType:(NSString *)type
                        contentName:(NSString *)name
                          contentID:(NSString *)contentID
                      contentNumber:(NSUInteger)number
                          isSuccess:(BOOL)isSuccess;

/*! @abstract 提交购买/下单
 @param type 内容类型
 @param name 内容名
 @param contentID 内容id
 @param number 内容数量
 @param isVirtualCurrency 是否使用的是虚拟货币
 @param virtualCurrency 虚拟币币种
 @param currency 真实货币类型
 @param amount 货币金额
 @param isSuccess 是否成功
 @discussion 上报参数：@{@"content_type":type,
                         @"content_name":name,
                         @"content_id":contentID,
                         @"content_num":number,
                         @"is_virtual_currency":@(isVirtualCurrency),
                         @"virtual_currency":virtualCurrency,
                         @"currency":currency,
                         @"is_success":@(isSuccess),
                         @"currency_amount":@(amount)}
 */
+ (void)checkoutEventWithContentType:(NSString *)type
                         contentName:(NSString *)name
                           contentID:(NSString *)contentID
                       contentNumber:(NSUInteger)number
                   isVirtualCurrency:(BOOL)isVirtualCurrency
                     virtualCurrency:(NSString *)virtualCurrency
                            currency:(NSString *)currency
                     currency_amount:(unsigned long long)amount
                           isSuccess:(BOOL)isSuccess;

/*! @abstract 支付
 @param type 内容类型
 @param name 内容名
 @param contentID 内容id
 @param number 内容数量
 @param channel 支付渠道
 @param currency 币种
 @param amount 货币金额，不能为0
 @param isSuccess 是否成功
 @discussion 上报参数：@{@"content_type":type,
                     @"content_name":name,
                     @"content_id":contentID,
                     @"content_num":@(number),
                     @"payment_channel":channel,
                     @"currency":currency,
                     @"is_success":@(isSuccess),
                     @"currency_amount":@(amount)}
 */
+ (void)purchaseEventWithContentType:(NSString *)type
                         contentName:(NSString *)name
                           contentID:(NSString *)contentID
                       contentNumber:(NSUInteger)number
                      paymentChannel:(NSString *)channel
                            currency:(NSString *)currency
                     currency_amount:(unsigned long long)amount
                           isSuccess:(BOOL)isSuccess;

/*! @abstract 添加支付渠道
 @param channel 支付渠道
 @param isSuccess 是否成功
 @discussion 上报参数：@{@"payment_channel":channel,
                        @"is_success":@(isSuccess)}
 */
+ (void)accessPaymentChannelEventByChannel:(NSString *)channel
                                 isSuccess:(BOOL)isSuccess;

/*! @abstract 添加至收藏
 @param type 内容类型
 @param name 内容名
 @param contentID 内容id
 @param number 内容数量
 @param isSuccess 是否成功
 @discussion 上报参数：@{@"content_type":type,
                     @"content_name":name,
                     @"content_id":contentID,
                     @"content_num":@(number),
                     @"is_success":@(isSuccess)}
 */
+ (void)addToFavouriteEventWithContentType:(NSString *)type
                               contentName:(NSString *)name
                                 contentID:(NSString *)contentID
                             contentNumber:(NSUInteger)number
                                 isSuccess:(BOOL)isSuccess;

@end

#pragma mark - GTGame


/*!
 BDAutoTrack 内置联运游戏上报API
 事件名称都有 gt 前缀
 具体参数参照接口人发送的文档
 */
@interface BDAutoTrack (SharedGTGame)

/*! @abstract 用户登录时触发 事件名称 gt_log_in
 @param level 用户等级
 @discussion 最终上报参数 @{@"lev":@(level)}
 */
+ (void)logInEventWithLevel:(NSInteger)level;

/*! @abstract 广告请求：事件名称 gt_ad_request
 @param level 用户等级，作为自定义公共属性（custom_header)上报
 @param type 广告类型：激励视频、插屏、banner等，直接使用汉字或者英文进行标识
 @param position 广告点位：复活、翻倍、试用、buff、奖励道具、新道具、减CD等，直接使用文字或者英文进行标识
 @param reason 广告出现的位置类型：具体的关卡、剧情、界面等，直接使用文字或者英文进行标识
 @param reasonID 广告出现的具体位置：关卡1则使用数字1进行标识，依次类推
 @discussion 触发条件：向服务器请求广告时。穿山甲广告有回调，可以直接获取。
 @discussion 最终上报参数 @{@"lev":@(level),
                        @"ad_type":type,
                        @"ad_position":position,
                        @"ad_reason":reason,
                        @"ad_reasonid":@(reasonID)}
 */
+ (void)adRequestEventWithLevel:(NSInteger)level
                           type:(NSString *)type
                       position:(NSString *)position
                         reason:(NSString *)reason
                       reasonID:(NSInteger)reasonID;

/*! @abstract 广告返回：gt_ad_send
 @param level 用户等级，作为自定义公共属性（custom_header)上报
 @param type 广告类型：激励视频、插屏、banner等，直接使用汉字或者英文进行标识
 @param position 广告点位：复活、翻倍、试用、buff、奖励道具、新道具、减CD等，直接使用文字或者英文进行标识
 @param reason 广告出现的位置类型：具体的关卡、剧情、界面等，直接使用文字或者英文进行标识
 @param reasonID 广告出现的具体位置：关卡1则使用数字1进行标识，依次类推
 @discussion 触发条件：服务器推送广告成功时。穿山甲广告有回调，可以直接获取。
 @discussion 上报参数： @{@"lev":@(level),
                    @"ad_type":type,
                    @"ad_position":position,
                    @"ad_reason":reason,
                    @"ad_reasonid":@(reasonID)}
 */
+ (void)adSendEventWithLevel:(NSInteger)level
                        type:(NSString *)type
                    position:(NSString *)position
                      reason:(NSString *)reason
                    reasonID:(NSInteger)reasonID;

/*! @abstract 广告位按钮展示：gt_ad_button_show
 @param level 用户等级，作为自定义公共属性（custom_header)上报
 @param type 广告类型：激励视频、插屏、banner等，直接使用汉字或者英文进行标识
 @param position 广告点位：复活、翻倍、试用、buff、奖励道具、新道具、减CD等，直接使用文字或者英文进行标识
 @param reason 广告出现的位置类型：具体的关卡、剧情、界面等，直接使用文字或者英文进行标识
 @param reasonID 广告出现的具体位置：关卡1则使用数字1进行标识，依次类推
 @discussion 触发条件：用户点击app内各广告位button时。
 @discussion 上报参数：@{@"lev":@(level),
                     @"ad_type":type,
                     @"ad_position":position,
                     @"ad_reason":reason,
                     @"ad_reasonid":@(reasonID)}
 */
+ (void)adButtonclickEventWithLevel:(NSInteger)level
                               type:(NSString *)type
                           position:(NSString *)position
                             reason:(NSString *)reason
                           reasonID:(NSInteger)reasonID;

/*! @abstract 广告展示：gt_ad_show
 @param level 用户等级，作为自定义公共属性（custom_header)上报
 @param type 广告类型：激励视频、插屏、banner等，直接使用汉字或者英文进行标识
 @param position 广告点位：复活、翻倍、试用、buff、奖励道具、新道具、减CD等，直接使用文字或者英文进行标识
 @param reason 广告出现的位置类型：具体的关卡、剧情、界面等，直接使用文字或者英文进行标识
 @param reasonID 广告出现的具体位置：关卡1则使用数字1进行标识，依次类推
 @discussion 触发条件：用户点击并观看广告时。穿山甲广告有回调，可以直接获取。
 @discussion 上报参数：@{@"lev":@(level),
                     @"ad_type":type,
                     @"ad_position":position,
                     @"ad_reason":reason,
                     @"ad_reasonid":@(reasonID)}
 */
+ (void)adShowEventWithLevel:(NSInteger)level
                        type:(NSString *)type
                    position:(NSString *)position
                      reason:(NSString *)reason
                    reasonID:(NSInteger)reasonID;

/*! @abstract 升级和经验：gt_levelup
 @param level 用户等级，作为自定义公共属性（custom_header)上报
 @param exp 获得经验
 @param method 获得经验途径：闯关成功、引导完成、领取奖励等，使用汉字或者英文进行标识
 @param afterLevel 用户获得经验后等级，如获得经验未导致升级，则lev=aflev，如导致升级，则lev<aflev
 @discussion 触发条件：用户获得经验或者等级发生变化时。
 @discussion 上报参数：@{@"lev":@(level),
                     @"get_exp":@(exp),
                     @"method":method,
                     @"aflev":@(afterLevel)}
 */
+ (void)levelUpEventWithLevel:(NSInteger)level
                          exp:(NSInteger)exp
                       method:(NSString *)method
                   afterLevel:(NSInteger)afterLevel;

/*! @abstract 引导：gt_guide
 @param level 用户等级，作为自定义公共属性（custom_header)上报
 @param guideID 新手引导的步骤：例如新手引导的第2步，则用2标识，使用数字标识引导内容的顺序
 @param guideName 新手引导内容：例如：“点击开始按钮”，“切换到首页”等，使用文字或者英文进行标识
 @discussion 触发条件：用户完成对应新手引导时。
 @discussion 上报参数：@{@"lev":@(level),
                     @"guide_id":@(guideID),
                     @"guide_name":guideName}
 */
+ (void)guideEventWithLevel:(NSInteger)level
                    guideID:(NSInteger)guideID
                  guideName:(NSString *)guideName;

/*! @abstract 活动奖励：gt_activity
 @param level 用户等级，作为自定义公共属性（custom_header)上报
 @param activityName 具体活动名称： 端午节活动，情人节活动等，使用文字或者英文进行标识
 @param rewardType 奖励的类型：节日奖励、签到奖励等，使用文字或者英文进行标识
 @param rewardName 奖励的名称：金币、道具、服装等，使用文字或者英文进行标识
 @param method 获得奖励的途径：完成节日任务、达成XX成就，使用文字或者英文进行标识
 @discussion 触发条件：用户参与活动并且获得活动奖励时。
 @discussion 上报参数： @{@"lev":@(level),
                     @"activity_name":activityName,
                     @"reward_type":rewardType,
                     @"reward_name":rewardName,
                     @"method":method}
 */
+ (void)activityEventWithLevel:(NSInteger)level
                  activityName:(NSString *)activityName
                    rewardType:(NSString *)rewardType
                    rewardName:(NSString *)rewardName
                        method:(NSString *)method;

/*! @abstract 开始玩法：gt_start_play
 @param level 用户等级，作为自定义公共属性（custom_header)上报
 @param ecTypeType 玩法类型：休闲模式、竞技模式
 @param ecTypeID 具体的玩法ID，如果是闯关性质的玩法，使用连续数字标识关卡的顺序
 @discussion 触发条件：用户开始玩法时。
 @discussion 上报参数：@{@"lev":@(level),
                     @"ectype_type":ecTypeType,
                     @"ectype_id":@(ecTypeID)}
 */
+ (void)startPlayEventWithLevel:(NSInteger)level
                     ecTypeType:(NSString *)ecTypeType
                       ecTypeID:(NSInteger)ecTypeID;

/*! @abstract 结束玩法：gt_end_play
 @param level 用户等级，作为自定义公共属性（custom_header)上报
 @param ecTypeType 玩法类型：休闲模式、竞技模式。 如游戏中只有一种玩法模式，该属性不上报
 @param ecTypeID 具体的玩法ID，如果是闯关性质的玩法，使用连续数字标识关卡的顺序
 @param result 玩法的结果：未完成、成功、失败等，使用英文进行标识.  未完成标记为uncompleted, 成功标记为success，失败为fail
 @param score 获得分数或者星级，如玩法中没有输出，该属性可不上报
 @param duration 消耗时间，单位秒
 @param killNum 击杀数量，如玩法中没有输出，则为空
 @param passed 曾经是否通关过，曾经通关过记为 yes，曾经未通关过记为 no. 如果游戏内没有首次通过概念，默认passed = no
 @discussion 触发条件：用户结束玩法时，涵盖中途退出、完成但失败和完成且成功。
 @discussion 上报参数：@{@"lev":@(level),
                     @"ectype_type":ecTypeType,
                     @"ectype_id":@(ecTypeID),
                     @"result":result,
                     @"score":@(score),
                     @"time":@(duration),
                     @"kill_num":@(killNum),
                     @"passed":passed}
 */
+ (void)endPlayEventWithLevel:(NSInteger)level
                   ecTypeType:(NSString *)ecTypeType
                     ecTypeID:(NSInteger)ecTypeID
                       result:(NSString *)result
                        score:(NSInteger)score
                     duration:(NSInteger)duration
                      killNum:(NSInteger)killNum
                       passed:(NSString *)passed;

/*! @abstract 复活：gt_revive
 @param level 用户等级，作为自定义公共属性（custom_header)上报
 @param ecTypeType 玩法类型：休闲模式、竞技模式
 @param ecTypeID 具体的玩法ID，如果是闯关性质的玩法，使用连续数字标识关卡的顺序
 @param method 用户复活的途径：观看激励视频、使用金币等，使用文字或者英文进行标识
 @discussion 触发条件：用户死亡后成功复活时。
 @discussion 上报参数：@{@"lev":@(level),
                     @"ectype_type":ecTypeType,
                     @"ectype_id":@(ecTypeID),
                     @"method":method}
 */
+ (void)reviveEventWithWithLevel:(NSInteger)level
                      ecTypeType:(NSString *)ecTypeType
                        ecTypeID:(NSInteger)ecTypeID
                          method:(NSString *)method;

/*! @abstract 获得游戏币：gt_get_coins
 @param level 用户等级，作为自定义公共属性（custom_header)上报
 @param coinType 货币类型：元宝、绑元、金币、银币等，使用文字或者英文进行标识
 @param method 获得途径：观看激励视频、闯关成功、活动奖励等，使用文字或者英文进行标识
 @param coinNum 获得数量
 @param coinLeft 获得货币之后，用户身上剩余的货币数量
 @discussion 触发条件：用户获得游戏币，导致游戏币增加时。
 @discussion 上报参数：@{@"lev":@(level),
                     @"coin_type":coinType,
                     @"method":method,
                     @"coin_num":@(coinNum),
                     @"coin_left":@(coinLeft)}
 */
+ (void)getCoinsEventWithLevel:(NSInteger)level
                    coinType:(NSString *)coinType
                        method:(NSString *)method
                       coinNum:(NSInteger)coinNum
                      coinLeft:(NSInteger)coinLeft;

/*! @abstract 消耗游戏币：gt_cost_coins
 @param level 用户等级，作为自定义公共属性（custom_header)上报
 @param coinType 货币类型：元宝、绑元、金币、银币等，使用文字或者英文进行标识
 @param method 消耗途径：观看激励视频、闯关成功、活动奖励等，使用文字或者英文进行标识
 @param coinNum 消耗数量
 @param coinLeft 消耗货币之后，用户身上剩余的货币数量
 @discussion 触发条件：用户消耗游戏币，导致游戏币减少时。
 @discussion 上报参数：@{@"lev":@(level),
                     @"coin_type":coinType,
                     @"method":method,
                     @"coin_num":@(coinNum),
                     @"coin_left":@(coinLeft)}
 */
+ (void)costCoinsEventWithLevel:(NSInteger)level
                       coinType:(NSString *)coinType
                         method:(NSString *)method
                        coinNum:(NSInteger)coinNum
                       coinLeft:(NSInteger)coinLeft;

/*! @abstract 获得物品：gt_get_item
 @param level 用户等级，作为自定义公共属性（custom_header)上报
 @param itemType 物品类型：经验道具、服装、皮肤等，使用文字或者英文进行标识
 @param itemName 物品名称：经验*100、节日服装等，使用文字或者英文进行标识
 @param method 获得途径：商城购买、活动奖励、闯关成功等，使用文字或者英文进行标识
 @param itemNum 获得数量
 @discussion 触发条件：用户获得物品，导致物品增加时。
 @discussion 上报参数：@{@"lev":@(level),
                     @"item_type":itemType,
                     @"item_name":itemName,
                     @"method":method,
                     @"item_num":@(itemNum)}
 */
+ (void)getItemEventWithLevel:(NSInteger)level
                     itemType:(NSString *)itemType
                     itemName:(NSString *)itemName
                       method:(NSString *)method
                      itemNum:(NSInteger)itemNum;

/*! @abstract 消耗物品：gt_cost_item
 @param level 用户等级，作为自定义公共属性（custom_header)上报
 @param itemType 物品类型：经验道具、服装、皮肤等，使用文字或者英文进行标识
 @param itemName 物品名称：经验*100、节日服装等，使用文字或者英文进行标识
 @param method 消耗途径：复活、解锁关卡等，使用文字或者英文进行标识
 @param itemNum 消耗数量
 @discussion 触发条件：用户消耗物品，导致物品减少时。
 @discussion 上报参数：@{@"lev":@(level),
                     @"item_type":itemType,
                     @"item_name":itemName,
                     @"method":method,
                     @"item_num":@(itemNum)}
 */
+ (void)costItemEventWithLevel:(NSInteger)level
                      itemType:(NSString *)itemType
                      itemName:(NSString *)itemName
                        method:(NSString *)method
                       itemNum:(NSInteger)itemNum;

/*! @abstract 商城：gt_shoptrade
 @param level 用户等级，作为自定义公共属性（custom_header)上报
 @param shopType 商店类型：摆摊商城、特价商城等，使用文字或者英文进行标识
 @param itemType 物品类型：经验道具、服装、皮肤等，使用文字或者英文进行标识
 @param itemName 物品名称：经验*100、节日服装等，使用文字或者英文进行标识
 @param itemNum 购买数量
 @param coinType 货币类型：元宝、绑元、金币、银币等，使用文字或者英文进行标识
 @param coinNum 消耗数量
 @discussion 触发条件：用户在商城购买完成时。
 @discussion 上报参数：@{@"lev":@(level),
                     @"shop_type":shopType,
                     @"item_type":itemType,
                     @"item_name":itemName,
                     @"item_num":@(itemNum),
                     @"coin_type":coinType,
                     @"coin_num":@(coinNum)}
 */
+ (void)shopTradeEventWithLevel:(NSInteger)level
                       shopType:(NSString *)shopType
                       itemType:(NSString *)itemType
                       itemName:(NSString *)itemName
                        itemNum:(NSInteger)itemNum
                       coinType:(NSString *)coinType
                        coinNum:(NSInteger)coinNum;

/*! @abstract 分享点击：gt_share_click
 @param level 用户等级，作为自定义公共属性（custom_header)上报
 @param shareType 分享的内容：录屏、截图，使用文字或者英文进行标识
 @param shareMedia 分享目标媒体：抖音，使用文字或者英文进行标识
 @discussion 触发条件：用户点击分享按钮时。
 @discussion 上报参数：@{@"lev":@(level),
                     @"share_type":shareType,
                     @"share_media":shareMedia}
 */
+ (void)shareClickEventWithLevel:(NSInteger)level
                       shareType:(NSString *)shareType
                      shareMedia:(NSString *)shareMedia;

/*! @abstract 分享结果：gt_share_result
 @param level 用户等级，作为自定义公共属性（custom_header)上报
 @param shareType 分享的内容：录屏、截图，使用文字或者英文进行标识
 @param shareMedia 分享目标媒体：抖音，使用文字或者英文进行标识
 @param result 分享的结果：未完成、成功、失败等，使用文字或者英文进行标识
 @discussion 触发条件：用户完成分享时，涵盖：中途退出未完成、完成但分享失败、完成并成功。
 @discussion 上报参数：@{@"lev":@(level),
                     @"share_type":shareType,
                     @"share_media":shareMedia,
                     @"result":result}
 */
+ (void)shareResultEventWithLevel:(NSInteger)level
                        shareType:(NSString *)shareType
                       shareMedia:(NSString *)shareMedia
                           result:(NSString *)result;

/*! @abstract 主路径转化：gt_module_conversion
 @param level 用户等级，作为自定义公共属性（custom_header)上报
 @param moduleID 主路径id
 @param moduleName 主路径步骤描述，使用文字或者英文进行标识
 @discussion 触发条件：用户在发生主路径行为时触发，主路径比如：初始化、登陆前、登陆后、主界面显示
 */
+ (void)moduleConversionEventWithLevel:(NSInteger)level
                              moduleID:(NSInteger)moduleID
                            moduleName:(NSString *)moduleName;

/*! @abstract 充值相关：gt_addcash
 @param level 用户等级，作为自定义公共属性（custom_header)上报
 @param addType 充值的类型：直充、礼包1、礼包2、礼包3
 @param cash 充值的金额，单位分
 @param coinType 获得货币的类型
 @param coinNum 充值获得数量
 @param itemName 获得物品的名称：经验*100、节日服装等，使用文字或者英文进行标识
 @param itemNum 充值获得物品的数量
 @discussion 触发条件：用户完成充值并获得对应的游戏内货币和道具时
 */
+ (void)addCashEventWithLevel:(NSInteger)level
                      addType:(NSString *)addType
                         cash:(NSInteger)cash
                     coinType:(NSString *)coinType
                      coinNum:(NSInteger)coinNum
                     itemName:(NSString *)itemName
                      itemNum:(NSInteger)itemNum;

@end

#pragma mark - Special

@interface BDAutoTrack (SharedSpecial)

+ (BOOL)eventV3:(NSString *)event params:(nullable NSDictionary *)params specialParams:(NSDictionary *)specialParams;

+ (BOOL)customEvent:(NSString *)category params:(NSDictionary *)params;

@end

NS_ASSUME_NONNULL_END
