//
//  BDBaseTableViewController.h
//  RangersAppLog
//
//  Created by bob on 2019/9/9.
//  Copyright © 2019 Bytedance. All rights reserved.
//

#import <UIKit/UIKit.h>

@class BDFeedModel;
NS_ASSUME_NONNULL_BEGIN

@interface BDBaseTableViewController : UITableViewController

@property (nonatomic, strong) NSArray<BDFeedModel *> *feedList;

@end

NS_ASSUME_NONNULL_END
