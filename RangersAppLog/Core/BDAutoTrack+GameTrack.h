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

typedef NS_ENUM(NSInteger, BDGTGameResultType) {
    BDGTGameResultUncompleted = 1,
    BDGTGameResultSuccess,
    BDGTGameResultFail,
};

/*!
 BDAutoTrack 内置联运游戏上报API
 事件名称都有 gt 前缀
 具体参数参照接口人发送的文档
 */
@interface BDAutoTrack (GameTrack)

/**
 广告请求：gt_ad_request
 lev int 当前玩家等级
 scene_id    int 当前场景id
 scene_lev   int 当前场景的用户等级
 ad_type     string  广告类型：激励视频、插屏、banner等，直接使用汉字或者英文进行标识
 code_id     int 广告代码位id
 触发条件：向服务器请求广告时。穿山甲广告有回调，可以直接获取。
 */
- (void)adRequestEventWithLevel:(NSInteger)level
                        sceneID:(NSInteger)sceneID
                       sceneLev:(NSInteger)sceneLev
                           type:(NSString *)type
                         codeID:(NSInteger)codeID
                    otherParams:(nullable NSDictionary *)otherParams;

/**
 广告返回：gt_ad_send
 lev        int 当前玩家等级
 scene_id   int 当前场景id
 scene_lev  int 当前场景的用户等级
 ad_type    string  广告类型：激励视频、插屏、banner等，直接使用汉字或者英文进行标识
 code_id    int 广告代码位id
 ad_code    string  SDK返回的响应码（包括错误码）
 触发条件：服务器推送广告成功时。穿山甲广告有回调，可以直接获取。
 */
- (void)adSendEventWithLevel:(NSInteger)level
                     sceneID:(NSInteger)sceneID
                    sceneLev:(NSInteger)sceneLev
                        type:(NSString *)type
                      codeID:(NSInteger)codeID
                      adCode:(NSString *)adCode
                 otherParams:(nullable NSDictionary *)otherParams;

/**
 广告位按钮展示：gt_ad_button_show
 lev         int 当前玩家等级
 scene_id    int 当前场景id
 scene_lev  int 当前场景的用户等级
 ad_type     string  广告类型：激励视频、插屏、banner等，直接使用汉字或者英文进行标识
 ad_position_type  string  广告点位类型：按照提供分类接入
 ad_position string  广告点位：复活、翻倍、试用、buff、奖励道具、新道具、减CD等，直接使用文字或者英文进行标识
 code_id     int 广告代码位id
 触发条件：app内各广告位button有展示时。
 */
- (void)adButtonShowEventWithLevel:(NSInteger)level
                           sceneID:(NSInteger)sceneID
                          sceneLev:(NSInteger)sceneLev
                              type:(NSString *)type
                      positionType:(NSString *)positionType
                          position:(NSString *)position
                            codeID:(NSInteger)codeID
                       otherParams:(nullable NSDictionary *)otherParams;

/**
 广告按钮点击：gt_ad_button_click
 lev              int 当前玩家等级
 scene_id    int 当前场景id
 scene_lev   int 当前场景的用户等级
 ad_type     string  广告类型：激励视频、插屏、banner等，直接使用汉字或者英文进行标识
 ad_position_type  string  广告点位类型：按照提供分类接入
 ad_position string  广告点位：复活、翻倍、试用、buff、奖励道具、新道具、减CD等，直接使用文字或者英文进行标识
 code_id     int 广告代码位id
 触发条件：用户点击app内各广告位button时。
 */
- (void)adButtonClickEventWithLevel:(NSInteger)level
                            sceneID:(NSInteger)sceneID
                           sceneLev:(NSInteger)sceneLev
                               type:(NSString *)type
                       positionType:(NSString *)positionType
                           position:(NSString *)position
                             codeID:(NSInteger)codeID
                        otherParams:(nullable NSDictionary *)otherParams;

