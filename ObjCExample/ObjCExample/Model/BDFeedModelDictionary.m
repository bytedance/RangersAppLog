//
//  BDFeedModelDictionary.m
//  ObjCExample
//
//  Created by 朱元清 on 2020/8/22.
//  Copyright © 2020 bytedance. All rights reserved.
//  TODO: 1. 生成公共API签名 Done.  2. 单元测试

#import "BDFeedModelDictionary.h"

@interface BDFeedModelDictionary ()
@property (strong, nonatomic) NSMutableDictionary <NSNumber *, BDModelSectionHeader *> *sectionMetaMap;
@property (strong, nonatomic) NSMutableDictionary <NSNumber *, NSMutableArray<BDAbstractModel *> *> *sectionItemMap;

@end

@implementation BDFeedModelDictionary

#pragma mark - create and modify
- (instancetype)initWithModelArray:(NSArray *)array {
    self = [super init];
    if (self) {
        if (array && array.count > 0) {  // 第一个 section devider 单独处理
            NSObject *obj = array[0];
            if (![obj isKindOfClass:BDModelSectionHeader.class]) {
                // 用户没有提供第一个默认section devider，我们帮他加上
                BDModelSectionHeader *firstDevider = [[BDModelSectionHeader alloc] initWithSectionName:@"default section" desc:@""];
                array = [@[firstDevider] arrayByAddingObjectsFromArray:array];
            }
        }
        
        NSInteger countSection = 0;
        for (int i = 0; i < array.count; ++i) {
            NSObject *obj = [array objectAtIndex:i];
            
            if ([obj isKindOfClass:BDModelSectionHeader.class]) {
                [self setSectionDevider:(BDModelSectionHeader *)obj ToSection:countSection];
                for (int j = i + 1; j < array.count; ++j) {
                    obj = [array objectAtIndex:j];
                    if ([obj isKindOfClass:BDAbstractModel.class]) {
                        [self appendItem:(BDAbstractModel *)obj
                               ToSection:countSection];
                    } else if ([obj isKindOfClass:BDModelSectionHeader.class]) {
                        i = j - 1;
                        break;
                    } else if (j == array.count - 1) {
                        i = j;
                        break;
                    }
                }
                ++countSection;
            }
        } // end for
    }
    return self;
}

- (BOOL)setSectionDevider:(BDModelSectionHeader *)sectionDevider ToSection:(NSInteger)section {
    if (!sectionDevider) {
        return NO;
    }
    [self.sectionMetaMap setObject:sectionDevider forKey:@(section)];
    return YES;
}

- (BOOL)appendItem:(BDAbstractModel *)item ToSection:(NSInteger)section {
    if (!item) {
        return NO;
    }
    NSMutableArray *mArray = [self __itemsForSection:section];
    [mArray addObject:item];
    return YES;
}

- (BOOL)appendItems:(NSArray *)items ToSection:(NSInteger)section {
    NSMutableArray *mArray = [self __itemsForSection:section];
    [mArray addObjectsFromArray:items];
    return YES;
}

- (BOOL)clear {
    self.sectionItemMap = nil;
    self.sectionMetaMap = nil;
    return YES;
}

#pragma mark - table view query
/// 返回特定section的model数据
/// 注意不要直接修改返回的数组，任何修改必须通过本类的public API来完成。
/// @param section section index
- (NSArray *)itemsForSection:(NSInteger)section {
    NSMutableArray *items = [self __itemsForSection:section];
    return items;
}

- (BDModelSectionHeader *)sectionDeviderForSection:(NSInteger)section {
    BDModelSectionHeader *sectionDevider = [self.sectionMetaMap objectForKey:@(section)];
    return sectionDevider;
}

- (NSUInteger)numOfItemsInSection:(NSInteger)section {
    NSMutableArray *items = [self.sectionItemMap objectForKey:@(section)];
    return items.count;
}

- (NSUInteger)numSections {
    return [self.sectionItemMap count];
}

/* private method */
#pragma mark - private
- (NSMutableArray *)__itemsForSection:(NSInteger)section {
    if (![self.sectionItemMap objectForKey:@(section)]) {
        [self.sectionItemMap setObject:[NSMutableArray new] forKey:@(section)];
    }
    return [self.sectionItemMap objectForKey:@(section)];
}

#pragma mark - getter
- (NSMutableDictionary<NSNumber *,BDModelSectionHeader *> *)sectionMetaMap {
    if (!_sectionMetaMap) {
        _sectionMetaMap = [NSMutableDictionary new];
    }
    return _sectionMetaMap;
}

- (NSMutableDictionary<NSNumber *, NSMutableArray<BDAbstractModel *> *> *)sectionItemMap {
    if (!_sectionItemMap) {
        _sectionItemMap = [NSMutableDictionary new];
    }
    return _sectionItemMap;
}


@end
