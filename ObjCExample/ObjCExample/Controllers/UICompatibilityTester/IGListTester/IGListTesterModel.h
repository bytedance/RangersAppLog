//
//  IGListTesterModel.h
//  ObjCExample
//
//  Created by 朱元清 on 2020/8/23.
//  Copyright © 2020 bytedance. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface IGListTesterModel : NSObject
@property (strong, nonatomic, readonly) NSString *uuid;
@property (strong, nonatomic) NSString *picName;

- (instancetype)initWithPictureName:(NSString *)picName;
@end

NS_ASSUME_NONNULL_END
