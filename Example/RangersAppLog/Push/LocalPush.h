//
//  LocalPush.h
//  RangersAppLog
//
//  Created by bob on 2019/11/8.
//  Copyright © 2019 Bytedance. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface LocalPush : NSObject

@property (nonatomic, assign) BOOL enabled;

+ (instancetype)sharedInstance;

- (void)registerUserNotification;

@end

NS_ASSUME_NONNULL_END
