//
//  BDAbstractModel.h
//  ObjCExample
//
//  Created by 朱元清 on 2020/8/25.
//  Copyright © 2020 bytedance. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/// 所有Model的抽象祖先类
@interface BDAbstractModel : NSObject

@property (nonatomic, copy) dispatch_block_t actionBlock;
@property (nonatomic, assign) NSInteger cellType;

@end

NS_ASSUME_NONNULL_END
