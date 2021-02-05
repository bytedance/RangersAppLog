//
//  BDAutoTrack+OhayooGameTrack.h
//  RangersAppLog
//
//  Created by 陈奕 on 2019/11/26.
//

#import "BDAutoTrack.h"

typedef NSString * OhayooCustomHeaderKey NS_TYPED_ENUM;

NS_ASSUME_NONNULL_BEGIN

/* ohayoo custom header key. 均以"ohayoo_"开头 */
FOUNDATION_EXTERN OhayooCustomHeaderKey OhayooCustomHeaderKeyPackageChannel;
FOUNDATION_EXTERN OhayooCustomHeaderKey OhayooCustomHeaderKeyZoneID;
FOUNDATION_EXTERN OhayooCustomHeaderKey OhayooCustomHeaderKeyServerID;
FOUNDATION_EXTERN OhayooCustomHeaderKey OhayooCustomHeaderKeySDKOpenID;
FOUNDATION_EXTERN OhayooCustomHeaderKey OhayooCustomHeaderKeyUserType;
FOUNDATION_EXTERN OhayooCustomHeaderKey OhayooCustomHeaderKeyRoleID;
FOUNDATION_EXTERN OhayooCustomHeaderKey OhayooCustomHeaderKeyLevel;

#pragma mark - OhayooGameTrack

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

/**
 @abstract 将相应ohayoo字段设置到custom header中的辅助方法。实际上是调用`setCustomHeaderValue:forKey:`。
 @discussion 使用示例:
 @code
 [BDAutoTrack ohayooHeaderSetObject:@"channel_123" forKey:OhayooCustomHeaderKeyPackageChannel];
 @code
 */
- (void)ohayooHeaderSetObject:(NSObject *)object forKey:(OhayooCustomHeaderKey)key;

- (void)ohayooHeaderRemoveObjectForKey:(OhayooCustomHeaderKey)key;

@end


#pragma mark - SharedOhayooGameTrack
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

/**
 @abstract 将相应ohayoo字段设置到custom header中的辅助方法。实际上是调用`setCustomHeaderValue:forKey:`。
 @discussion 使用示例:
 @code
 [BDAutoTrack ohayooHeaderSetObject:@"channel_123" forKey:OhayooCustomHeaderKeyPackageChannel];
 @code
 */
+ (void)ohayooHeaderSetObject:(NSObject *)object forKey:(OhayooCustomHeaderKey)key;

+ (void)ohayooHeaderRemoveObjectForKey:(OhayooCustomHeaderKey)key;


@end

NS_ASSUME_NONNULL_END
