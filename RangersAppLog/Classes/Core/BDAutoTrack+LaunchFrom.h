//
//  BDAutoTrack+LaunchFrom.h
//  RangersAppLog
//
//  Created by bob on 2020/6/3.
//

#import "BDAutoTrack.h"
#import "BDCommonDefine.h"

NS_ASSUME_NONNULL_BEGIN

@interface BDAutoTrack (LaunchFrom)

/*
 @abstract 初始化之后，支持设置APP的启动方式，会体现的上报的数据中，参考<RangersAppLog/BDCommonDefine.h>
 */
+ (void)setLaunchFrom:(BDAutoTrackLaunchFrom)from;

@end

NS_ASSUME_NONNULL_END