/**
 广告开始展示：gt_ad_show
 lev                    int 当前玩家等级
 scene_id          int 当前场景id
 scene_lev         int 当前场景的用户等级
 ad_type           string  广告类型：激励视频、插屏、banner等，直接使用汉字或者英文进行标识
 ad_position_type  string  广告点位类型：按照提供分类接入
 ad_position       string  广告点位：复活、翻倍、试用、buff、奖励道具、新道具、减CD等，直接使用文字或者英文进行标识
 code_id            int 广告代码位id
 ad_code           string  SDK返回的响应码（包括错误码）
 触发条件：用户点击并观看广告时。穿山甲广告有回调，可以直接获取。
 */
- (void)adShowEventWithLevel:(NSInteger)level
                     sceneID:(NSInteger)sceneID
                    sceneLev:(NSInteger)sceneLev
                        type:(NSString *)type
                positionType:(NSString *)positionType
                    position:(NSString *)position
                      codeID:(NSInteger)codeID
                      adCode:(NSString *)adCode
                 otherParams:(nullable NSDictionary *)otherParams;


/**
 广告结束展示：gt_ad_show_end
 lev               int 当前玩家等级
 scene_id          int 当前场景id
 scene_lev         int 当前场景的用户等级
 ad_type           string  广告类型：激励视频、插屏、banner等，直接使用汉字或者英文进行标识
 ad_position_type  string  广告点位类型：按照提供分类接入
 ad_position       string  广告点位：复活、翻倍、试用、buff、奖励道具、新道具、减CD等，直接使用文字或者英文进行标识
 code_id           int 广告代码位id
 result            string  广告观看结果：跳过、成功、失败等，使用英文进行标识.  跳过标记为skip, 成功标记为success，失败为fail
 触发条件：用户观看广告结束时。
 */
- (void)adShowEndEventWithLevel:(NSInteger)level
                        sceneID:(NSInteger)sceneID
                       sceneLev:(NSInteger)sceneLev
                           type:(NSString *)type
                   positionType:(NSString *)positionType
                       position:(NSString *)position
                         codeID:(NSInteger)codeID
                         result:(NSString *)result
                    otherParams:(nullable NSDictionary *)otherParams;

/**
 （总等级）升级和经验：gt_levelup
 lev             int 当前玩家等级
 scene_id    int 当前场景id
 scene_lev   int 当前场景的用户等级
 get_exp     int 获得经验
 method      string  获得经验途径：闯关成功、引导完成、领取奖励等，使用汉字或者英文进行标识
 aflev          int 用户获得经验后等级，如获得经验未导致升级，则lev=aflev，如导致升级，则lev<aflev
 触发条件：用户获得经验或者等级发生变化时。
 */
- (void)levelUpEventWithLevel:(NSInteger)level
                      sceneID:(NSInteger)sceneID
                     sceneLev:(NSInteger)sceneLev
                          exp:(NSInteger)exp
                       method:(NSString *)method
                   afterLevel:(NSInteger)afterLevel
                  otherParams:(nullable NSDictionary *)otherParams;

/**
 （分场景适用）升级和经验：gt_scene_levup
 lev              int 当前玩家等级
 scene_id    int 当前场景id
 scene_lev   int 当前场景的用户等级
 exp     int 获得经验
 method      string  获得经验途径：闯关成功、引导完成、领取奖励等，使用汉字或者英文进行标识
 scene_aflev int 用户获得经验后等级，如获得经验未导致升级，则 scene_lev=scene_aflev，如导致升级，则 scene_lev＜scene_aflev
 reset          int 当前场景的等级是否重置，未重置=0，重置1次=1，以此类推
 触发条件：用户在分场景获得经验或者等级发生变化时。
 */
- (void)sceneLevelUpEventWithLevel:(NSInteger)level
                           sceneID:(NSInteger)sceneID
                          sceneLev:(NSInteger)sceneLev
                               exp:(NSInteger)exp
                            method:(NSString *)method
                        afterLevel:(NSInteger)afterLevel
                             reset:(NSInteger)reset
                       otherParams:(nullable NSDictionary *)otherParams;

