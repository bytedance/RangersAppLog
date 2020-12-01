//
//  BDAutoTrack- GameTrack.h
//  Applog
//
//  Created by bob on 2019/7/17.
//

#import "BDAutoTrack.h"

NS_ASSUME_NONNULL_BEGIN
/*!
 BDAutoTrack 增加多实例支持
 使用示例1：
  BDAutoTrackConfig *config = [BDAutoTrackConfig new];
  config.xxx = xxx;
  ...
 // 初始化完成之后，可以调用其他接口
 BDAutoTrack *track = [BDAutoTrack trackWithConfig:config]

 // 开始上报
 [track satrtTrack];

 // 用变量引用住track用于上报
 [track logInEventWithLevel:xxx];
 事件参数level的key，保持参数一致
 可以这样使用来设置Header
 [self getCurrentLevel]返回一个当前level的函数
 此header的block设置一次即可，每次会回调。

 [track setCustomHeaderBlock:^NSDictionary<NSString *,id> * _Nonnull{
    return @{kGTGameParameterLevel:@([self getCurrentLevel])};
 }];
 */
FOUNDATION_EXTERN NSString * const kGTGameParameterLevel;

/*!
 BDAutoTrack 内置联运游戏上报API
 事件名称都有 gt 前缀
 具体参数参照接口人发送的文档
 */
@interface BDAutoTrack (GameTrack)

#pragma mark - AD
/**
 广告按钮点击：gt_ad_button_click
 ad_type     string  广告类型：激励视频、插屏、banner等，直接使用汉字或者英文进行标识
 ad_position_type  string  广告点位类型：按照提供分类接入
 ad_position string  广告点位：复活、翻倍、试用、buff、奖励道具、新道具、减CD等，直接使用文字或者英文进行标识
 触发条件：用户点击app内各广告位button时。
 */
- (void)adButtonClickEventWithADType:(NSString *)adType
                        positionType:(NSString *)positionType
                            position:(NSString *)position
                         otherParams:(nullable NSDictionary *)otherParams;

/**
 广告开始展示：gt_ad_show
 ad_type           string  广告类型：激励视频、插屏、banner等，直接使用汉字或者英文进行标识
 ad_position_type  string  广告点位类型：按照提供分类接入
 ad_position       string  广告点位：复活、翻倍、试用、buff、奖励道具、新道具、减CD等，直接使用文字或者英文进行标识
 触发条件：用户点击并观看广告时。穿山甲广告有回调，可以直接获取。
 */
- (void)adShowEventWithADType:(NSString *)adType
                 positionType:(NSString *)positionType
                     position:(NSString *)position
                  otherParams:(nullable NSDictionary *)otherParams;


/**
 广告结束展示：gt_ad_show_end
 ad_type           string  广告类型：激励视频、插屏、banner等，直接使用汉字或者英文进行标识
 ad_position_type  string  广告点位类型：按照提供分类接入
 ad_position       string  广告点位：复活、翻倍、试用、buff、奖励道具、新道具、减CD等，直接使用文字或者英文进行标识
 result            string  广告观看结果：跳过、成功、失败等，使用英文进行标识.  跳过标记为skip, 成功标记为success，失败为fail
 触发条件：用户观看广告结束时。
 */
- (void)adShowEndEventWithADType:(NSString *)adType
                    positionType:(NSString *)positionType
                        position:(NSString *)position
                          result:(NSString *)result
                     otherParams:(nullable NSDictionary *)otherParams;

#pragma mark - Level
/**
 （总等级）升级和经验：gt_levelup
 lev             int 当前玩家等级
 get_exp     int 获得经验
 method      string  获得经验途径：闯关成功、引导完成、领取奖励等，使用汉字或者英文进行标识
 aflev          int 用户获得经验后等级，如获得经验未导致升级，则lev=aflev，如导致升级，则lev<aflev
 触发条件：用户获得经验或者等级发生变化时。
 */
- (void)levelUpEventWithLevel:(NSInteger)level
                          exp:(NSInteger)exp
                       method:(NSString *)method
                   afterLevel:(NSInteger)afterLevel
                  otherParams:(nullable NSDictionary *)otherParams;

#pragma mark - play

/**
 开始玩法：gt_start_play
 ectype_name string  针对闯关性质玩法，标注关卡名称
 触发条件：用户开始玩法时。
 */
- (void)startPlayEventWithName:(NSString *)ecTypeName
                   otherParams:(nullable NSDictionary *)otherParams;

/**
 结束玩法：gt_end_play
 ectype_name string  针对闯关性质玩法，标注关卡名称
 result      string  玩法的结果：未完成、成功、失败等，使用英文进行标识.  未完成标记为uncompleted, 成功标记为success，失败为fail
 duration    int 消耗时间，单位秒
 触发条件：用户结束玩法时，涵盖中途退出、完成但失败和完成且成功。
 */
