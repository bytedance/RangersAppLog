//
//  BDCommonEnumDefine.h
//  RangersAppLog
//
//  Created by 朱元清 on 2020/8/10.
//

#import <Foundation/Foundation.h>

#ifndef BDCommonEnumDefine_h
#define BDCommonEnumDefine_h

/*! @abstract 日志上报地区属性
 @discussion 上报地区请勿擅自选择，需要与申请服务的地区一致，或者咨询接口人确认
 */
typedef NSString* BDAutoTrackServiceVendor NS_EXTENSIBLE_STRING_ENUM;
FOUNDATION_EXTERN BDAutoTrackServiceVendor const BDAutoTrackServiceVendorPrivate;  // 私有化，此时一定要设置BDAutoTrackRequestURLBlock



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

/**
 IDFA Authorization Status
 */
typedef NS_ENUM(NSInteger, BDAutoTrackAuthorizationStatus) {
    BDAutoTrackAuthorizationStatusNotDetermined = 0,
    BDAutoTrackAuthorizationStatusRestricted,
    BDAutoTrackAuthorizationStatusDenied,
    BDAutoTrackAuthorizationStatusAuthorized
};

#endif /* BDCommonEnumDefine_h */
