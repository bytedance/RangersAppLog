//
//  BDAutoTrack+Special.h
//  RangersAppLog
//
//  Created by bob on 2019/6/2.
//

#import "BDAutoTrack.h"
#import "BDAutoTrack+SharedInstance.h"

NS_ASSUME_NONNULL_BEGIN

/*!
 BDAutoTrack  内部支持上报接口，外部客户请勿调用
 */
@interface BDAutoTrack (Special)

+ (NSDictionary *)specialParamsWitAppID:(NSString *)appID
                                appName:(NSString *)appName
                                   type:(NSString *)productType;

- (BOOL)eventV3:(NSString *)event params:(nullable NSDictionary *)params specialParams:(NSDictionary *)specialParams;

- (BOOL)customEvent:(NSString *)category params:(NSDictionary *)params;

@end

NS_ASSUME_NONNULL_END
