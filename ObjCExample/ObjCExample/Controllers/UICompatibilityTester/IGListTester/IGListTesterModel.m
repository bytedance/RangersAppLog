//
//  IGListTesterModel.m
//  ObjCExample
//
//  Created by 朱元清 on 2020/8/23.
//  Copyright © 2020 bytedance. All rights reserved.
//

#import "IGListTesterModel.h"
#import <IGListKit.h>

@interface IGListTesterModel () <IGListDiffable>

@end

@implementation IGListTesterModel

- (instancetype)init {
    self = [super init];
    if (self) {
        _uuid = NSUUID.UUID.UUIDString;
    }
    return self;
}

- (instancetype)initWithPictureName:(NSString *)picName {
    self = [self init];
    if (self) {
        _picName = picName;
    }
    return self;
}

#pragma mark - IGListDiffable
- (nonnull id<NSObject>)diffIdentifier {
    return self.uuid;
}

- (BOOL)isEqualToDiffableObject:(nullable NSObject<IGListDiffable> *)object {
    if ([object isKindOfClass:IGListTesterModel.class]) {
        return false;
    }
    
    return [self.uuid isEqualToString:((IGListTesterModel *)object).uuid];
}

@end
