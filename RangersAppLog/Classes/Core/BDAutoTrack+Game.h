//
//  BDAutoTrack+Game.h
//  Applog
//
//  Created by bob on 2019/4/10.
//

#import "BDAutoTrack.h"

NS_ASSUME_NONNULL_BEGIN

FOUNDATION_EXTERN NSString * const kBDAGameLevel;

/*!
 BDAutoTrack 内置游戏上报API
 */
@interface BDAutoTrack (Game)

/*! @abstract 初始化注册
 @param method 注册方式，@"wechat"、@"qq"，强制添加
 @param isSuccess 状态，强制添加
 @discussion 上报参数：@{@"method":method,@"is_success":@(isSuccess)}
 */
- (void)registerEventByMethod:(NSString *)method
                    isSuccess:(BOOL)isSuccess;

/*! @abstract 初始化登录
 @param method 登录方式，@"wechat"、@"qq"
 @param isSuccess 状态
 @discussion 上报参数：@{@"method":method,@"is_success":@(isSuccess)}
 */
- (void)loginEventByMethod:(NSString *)method
                 isSuccess:(BOOL)isSuccess;

/*! @abstract 绑定社交账号
 @param type 账号类型
 @param isSuccess 状态
 @discussion 上报参数：@{@"account_type":type,@"is_success":@(isSuccess)}
 */
- (void)accessAccountEventByType:(NSString *)type
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
- (void)questEventWithQuestID:(NSString *)questID
                    questType:(NSString *)type
                    questName:(NSString *)name
                   questNumer:(NSUInteger)number
                  description:(NSString *)desc
                    isSuccess:(BOOL)isSuccess;

/*! @abstract 升级
 @param level 当前等级
 @discussion 上报参数：@{@"level":@(level)}
 */
- (void)updateLevelEventWithLevel:(NSUInteger)level;

/*! @abstract 创建角色
 @param roleID 角色id
 @discussion 上报参数：@{@"gamerole_id":roleID}
 */
- (void)createGameRoleEventByID:(NSString *)roleID;

/*! @abstract 查看内容/商品详情
 @param type 内容类型
 @param name 内容名
 @param contentID 内容id
 @discussion 上报参数：@{@"content_type":type,
                         @"content_name":name,
                         @"content_id":contentID}
 */
- (void)viewContentEventWithContentType:(NSString *)type
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
- (void)addCartEventWithContentType:(NSString *)type
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
- (void)checkoutEventWithContentType:(NSString *)type
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
- (void)purchaseEventWithContentType:(NSString *)type
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
- (void)accessPaymentChannelEventByChannel:(NSString *)channel
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
- (void)addToFavouriteEventWithContentType:(NSString *)type
                               contentName:(NSString *)name
                                 contentID:(NSString *)contentID
                             contentNumber:(NSUInteger)number
                                 isSuccess:(BOOL)isSuccess;

@end


/*!
 特别说明：
    先调用[BDAutoTrack startTrackWithConfig:config];
    之后调用BDAutoTrack的游戏埋点接口
*/

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


NS_ASSUME_NONNULL_END