/**
 开始玩法：gt_start_play
 lev               int 当前玩家等级
 scene_id    int 当前场景id
 scene_lev   int 当前场景的用户等级
 ectype_type string  玩法类型：休闲模式、竞技模式
 ectype_id   int 具体的玩法ID，如果是闯关性质的玩法，使用连续数字标识关卡的顺序
 ectype_name string  针对闯关性质玩法，标注关卡名称。如无特定名称，可填ectype_id 关卡ID数字
 触发条件：用户开始玩法时。
 */
- (void)startPlayEventWithLevel:(NSInteger)level
                        sceneID:(NSInteger)sceneID
                       sceneLev:(NSInteger)sceneLev
                     ecTypeType:(NSString *)ecTypeType
                       ecTypeID:(NSInteger)ecTypeID
                     ecTypeName:(NSString *)ecTypeName
                    otherParams:(nullable NSDictionary *)otherParams;

/**
 结束玩法：gt_end_play
 lev                int 当前玩家等级
 scene_id      int 当前场景id
 scene_lev   int 当前场景的用户等级
 ectype_type string  玩法类型：休闲模式、竞技模式。 如游戏中只有一种玩法模式，该属性不上报
 ectype_id   int 具体的玩法ID，如果是闯关性质的玩法，使用从1开始连续数字标识关卡的顺序
 ectype_name string  针对闯关性质玩法，标注关卡名称。如无特定名称，可填ectype_id 关卡ID数字
 result      string  玩法的结果：未完成、成功、失败等，使用英文进行标识.  未完成标记为uncompleted, 成功标记为success，失败为fail
 score       int 获得分数或者星级，如玩法中没有输出，该属性可不上报
 duration    int 消耗时间，单位秒
 kill_num    int 击杀数量，如玩法中没有输出，则为空
 passed      string  曾经是否通关过，曾经通关过记为 yes，曾经未通关过记为 no. 如果游戏内没有首次通过概念，默认passed = no
 percentage  int 游戏进度：例如100%、25%等
 rank        string  结束时的段位、获取星星总量
 触发条件：用户结束玩法时，涵盖中途退出、完成但失败和完成且成功。
 */
- (void)endPlayEventWithLevel:(NSInteger)level
                      sceneID:(NSInteger)sceneID
                     sceneLev:(NSInteger)sceneLev
                   ecTypeType:(NSString *)ecTypeType
                     ecTypeID:(NSInteger)ecTypeID
                   ecTypeName:(NSString *)ecTypeName
                       result:(BDGTGameResultType)result
                        score:(NSInteger)score
                     duration:(NSInteger)duration
                      killNum:(NSInteger)killNum
                       passed:(BOOL)passed
                   percentage:(NSInteger)percentage
                         rank:(NSString *)rank
                  otherParams:(nullable NSDictionary *)otherParams;

/**
 内购充值相关：purchase
 lev           int 当前玩家等级
 scene_id      int 当前场景id
 scene_lev     int 当前场景的用户等级
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
- (void)purchaseEventWithLevel:(NSInteger)level
                       sceneID:(NSInteger)sceneID
                      sceneLev:(NSInteger)sceneLev
                   contentType:(NSString *)contentType
                   contentName:(NSString *)contentName
                     contentID:(NSString *)contentID
                    contentNum:(NSInteger)contentNum
                       channel:(NSString *)channel
                      currency:(NSString *)currency
                     isSuccess:(NSString *)isSuccess
                currencyAmount:(NSInteger)currencyAmount
                   otherParams:(nullable NSDictionary *)otherParams;

/**
 初始化信息：gt_init_info
 lev         int 当前玩家等级
 scene_id    int 当前场景id
 scene_lev   int 当前场景的用户等级
 coin_type   string  获得货币的类型
 coin_left   int 用户身上剩余的货币数量
 触发条件：用户启动游戏，初始化完成时上报
 */
