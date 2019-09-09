//
//  BDFeedModel.h
//  RangersAppLog
//
//  Created by bob on 2019/9/9.
//  Copyright © 2019 Bytedance. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface BDFeedModel : NSObject

@property (nonatomic, copy) NSString *title;
@property (nonatomic, copy) NSString *nextVCName;
@property (nonatomic, copy) dispatch_block_t actionBlock;

@end

NS_ASSUME_NONNULL_END
