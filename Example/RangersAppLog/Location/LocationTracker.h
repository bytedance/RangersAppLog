//
//  LocationTracker.h
//  RangersAppLog
//
//  Created by bob on 2019/11/6.
//  Copyright © 2019 Bytedance. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface LocationTracker : NSObject

@property (nonatomic, assign) BOOL enabled;

+ (instancetype)sharedInstance;

- (void)requestAuthorization;

+ (BOOL)checkLocationAbility;

@end

NS_ASSUME_NONNULL_END