- (void)gameInitInfoEventWithLevel:(NSInteger)level
                           sceneID:(NSInteger)sceneID
                          sceneLev:(NSInteger)sceneLev
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

/**
广告请求：gt_ad_request
lev int 当前玩家等级
scene_id    int 当前场景id
scene_lev   int 当前场景的用户等级
ad_type     string  广告类型：激励视频、插屏、banner等，直接使用汉字或者英文进行标识
code_id     int 广告代码位id
触发条件：向服务器请求广告时。穿山甲广告有回调，可以直接获取。
*/
+ (void)adRequestEventWithLevel:(NSInteger)level
                        sceneID:(NSInteger)sceneID
                       sceneLev:(NSInteger)sceneLev
                           type:(NSString *)type
                         codeID:(NSInteger)codeID
                    otherParams:(nullable NSDictionary *)otherParams;

/**
广告返回：gt_ad_send
lev        int 当前玩家等级
scene_id   int 当前场景id
scene_lev  int 当前场景的用户等级
ad_type    string  广告类型：激励视频、插屏、banner等，直接使用汉字或者英文进行标识
code_id    int 广告代码位id
ad_code    string  SDK返回的响应码（包括错误码）
触发条件：服务器推送广告成功时。穿山甲广告有回调，可以直接获取。
*/
+ (void)adSendEventWithLevel:(NSInteger)level
                     sceneID:(NSInteger)sceneID
                    sceneLev:(NSInteger)sceneLev
                        type:(NSString *)type
                      codeID:(NSInteger)codeID
                      adCode:(NSString *)adCode
                 otherParams:(nullable NSDictionary *)otherParams;

/**
广告位按钮展示：gt_ad_button_show
lev         int 当前玩家等级
scene_id    int 当前场景id
scene_lev  int 当前场景的用户等级
ad_type     string  广告类型：激励视频、插屏、banner等，直接使用汉字或者英文进行标识
ad_position_type  string  广告点位类型：按照提供分类接入
ad_position string  广告点位：复活、翻倍、试用、buff、奖励道具、新道具、减CD等，直接使用文字或者英文进行标识
code_id     int 广告代码位id
触发条件：app内各广告位button有展示时。
*/
+ (void)adButtonShowEventWithLevel:(NSInteger)level
                           sceneID:(NSInteger)sceneID
                          sceneLev:(NSInteger)sceneLev
                              type:(NSString *)type
                      positionType:(NSString *)positionType
                          position:(NSString *)position
                            codeID:(NSInteger)codeID
                       otherParams:(nullable NSDictionary *)otherParams;

/**
广告按钮点击：gt_ad_button_click
lev              int 当前玩家等级
scene_id    int 当前场景id
scene_lev   int 当前场景的用户等级
ad_type     string  广告类型：激励视频、插屏、banner等，直接使用汉字或者英文进行标识
ad_position_type  string  广告点位类型：按照提供分类接入
ad_position string  广告点位：复活、翻倍、试用、buff、奖励道具、新道具、减CD等，直接使用文字或者英文进行标识
code_id     int 广告代码位id
触发条件：用户点击app内各广告位button时。
*/
+ (void)adButtonClickEventWithLevel:(NSInteger)level
                            sceneID:(NSInteger)sceneID
                           sceneLev:(NSInteger)sceneLev
                               type:(NSString *)type
                       positionType:(NSString *)positionType
                           position:(NSString *)position
                             codeID:(NSInteger)codeID
                        otherParams:(nullable NSDictionary *)otherParams;

