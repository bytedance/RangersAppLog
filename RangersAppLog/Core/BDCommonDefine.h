//
//  BDCommonDefine.h
//  RangersAppLog
//
//  Created by bob on 2020/3/25.
//

#import <Foundation/Foundation.h>

#ifndef BDCommonDefine_h
#define BDCommonDefine_h

NS_ASSUME_NONNULL_BEGIN

/*! @abstract 日志上报地区属性
 @discussion 上报地区请勿擅自选择，需要与申请服务的地区一致，或者咨询接口人确认
 */
typedef NS_ENUM(NSInteger, BDAutoTrackServiceVendor) {
    BDAutoTrackServiceVendorCN = 0x010, // 国内 中国
    BDAutoTrackServiceVendorSG,         // 新加坡
    BDAutoTrackServiceVendorVA,         // 美东
    BDAutoTrackServiceVendorPrivate,    // 私有化，此时一定要设置BDAutoTrackRequestURLBlock
};

/*! @abstract 日志输出
 @param log 输出的日志
 @discussion 请使用自己的日志SDK输出日志
 */
typedef void(^BDAutoTrackLogger)(NSString * _Nullable log);


/*!
 请求URL type
 */
typedef NSInteger BDAutoTrackRequestURLType NS_TYPED_ENUM;

FOUNDATION_EXTERN BDAutoTrackRequestURLType const BDAutoTrackRequestURLRegister; /// 注册
FOUNDATION_EXTERN BDAutoTrackRequestURLType const BDAutoTrackRequestURLActivate; /// 激活
FOUNDATION_EXTERN BDAutoTrackRequestURLType const BDAutoTrackRequestURLSettings; /// 基本配置
FOUNDATION_EXTERN BDAutoTrackRequestURLType const BDAutoTrackRequestURLABTest;   /// ABTest配置
FOUNDATION_EXTERN BDAutoTrackRequestURLType const BDAutoTrackRequestURLLog;      /// 日志上报
FOUNDATION_EXTERN BDAutoTrackRequestURLType const BDAutoTrackRequestURLLogBackup;/// 日志上报备用
FOUNDATION_EXTERN BDAutoTrackRequestURLType const BDAutoTrackRequestURLSuccessRatio; /// 成功率日志上报

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

typedef NS_ENUM(NSUInteger, BDAutoTrackLaunchFrom) {
    /// 初始状态
    BDAutoTrackLaunchFromInitialState = 0,
    /// 用户手动点击进入app
    BDAutoTrackLaunchFromUserClick,
    /// 用户通过push点击进入app
    BDAutoTrackLaunchFromRemotePush,
    /// 用户通过widget点击进入app
    BDAutoTrackLaunchFromWidget,
    /// 用户通过sptlight点击进入app
    BDAutoTrackLaunchFromSpotlight,
    /// 用户通过外部app唤醒进入app
    BDAutoTrackLaunchFromExternal,
    /// 用户手动切回前台
    BDAutoTrackLaunchFromBackground,
    /// from siri
    BDAutoTrackLaunchFromSiri,
};

NS_ASSUME_NONNULL_END
#endif /* BDCommonDefine_h */
