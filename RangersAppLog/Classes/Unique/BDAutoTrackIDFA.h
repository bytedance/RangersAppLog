//
//  BDAutoTrackIDFA.h
//  RangersAppLog
//
//  Created by bob on 2020/8/28.
//

#import "BDCommonDefine.h"

NS_ASSUME_NONNULL_BEGIN

@interface BDAutoTrackIDFA : NSObject

/**
 if you want to use idfa, you should request Authorization
 */
+ (BDAutoTrackAuthorizationStatus)authorizationStatus;
+ (void)requestAuthorizationWithHandler:(nullable BDAutoTrackAuthorizationHandler)completion;
+ (nullable NSString *)trackingIdentifier;

@end

NS_ASSUME_NONNULL_END
