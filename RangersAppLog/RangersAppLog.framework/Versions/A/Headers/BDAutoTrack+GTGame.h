//
//  BDAutoTrack+GTGame.h
//  Applog
//
//  Created by bob on 2019/7/17.
//

#import "BDAutoTrack.h"

NS_ASSUME_NONNULL_BEGIN
/*!
 事件参数level的key，保持参数一致
 可以这样使用来设置Header
 [self getCurrentLevel]返回一个当前level的函数
 此header的block设置一次即可，每次会回调。

 [BDAutoTrack setCustomHeaderBlock:^NSDictionary<NSString *,id> * _Nonnull{
    return @{kGTGameParameterLevel:@([self getCurrentLevel])};
 }];
 */
FOUNDATION_EXTERN NSString * const kGTGameParameterLevel;

/*!
 BDAutoTrack 内置联运游戏上报API
 事件名称都有 gt 前缀
 具体参数参照接口人发送的文档
 */
@interface BDAutoTrack (GTGame)

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

NS_ASSUME_NONNULL_END
