//
//  BDPlayer.h
//  RangersAppLog
//
//  Created by bob on 2019/11/6.
//  Copyright © 2019 Bytedance. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface BDPlayer : NSObject

+ (instancetype)sharedInstance;

- (void)play;
- (void)pause;
- (void)stop;

@end

NS_ASSUME_NONNULL_END
