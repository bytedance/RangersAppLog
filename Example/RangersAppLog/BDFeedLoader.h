//
//  BDFeedLoader.h
//  RangersAppLog
//
//  Created by bob on 2019/9/9.
//  Copyright © 2019 Bytedance. All rights reserved.
//

#import <Foundation/Foundation.h>

@class BDFeedModel;

NS_ASSUME_NONNULL_BEGIN

@interface BDFeedLoader : NSObject

+ (NSArray<BDFeedModel *> *)loadDemoFeedList;

@end

NS_ASSUME_NONNULL_END
