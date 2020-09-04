//
//  BDModelSectionHeader.h
//  ObjCExample
//
//  Created by 朱元清 on 2020/8/22.
//  Copyright © 2020 bytedance. All rights reserved.
//  没有实际数据。只是用于在FeedModel数组中标识一个Section.

#import "BDFeedModel.h"
#import "BDAbstractModel.h"

NS_ASSUME_NONNULL_BEGIN

@interface BDModelSectionHeader : NSObject

@property (strong, nonatomic) NSString *sectionName;
@property (nonatomic) NSUInteger sectionLength;
@property (strong, nonatomic) NSString *sectionDescription;

- (instancetype)initWithSectionName:(NSString *)name desc:(NSString *)desc;
@end

NS_ASSUME_NONNULL_END
