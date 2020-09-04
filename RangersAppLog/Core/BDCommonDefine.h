//
//  BDCommonDefine.h
//  RangersAppLog
//
//  Created by bob on 2020/3/25.
//

#import <Foundation/Foundation.h>
#import "BDCommonEnumDefine.h"

#ifndef BDCommonDefine_h
#define BDCommonDefine_h

NS_ASSUME_NONNULL_BEGIN

/*
 request IDFA handler
 */
typedef void (^BDAutoTrackAuthorizationHandler)(BDAutoTrackAuthorizationStatus status);

/*! @abstract 日志输出
 @param log 输出的日志
 @discussion 请使用自己的日志SDK输出日志
 */
typedef void(^BDAutoTrackLogger)(NSString * _Nullable log);


/*! @abstract 自定义请求链接，把相关请求发送到对应的自定义的URL上
 @param vendor 地区
 @param requestURLType 上面的六个枚举值
 @discussion 一般情况不需要实现；如果实现，针对想改变的枚举值返回一个准确的URL，其他不想修改的返回nil即可
 @result 返回自定义的URL
 */
typedef NSString * _Nullable (^BDAutoTrackRequestURLBlock)(BDAutoTrackServiceVendor vendor, BDAutoTrackRequestURLType requestURLType);

/*! @abstract 自定义请求链接的Host，把相关请求发送到对应的自定义的Host上，path仍然按照SDK规则拼接
 @param vendor 地区
 @param requestURLType 上面的六个枚举值
 @discussion 一般情况不需要实现；如果实现，返回值类似  https://github.com/
 @result 返回自定义的URL
 */
typedef NSString * _Nullable (^BDAutoTrackRequestHostBlock)(BDAutoTrackServiceVendor vendor, BDAutoTrackRequestURLType requestURLType);


/*! @abstract 自定义上报信息
 @discussion 每次上报都会回调，设置一次即可，格式要求同日志要求，需要可序列化；如果无法序列化，会被丢弃
 @result NSDictionary custom数据
 */
typedef NSDictionary<NSString*, id> *_Nonnull (^BDAutoTrackCustomHeaderBlock)(void);

@protocol BDAutoTrackSchemeHandler <NSObject>

/*! @abstract 处理scheme
 @discussion 请参考下面接口调用示例
 @param URL scheme的完整URL，透传参数
 @param appID 初始化SDK的AppID
 @param scene 适配iOS 13的参数，透传参数
 @result 返回YES，表示已经处理了该URL，NO表示没有处理
*/
- (BOOL)handleURL:(NSURL *)URL appID:(NSString *)appID scene:(nullable id)scene;

@end

NS_ASSUME_NONNULL_END
#endif /* BDCommonDefine_h */
