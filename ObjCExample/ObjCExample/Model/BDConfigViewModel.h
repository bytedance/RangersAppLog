//
//  BDConfigViewModel.h
//  ObjCExample
//
//  Created by 朱元清 on 2020/8/25.
//  Copyright © 2020 bytedance. All rights reserved.
//

#import "BDAbstractModel.h"

NS_ASSUME_NONNULL_BEGIN

@interface BDConfigViewModel : BDAbstractModel

@property (strong, nonatomic) NSString *configKey;
@property (strong, nonatomic) NSString *configValue;

- (instancetype)initWithConfigKey:(NSString *)configKey value:(NSString *)value;
@end

NS_ASSUME_NONNULL_END
