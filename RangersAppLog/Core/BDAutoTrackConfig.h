//
//  BDAutoTrackConfig.h
//  RangersAppLog
//
//  Created by bob on 2020/3/25.
//

#import <Foundation/Foundation.h>
#import "BDCommonDefine.h"

NS_ASSUME_NONNULL_BEGIN

@interface BDAutoTrackConfig : NSObject

/*! @abstract channel默认 @"App Store", Release版本只有 @"App Store"， debug版本可以任意设置. */
@property (nonatomic, copy) NSString *channel;

/*! @abstract 申请appID时候填写的英文名称 */
@property (nonatomic, copy, nullable) NSString *appName;

/*! @abstract AppID，非空，必须设置 */
@property (nonatomic, copy) NSString *appID;


/*! @abstract 默认国内,初始化时一定要传正确的值
 @discussion 发生变化时候请调用 `+[BDAutoTrack setServiceVendor:]`更新值
 @discussion 会影响注册和日志上报。所以如果发生变化后，下次启动初始化请传入正确的值
 */
@property (nonatomic, assign) BDAutoTrackServiceVendor serviceVendor;


/*! @abstract 根据App ID获取一个config
@param appID AppID
@result 一个config实例, 其他参数非必填，或者有默认值，可以直接通过setter 设置
*/
+ (instancetype)configWithAppID:(NSString *)appID;


/*!
 使用示例1：
  BDAutoTrackConfig *config = [BDAutoTrackConfig configWithSecondAppID:appid];
 // 初始化完成之后，可以调用其他接口
 BDAutoTrack *track = [BDAutoTrack trackWithConfig:config]

 // 设置一些属性等配置
 [track setCurrentUserUniqueID:@"123"];

 // 开始上报
 [track satrtTrack];

 // 用变量引用住track用于上报
 [track eventV3:xxx params:xxx];
 */

/*! @abstract 根据App ID获取一个config
@param appID AppID
@result 一个config实例, 此config默认设置了不会激活和拉取settings。可用于第三方SDK需要上报一些事件，但是不需要激活等
*/
+ (instancetype)configWithSecondAppID:(NSString *)appID;

@end

NS_ASSUME_NONNULL_END
