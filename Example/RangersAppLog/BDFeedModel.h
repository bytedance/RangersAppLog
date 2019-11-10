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

@property (nonatomic, assign) NSInteger state;
@property (nonatomic, assign) NSInteger eventIndex;
@property (nonatomic, copy) NSString *methodName;
+ (instancetype)modelWithIndex:(NSInteger)index
                        method:(NSString *)method
                         state:(NSInteger)state;

@end

NS_ASSUME_NONNULL_END