/**
广告开始展示：gt_ad_show
lev                    int 当前玩家等级
scene_id          int 当前场景id
scene_lev         int 当前场景的用户等级
ad_type           string  广告类型：激励视频、插屏、banner等，直接使用汉字或者英文进行标识
ad_position_type  string  广告点位类型：按照提供分类接入
ad_position       string  广告点位：复活、翻倍、试用、buff、奖励道具、新道具、减CD等，直接使用文字或者英文进行标识
code_id            int 广告代码位id
ad_code           string  SDK返回的响应码（包括错误码）
触发条件：用户点击并观看广告时。穿山甲广告有回调，可以直接获取。
*/
+ (void)adShowEventWithLevel:(NSInteger)level
                     sceneID:(NSInteger)sceneID
                    sceneLev:(NSInteger)sceneLev
                        type:(NSString *)type
                positionType:(NSString *)positionType
                    position:(NSString *)position
                      codeID:(NSInteger)codeID
                      adCode:(NSString *)adCode
                 otherParams:(nullable NSDictionary *)otherParams;

/**
广告结束展示：gt_ad_show_end
lev               int 当前玩家等级
scene_id          int 当前场景id
scene_lev         int 当前场景的用户等级
ad_type           string  广告类型：激励视频、插屏、banner等，直接使用汉字或者英文进行标识
ad_position_type  string  广告点位类型：按照提供分类接入
ad_position       string  广告点位：复活、翻倍、试用、buff、奖励道具、新道具、减CD等，直接使用文字或者英文进行标识
code_id           int 广告代码位id
result            string  广告观看结果：跳过、成功、失败等，使用英文进行标识.  跳过标记为skip, 成功标记为success，失败为fail
触发条件：用户观看广告结束时。
*/
+ (void)adShowEndEventWithLevel:(NSInteger)level
                        sceneID:(NSInteger)sceneID
                       sceneLev:(NSInteger)sceneLev
                           type:(NSString *)type
                   positionType:(NSString *)positionType
                       position:(NSString *)position
                         codeID:(NSInteger)codeID
                         result:(NSString *)result
                    otherParams:(nullable NSDictionary *)otherParams;

/**
（总等级）升级和经验：gt_levelup
lev             int 当前玩家等级
scene_id    int 当前场景id
scene_lev   int 当前场景的用户等级
get_exp     int 获得经验
method      string  获得经验途径：闯关成功、引导完成、领取奖励等，使用汉字或者英文进行标识
aflev          int 用户获得经验后等级，如获得经验未导致升级，则lev=aflev，如导致升级，则lev<aflev
触发条件：用户获得经验或者等级发生变化时。
*/
+ (void)levelUpEventWithLevel:(NSInteger)level
                      sceneID:(NSInteger)sceneID
                     sceneLev:(NSInteger)sceneLev
                          exp:(NSInteger)exp
                       method:(NSString *)method
                   afterLevel:(NSInteger)afterLevel
                  otherParams:(nullable NSDictionary *)otherParams;

/**
（分场景适用）升级和经验：gt_scene_levup
lev              int 当前玩家等级
scene_id    int 当前场景id
scene_lev   int 当前场景的用户等级
exp     int 获得经验
method      string  获得经验途径：闯关成功、引导完成、领取奖励等，使用汉字或者英文进行标识
scene_aflev int 用户获得经验后等级，如获得经验未导致升级，则 scene_lev=scene_aflev，如导致升级，则 scene_lev＜scene_aflev
reset          int 当前场景的等级是否重置，未重置=0，重置1次=1，以此类推
触发条件：用户在分场景获得经验或者等级发生变化时。
*/
+ (void)sceneLevelUpEventWithLevel:(NSInteger)level
                           sceneID:(NSInteger)sceneID
                          sceneLev:(NSInteger)sceneLev
                               exp:(NSInteger)exp
                            method:(NSString *)method
                        afterLevel:(NSInteger)afterLevel
                             reset:(NSInteger)reset
                       otherParams:(nullable NSDictionary *)otherParams;

