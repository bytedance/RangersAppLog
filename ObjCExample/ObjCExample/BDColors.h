//
//  BDColors.h
//  ObjCExample
//
//  Created by 朱元清 on 2020/8/24.
//  Copyright © 2020 bytedance. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
NS_ASSUME_NONNULL_BEGIN

@interface BDColors : NSObject

+ (instancetype)sharedInstance;

- (UIColor *)lightGreen;
- (UIColor *)lightRed;
- (UIColor *)lightBlue;
@end

NS_ASSUME_NONNULL_END
