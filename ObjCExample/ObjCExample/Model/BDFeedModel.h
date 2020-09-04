//
//  BDFeedModel.h
//  BDAutoTracker_Example
//
//  Created by bob on 2019/4/17.
//  Copyright © 2019 ByteDance. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "BDAbstractModel.h"

NS_ASSUME_NONNULL_BEGIN

@interface BDFeedModel : BDAbstractModel

@property (nonatomic, copy) NSString *title;

//@property (nonatomic, copy) NSString *httpURL;

- (instancetype)initWithTitle:(NSString *)title actionBlock:(dispatch_block_t)actionBlock;

@end

NS_ASSUME_NONNULL_END
