//
//  BDTesterIntroducerBase.h
//  ObjCExample
//
//  Created by 朱元清 on 2020/8/22.
//  Copyright © 2020 bytedance. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "BDFeedModelDictionary.h"

NS_ASSUME_NONNULL_BEGIN

/// TesterIntroducer的基类，本身不实例化。
/// 包括一个多section的tableView，用于介绍各种Tester VC。
@interface BDTesterIntroducerBase : UIViewController
@property (strong, nonatomic) UITableView *tableView;
@property (strong, nonatomic) BDFeedModelDictionary *modelObject;
@property (strong, nonatomic) NSMutableArray <BDFeedModel *> *feedModels;

/// override to register a different cell
- (void)registerTableViewCell;

/// override to provide a different cell reuse id
/// usually no need to override this
- (NSString *)cellReuseID1;
@end

NS_ASSUME_NONNULL_END
