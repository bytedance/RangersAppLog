//
//  BDAutoTrackCacheRemover.h
//  RangersAppLog
//
//  Created by 朱元清 on 2020/11/2.
//

#import <Foundation/Foundation.h>
#import "RangersAppLog.h"

/**
 本文件包含SDK缓存的接口。仅限于开发调试阶段清除SDK缓存之用途。生产环境禁止使用！
 本文件接口主要是为了自动化测试中快速删除缓存。
 如果您不是自动化测试，建议通过在手机或模拟器上删除应用的方式来清除缓存，更方便快捷；不必使用本文件的接口。
 */

NS_ASSUME_NONNULL_BEGIN

@interface BDAutoTrackCacheRemover : NSObject


/*********************************** SDK私有缓存 ************************************/
/// 永久删除 SDK 私有缓存（包括deviceID\ssID\installID\userUniqueID\ABTest配置等信息）
- (void)removeDefaultsForAppID:(NSString *)appID;


/*********************************** StandardDefaults ************************************/
/// 临时将应用层移除出StandardDefaults的搜索列表
- (void)removeCurrentBundleFromStandardDefaultsSearchList;

/// 永久删除 StandardDefaults 的应用层缓存
- (void)removeCurrentBundleFromStandardDefaults;


/*********************************** KeyChain ************************************/
/// 删除SDK再 keychian 中的缓存
- (void)removeKeychainForAppID:(NSString *)appID serviceVendor:(BDAutoTrackServiceVendor)vendor;

@end

NS_ASSUME_NONNULL_END
