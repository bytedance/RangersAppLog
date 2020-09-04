//
//  BDAdapter.h
//  BDAutoTracker_Example
//
//  Created by bob on 2019/8/19.
//  Copyright © 2019 ByteDance. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@class BDFeedModel;

@interface BDAdapter : NSObject

+ (void)startAutoTracker;

+ (void)trackKeyWindow:(UIWindow *)keyWindow;

+ (BOOL)eventV3:(NSString *)event params:(NSDictionary *)params;

+ (BOOL)handleURL:(NSURL *)URL scene:(nullable id)scene;

+ (void)addTestButtonInWindow:(UIWindow *)window;

@end

NS_ASSUME_NONNULL_END
