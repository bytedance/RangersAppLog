//
//  BDAdapter.h
//  RangersAppLog
//
//  Created by bob on 2019/9/9.
//  Copyright © 2019 Bytedance. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface BDAdapter : NSObject

+ (void)startAppLog;

+ (void)eventV3:(NSString *)event params:(nullable NSDictionary *)params;

+ (id)ABTestValue;

+ (void)logout;

+ (void)login;

@end

NS_ASSUME_NONNULL_END
