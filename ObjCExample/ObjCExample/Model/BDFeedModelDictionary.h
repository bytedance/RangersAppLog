//
//  BDFeedModelDictionary.h
//  ObjCExample
//
//  Created by 朱元清 on 2020/8/22.
//  Copyright © 2020 bytedance. All rights reserved.
//  作为 UITableView 的 Model
/*
 * 实现：
 * 类内部维护两个字典。
 * 1. section:modelItems MAP
 * {
 *     @(0): @[BDAbstractModel, BDAbstractModel, ...],
 *     @(1): @[BDAbstractModel, BDAbstractModel, ...]
 * }
 *
 * 2. section:sectionMeta MAP
 * {
 *     @(0): BDModelSectionHeader,
 *     @(1): BDModelSectionHeader
 * }
*/


#import <Foundation/Foundation.h>
#import "BDFeedModel.h"
#import "BDModelSectionHeader.h"

NS_ASSUME_NONNULL_BEGIN

@interface BDFeedModelDictionary : NSObject

- (instancetype)initWithModelArray:(NSArray *)array;

- (BOOL)setSectionDevider:(BDModelSectionHeader *)sectionDevider ToSection:(NSInteger)section;

- (BOOL)appendItem:(BDAbstractModel *)item ToSection:(NSInteger)section;

- (BOOL)appendItems:(NSArray *)items ToSection:(NSInteger)section;

- (BOOL)clear;

- (NSArray *)itemsForSection:(NSInteger)section;

- (BDModelSectionHeader *)sectionDeviderForSection:(NSInteger)section;

- (NSUInteger)numOfItemsInSection:(NSInteger)section;

- (NSUInteger)numSections;

@end

NS_ASSUME_NONNULL_END