/**
开始玩法：gt_start_play
lev               int 当前玩家等级
scene_id    int 当前场景id
scene_lev   int 当前场景的用户等级
ectype_type string  玩法类型：休闲模式、竞技模式
ectype_id   int 具体的玩法ID，如果是闯关性质的玩法，使用连续数字标识关卡的顺序
ectype_name string  针对闯关性质玩法，标注关卡名称。如无特定名称，可填ectype_id 关卡ID数字
触发条件：用户开始玩法时。
*/
+ (void)startPlayEventWithLevel:(NSInteger)level
                        sceneID:(NSInteger)sceneID
                       sceneLev:(NSInteger)sceneLev
                     ecTypeType:(NSString *)ecTypeType
                       ecTypeID:(NSInteger)ecTypeID
                     ecTypeName:(NSString *)ecTypeName
                    otherParams:(nullable NSDictionary *)otherParams;


/**
 结束玩法：gt_end_play
 lev                int 当前玩家等级
 scene_id      int 当前场景id
 scene_lev   int 当前场景的用户等级
 ectype_type string  玩法类型：休闲模式、竞技模式。 如游戏中只有一种玩法模式，该属性不上报
 ectype_id   int 具体的玩法ID，如果是闯关性质的玩法，使用从1开始连续数字标识关卡的顺序
 ectype_name string  针对闯关性质玩法，标注关卡名称。如无特定名称，可填ectype_id 关卡ID数字
 result      string  玩法的结果：未完成、成功、失败等，使用英文进行标识.  未完成标记为uncompleted, 成功标记为success，失败为fail
 score       int 获得分数或者星级，如玩法中没有输出，该属性可不上报
 duration    int 消耗时间，单位秒
 kill_num    int 击杀数量，如玩法中没有输出，则为空
 passed      string  曾经是否通关过，曾经通关过记为 yes，曾经未通关过记为 no. 如果游戏内没有首次通过概念，默认passed = no
 percentage  int 游戏进度：例如100%、25%等
 rank        string  结束时的段位、获取星星总量
 触发条件：用户结束玩法时，涵盖中途退出、完成但失败和完成且成功。
 */
+ (void)endPlayEventWithLevel:(NSInteger)level
                      sceneID:(NSInteger)sceneID
                     sceneLev:(NSInteger)sceneLev
                   ecTypeType:(NSString *)ecTypeType
                     ecTypeID:(NSInteger)ecTypeID
                   ecTypeName:(NSString *)ecTypeName
                       result:(BDGTGameResultType)result
                        score:(NSInteger)score
                     duration:(NSInteger)duration
                      killNum:(NSInteger)killNum
                       passed:(BOOL)passed
                   percentage:(NSInteger)percentage
                         rank:(NSString *)rank
                  otherParams:(nullable NSDictionary *)otherParams;

/**
内购充值相关：purchase
lev           int 当前玩家等级
scene_id      int 当前场景id
scene_lev     int 当前场景的用户等级
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
+ (void)purchaseEventWithLevel:(NSInteger)level
                       sceneID:(NSInteger)sceneID
                      sceneLev:(NSInteger)sceneLev
                   contentType:(NSString *)contentType
                   contentName:(NSString *)contentName
                     contentID:(NSString *)contentID
                    contentNum:(NSInteger)contentNum
                       channel:(NSString *)channel
                      currency:(NSString *)currency
                     isSuccess:(NSString *)isSuccess
                currencyAmount:(NSInteger)currencyAmount
                   otherParams:(nullable NSDictionary *)otherParams;

/**
初始化信息：gt_init_info
lev         int 当前玩家等级
scene_id    int 当前场景id
scene_lev   int 当前场景的用户等级
coin_type   string  获得货币的类型
coin_left   int 用户身上剩余的货币数量
触发条件：用户启动游戏，初始化完成时上报
*/
+ (void)gameInitInfoEventWithLevel:(NSInteger)level
                           sceneID:(NSInteger)sceneID
                          sceneLev:(NSInteger)sceneLev
                          coinType:(NSString *)coinType
                          coinLeft:(NSInteger)coinLeft
                       otherParams:(nullable NSDictionary *)otherParams;

@end
NS_ASSUME_NONNULL_END
