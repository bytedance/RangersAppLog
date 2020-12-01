//
//  BDAutoTrack+OhayooGameTrack.h
//  RangersAppLog
//
//  Created by 陈奕 on 2019/11/26.
//

#import "BDAutoTrack.h"

NS_ASSUME_NONNULL_BEGIN

@interface BDAutoTrack (OhayooGameTrack)

/**
初始化信息：gt_init_info
lev         int 当前玩家等级
scene_id    int 当前场景id
scene_lev   int 当前场景的用户等级
coin_type   string  获得货币的类型
coin_left   int 用户身上剩余的货币数量
roleId      string 角色id
触发条件：用户启动游戏，初始化完成时上报
 
 @discussion 上报参数比GameTrack的多了 sceneID sceneLev
*/
- (void)gameInitInfoEventWithLevel:(NSInteger)level
                           sceneID:(NSInteger)sceneID
                          sceneLev:(NSInteger)sceneLev
                          coinType:(NSString *)coinType
                          coinLeft:(NSInteger)coinLeft
                            roleId:(NSString *)roleId
                       otherParams:(nullable NSDictionary *)otherParams;

@end

@interface BDAutoTrack (SharedOhayooGameTrack)

/**
初始化信息：gt_init_info
lev         int 当前玩家等级
scene_id    int 当前场景id
scene_lev   int 当前场景的用户等级
coin_type   string  获得货币的类型
coin_left   int 用户身上剩余的货币数量
roleId      string 角色id
触发条件：用户启动游戏，初始化完成时上报
 
@discussion 上报参数比GameTrack的多了 sceneID sceneLev
*/
+ (void)gameInitInfoEventWithLevel:(NSInteger)level
                           sceneID:(NSInteger)sceneID
                          sceneLev:(NSInteger)sceneLev
                          coinType:(NSString *)coinType
                          coinLeft:(NSInteger)coinLeft
                            roleId:(NSString *)roleId
                       otherParams:(nullable NSDictionary *)otherParams;

@end

NS_ASSUME_NONNULL_END