- (void)endPlayEventWithName:(NSString *)ecTypeName
                      result:(NSString *)result
                     duration:(NSInteger)duration
                  otherParams:(nullable NSDictionary *)otherParams;

#pragma mark - coins

/**
 获得游戏币：gt_get_coins
 coin_type    string    货币类型：元宝、绑元、金币、银币等，使用文字或者英文进行标识
 method    string    获得途径：观看激励视频、闯关成功、活动奖励等，使用文字或者英文进行标识
 coin_num    int    获得数量
 触发条件：用户获得游戏币，导致游戏币增加时
 */
- (void)getCoinsEventWitType:(NSString *)coinType
                      method:(NSString *)method
                  coinNumber:(NSInteger)number
                 otherParams:(nullable NSDictionary *)otherParams;

/**
 消耗游戏币：gt_cost_coins
 coin_type    string    货币类型：元宝、绑元、金币、银币等，使用文字或者英文进行标识
 method    string    消耗途径：复活、购买道具、解锁关卡等，使用文字或者英文进行标识
 coin_num    int    消耗数量
 触发条件：用户消耗游戏币，导致游戏币减少时。
 */
- (void)costCoinsEventWitType:(NSString *)coinType
                       method:(NSString *)method
                   coinNumber:(NSInteger)number
                  otherParams:(nullable NSDictionary *)otherParams;

#pragma mark - Purchase

/**
 内购充值相关：purchase
 content_type  string  内购充值内容类型
 content_name  string  内购充值内容名称
 content_id    string  内购充值内容id
 content_num   int 内购充值内容的数量
 payment_channel string  支付渠道：例如 支付宝，微信等
 currency      string  支付货币类型
 is_success    string  支付是否成功
 currency_amount int 支付的金额，单位元
 触发条件：用户完成内购充值并获得对应的游戏内货币和道具时
 */
- (void)purchaseEventWithContentType:(NSString *)contentType
                         contentName:(NSString *)contentName
                           contentID:(NSString *)contentID
                          contentNum:(NSInteger)contentNum
                             channel:(NSString *)channel
                            currency:(NSString *)currency
                           isSuccess:(NSString *)isSuccess
                      currencyAmount:(NSInteger)currencyAmount
                         otherParams:(nullable NSDictionary *)otherParams;

#pragma mark - InitInfo
/**
 初始化信息：gt_init_info
 lev    int    玩家等级
 coin_type    string    获得货币的类型
 coin_left    int    用户身上剩余的货币数量
 role_id    string    玩家角色id-cp侧
 触发条件：用户启动游戏，初始化完成时上报
 */
- (void)gameInitInfoEventWithLevel:(NSInteger)level
                          coinType:(NSString *)coinType
                          coinLeft:(NSInteger)coinLeft
                       otherParams:(nullable NSDictionary *)otherParams;

@end


/*!
 BDAutoTrack 内置联运游戏上报API
 事件名称都有 gt 前缀
 具体参数参照接口人发送的文档
 */

/*!
 特别说明：
    先调用[BDAutoTrack startTrackWithConfig:config];
    之后调用BDAutoTrack的游戏埋点接口
*/
@interface BDAutoTrack (SharedGameTrack)

#pragma mark - AD
/**
 广告按钮点击：gt_ad_button_click
 ad_type     string  广告类型：激励视频、插屏、banner等，直接使用汉字或者英文进行标识
 ad_position_type  string  广告点位类型：按照提供分类接入
 ad_position string  广告点位：复活、翻倍、试用、buff、奖励道具、新道具、减CD等，直接使用文字或者英文进行标识
 触发条件：用户点击app内各广告位button时。
 */
+ (void)adButtonClickEventWithADType:(NSString *)adType
                        positionType:(NSString *)positionType
                            position:(NSString *)position
                         otherParams:(nullable NSDictionary *)otherParams;

/**
 广告开始展示：gt_ad_show
 ad_type           string  广告类型：激励视频、插屏、banner等，直接使用汉字或者英文进行标识
 ad_position_type  string  广告点位类型：按照提供分类接入
 ad_position       string  广告点位：复活、翻倍、试用、buff、奖励道具、新道具、减CD等，直接使用文字或者英文进行标识
 触发条件：用户点击并观看广告时。穿山甲广告有回调，可以直接获取。
 */
+ (void)adShowEventWithADType:(NSString *)adType
                 positionType:(NSString *)positionType
                     position:(NSString *)position
                  otherParams:(nullable NSDictionary *)otherParams;


