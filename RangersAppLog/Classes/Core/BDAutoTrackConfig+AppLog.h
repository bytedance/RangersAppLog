//
//  BDAutoTrackConfig+AppLog.h
//  RangersAppLog
//
//  Created by bob on 2020/3/25.
//

#import "BDAutoTrackConfig.h"

NS_ASSUME_NONNULL_BEGIN

@interface BDAutoTrackConfig (AppLog)

/*! @abstract 是否开启无埋点。同时需要在Tea配置。
 @discussion 如果设置NO且Tea平台配置NO，则不会采集无埋点事件
 @discussion 如果设置NO且Tea平台配置YES，则拉取配置成功后开始采集无埋点事件
 @discussion 如果设置YES且Tea平台配置NO，则拉取配置成功后停止采集无埋点事件
 @discussion 如果设置YES且Tea平台配置YES，则采集无埋点事件
 */
@property (nonatomic, assign) BOOL autoTrackEnabled;

/*! @abstract 游戏模式，开启游戏模式会默认上报游戏心跳事件 */
@property (nonatomic, assign) BOOL gameModeEnable;

/*! @abstract 是否自动激活。默认YES，一般情况请不要修改 */
@property (nonatomic, assign) BOOL autoActiveUser;

/*! @abstract 采集事件的时候输出日志，在控制台中可以查看
 @discussion 需要同时设置logger，因为NSLog低效，且在iOS 13中有问题。release版本请设置为NO
 */
@property (nonatomic, assign) BOOL showDebugLog;

/*! @abstract 采集事件的时候输出日志，在控制台中可以查看
 @discussion logger为nil，则不会输出日志
 */
@property (nonatomic, copy, nullable) BDAutoTrackLogger logger;

/*! @abstract 日志上报是否加密。用于debug情况可以抓包调试 */
@property (nonatomic, assign) BOOL logNeedEncrypt;

/*! @abstract 是否自动拉配置。默认YES，一般情况请不要修改。仅私有化部署情况，可能不需要自动拉取配置 */
@property (nonatomic, assign) BOOL autoFetchSettings;

/*! @abstract 是否开AB。默认YES，一般情况请不要修改 */
@property (nonatomic, assign) BOOL abEnable;

@end

NS_ASSUME_NONNULL_END
