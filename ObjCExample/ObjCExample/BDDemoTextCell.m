//
//  BDDemoTextCell.m
//  BDAutoTracker_Example
//
//  Created by bob on 2019/4/17.
//  Copyright © 2019 ByteDance. All rights reserved.
//

#import "BDDemoTextCell.h"

@interface BDDemoTextCell ()

@property (nonatomic, strong) UILabel *extraLabel;

@end

@implementation BDDemoTextCell

- (instancetype)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(NSString *)reuseIdentifier {
    if (self = [super initWithStyle:style reuseIdentifier:reuseIdentifier]) {
        UILabel *extraLabel = [[UILabel alloc] initWithFrame:self.contentView.bounds];
        extraLabel.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight;
        extraLabel.textAlignment = NSTextAlignmentCenter;
        extraLabel.textColor = [UIColor blueColor];
        [self.contentView addSubview: extraLabel];
        self.extraLabel = extraLabel;
    }

    return self;
}



@end
