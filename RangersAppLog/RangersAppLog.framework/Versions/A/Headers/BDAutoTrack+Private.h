//
//  BDAutoTrack+Private.h
//  Pods-BDAutoTracker_Example
//
//  Created by bob on 2019/6/4.
//

#import "BDAutoTrack.h"

NS_ASSUME_NONNULL_BEGIN

/*!
 BDAutoTrack  内部支持log_data上报接口，外部客户请勿调用
 */
@interface BDAutoTrack (Private)

+ (BOOL)customEvent:(NSString *)category params:(NSDictionary *)params;

@end

NS_ASSUME_NONNULL_END
