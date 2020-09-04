//
//  BDConfigViewerCell.h
//  ObjCExample
//
//  Created by 朱元清 on 2020/8/25.
//  Copyright © 2020 bytedance. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface BDConfigViewerCell : UITableViewCell
@property (weak, nonatomic) IBOutlet UILabel *configKeyLabel;
@property (weak, nonatomic) IBOutlet UITextField *configValueTextField;

@end

NS_ASSUME_NONNULL_END
