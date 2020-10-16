//
//  BDAutoTrack+Profile.h
//  Applog
//
//  Created by 朱元清 on 2020/9/11.
//

#import "BDAutoTrack.h"

NS_ASSUME_NONNULL_BEGIN

@interface BDAutoTrack (Profile)

#pragma mark 实例方法
/// @abstract 设置一组profile属性
/// @discussion 参数字典的值只能是以下类型：字符串、整型、浮点型、字符串数组
/// @param profileDict 字典。包含一个或多个要设置的profile属性和值
- (void)profileSet:(NSDictionary *)profileDict;

/// @abstract 设置一组profile属性。若一个接口是通过重复调用该接口无效。
/// @discussion 与profileSet接口不同的是：若某profile已成功通过setOnce接口设置，那么对该profile再次调用setOnce接口无效。
/// 一个通过setOnce设置的profile被unset后，无法再次通过setOnce设置。
/// 参数字典的值只能是以下类型：字符串、整型、浮点型、字符串数组
/// @param profileDict 字典。包含一个或多个要设置的profile属性和值
- (void)profileSetOnce:(NSDictionary *)profileDict;

/// @abstract unset一个之前被profileSet或profileSetOnce接口设置的profile
/// @param profileName 要unset的profile的名称
- (void)profileUnset:(NSString *)profileName;

/// @abstract 为数值类型的profile属性做自增操作
/// @discussion 只能自增整数（可以为负整数）。如果传入浮点数，SDK将忽略。
/// @param profileDict 字典。包含一个或多个要设置的数值类型profile属性和要增加的值。
- (void)profileIncrement:(NSDictionary <NSString *, NSNumber *> *)profileDict;

/// @abstract 为数组类型的profile属性添加一个值
/// @discussion 参数字典的值只能为字符串或者字符串数组。e.g.
/// @code
/// NSDitcionary *profileDict = @{
///     @"needs": @"洗衣机",
///     @"favorites": @[@"海尔", @"海信", @"美的"]
/// }
/// [track profileAppend:profileDict];
/// @param profileDict 字典。包含一个或多个要设置的数组类型的profile属性和要添加的值
- (void)profileAppend:(NSDictionary *)profileDict;

#pragma mark 类方法
/// @abstract 设置一组profile属性
/// @discussion 参数字典的值只能是以下类型：字符串、整型、浮点型、字符串数组
/// @param profileDict 字典。包含一个或多个要设置的profile属性和值
+ (void)profileSet:(NSDictionary *)profileDict;

/// @abstract 设置一组profile属性。若一个接口是通过重复调用该接口无效。
/// @discussion 与profileSet接口不同的是：若某profile已成功通过setOnce接口设置，那么对该profile再次调用setOnce接口无效。
/// 一个通过setOnce设置的profile被unset后，无法再次通过setOnce设置。
/// 参数字典的值只能是以下类型：字符串、整型、浮点型、字符串数组
/// @param profileDict 字典。包含一个或多个要设置的profile属性和值
+ (void)profileSetOnce:(NSDictionary *)profileDict;

/// @abstract unset一个之前被profileSet或profileSetOnce接口设置的profile
/// @param profileName 要unset的profile的名称
+ (void)profileUnset:(NSString *)profileName;

/// @abstract 为数值类型的profile属性做自增操作
/// @discussion 只能自增整数（可以为负整数）。如果传入浮点数，SDK将忽略。
/// @param profileDict 字典。包含一个或多个要设置的数值类型profile属性和要增加的值。
+ (void)profileIncrement:(NSDictionary <NSString *, NSNumber *> *)profileDict;

/// @abstract 为数组类型的profile属性添加一个值
/// @discussion 参数字典的值只能为字符串或者字符串数组。e.g.
/// @code
/// NSDitcionary *profileDict = @{
///     @"needs": @"洗衣机",
///     @"favorites": @[@"海尔", @"海信", @"美的"]
/// }
/// [BDAutoTrack profileAppend:profileDict];
/// @param profileDict 字典。包含一个或多个要设置的数组类型的profile属性和要添加的值
+ (void)profileAppend:(NSDictionary *)profileDict;


@end

NS_ASSUME_NONNULL_END
