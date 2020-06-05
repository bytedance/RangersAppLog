//
//  BDAutoTrack+IDFA.h
//  RangersAppLog
//
//  Created by bob on 2020/5/25.
//

#import "BDAutoTrack.h"

NS_ASSUME_NONNULL_BEGIN

@interface BDAutoTrack (IDFA)

/*! @abstract 初始化之前设置，关闭IDFA采集
*/
+ (void)turnOffIDFA;

@end

NS_ASSUME_NONNULL_END