/**
 广告结束展示：gt_ad_show_end
 ad_type           string  广告类型：激励视频、插屏、banner等，直接使用汉字或者英文进行标识
 ad_position_type  string  广告点位类型：按照提供分类接入
 ad_position       string  广告点位：复活、翻倍、试用、buff、奖励道具、新道具、减CD等，直接使用文字或者英文进行标识
 result            string  广告观看结果：跳过、成功、失败等，使用英文进行标识.  跳过标记为skip, 成功标记为success，失败为fail
 触发条件：用户观看广告结束时。
 */
+ (void)adShowEndEventWithADType:(NSString *)adType
                    positionType:(NSString *)positionType
                        position:(NSString *)position
                          result:(NSString *)result
                     otherParams:(nullable NSDictionary *)otherParams;

#pragma mark - Level
/**
 （总等级）升级和经验：gt_levelup
 lev             int 当前玩家等级
 get_exp     int 获得经验
 method      string  获得经验途径：闯关成功、引导完成、领取奖励等，使用汉字或者英文进行标识
 aflev          int 用户获得经验后等级，如获得经验未导致升级，则lev=aflev，如导致升级，则lev<aflev
 触发条件：用户获得经验或者等级发生变化时。
 */
+ (void)levelUpEventWithLevel:(NSInteger)level
                          exp:(NSInteger)exp
                       method:(NSString *)method
                   afterLevel:(NSInteger)afterLevel
                  otherParams:(nullable NSDictionary *)otherParams;

#pragma mark - play

/**
 开始玩法：gt_start_play
 ectype_name string  针对闯关性质玩法，标注关卡名称
 触发条件：用户开始玩法时。
 */
+ (void)startPlayEventWithName:(NSString *)ecTypeName
                   otherParams:(nullable NSDictionary *)otherParams;

/**
 结束玩法：gt_end_play
 ectype_name string  针对闯关性质玩法，标注关卡名称
 result      string  玩法的结果：未完成、成功、失败等，使用英文进行标识.  未完成标记为uncompleted, 成功标记为success，失败为fail
 duration    int 消耗时间，单位秒
 触发条件：用户结束玩法时，涵盖中途退出、完成但失败和完成且成功。
 */
+ (void)endPlayEventWithName:(NSString *)ecTypeName
                      result:(NSString *)result
                     duration:(NSInteger)duration
                  otherParams:(nullable NSDictionary *)otherParams;

#pragma mark - coins

/**
 获得游戏币：gt_get_coins
 coin_type    string    货币类型：元宝、绑元、金币、银币等，使用文字或者英文进行标识
 method    string    获得途径：观看激励视频、闯关成功、活动奖励等，使用文字或者英文进行标识
 coin_num    int    获得数量
 触发条件：用户获得游戏币，导致游戏币增加时
 */
+ (void)getCoinsEventWitType:(NSString *)coinType
                      method:(NSString *)method
                  coinNumber:(NSInteger)number
                 otherParams:(nullable NSDictionary *)otherParams;

/**
 消耗游戏币：gt_cost_coins
 coin_type    string    货币类型：元宝、绑元、金币、银币等，使用文字或者英文进行标识
 method    string    消耗途径：复活、购买道具、解锁关卡等，使用文字或者英文进行标识
 coin_num    int    消耗数量
 触发条件：用户消耗游戏币，导致游戏币减少时。
 */
+ (void)costCoinsEventWitType:(NSString *)coinType
                       method:(NSString *)method
                   coinNumber:(NSInteger)number
                  otherParams:(nullable NSDictionary *)otherParams;

#pragma mark - Purchase

/**
 内购充值相关：purchase
 content_type  string  内购充值内容类型
 content_name  string  内购充值内容名称
 content_id    string  内购充值内容id
 content_num   int 内购充值内容的数量
 payment_channel string  支付渠道：例如 支付宝，微信等
 currency      string  支付货币类型
 is_success    string  支付是否成功
 currency_amount int 支付的金额，单位元
 触发条件：用户完成内购充值并获得对应的游戏内货币和道具时
 */
+ (void)purchaseEventWithContentType:(NSString *)contentType
                         contentName:(NSString *)contentName
                           contentID:(NSString *)contentID
                          contentNum:(NSInteger)contentNum
                             channel:(NSString *)channel
                            currency:(NSString *)currency
                           isSuccess:(NSString *)isSuccess
                      currencyAmount:(NSInteger)currencyAmount
                         otherParams:(nullable NSDictionary *)otherParams;

#pragma mark - InitInfo
/**
 初始化信息：gt_init_info
 lev    int    玩家等级
 coin_type    string    获得货币的类型
 coin_left    int    用户身上剩余的货币数量
 role_id    string    玩家角色id-cp侧
 触发条件：用户启动游戏，初始化完成时上报
 */
+ (void)gameInitInfoEventWithLevel:(NSInteger)level
                          coinType:(NSString *)coinType
                          coinLeft:(NSInteger)coinLeft
                       otherParams:(nullable NSDictionary *)otherParams;

@end
NS_ASSUME_NONNULL_END
