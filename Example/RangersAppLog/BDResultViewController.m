//
//  BDResultViewController.m
//  RangersAppLog
//
//  Created by bob on 2019/11/9.
//  Copyright © 2019 Bytedance. All rights reserved.
//

#import "BDResultViewController.h"
#import "BDAdapter.h"
#import "BDFeedModel.h"

static NSString * const CellReuseIdentifier = @"UITableViewCell_";

@interface BDResultViewController ()

@end

@implementation BDResultViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.feedList = [[BDAdapter sharedInstance].events copy];
    self.navigationItem.title = @"Result";
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    BDFeedModel *model = [self.feedList objectAtIndex:indexPath.row];
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CellReuseIdentifier];
    if (!cell) {
        cell = [[UITableViewCell alloc] initWithStyle:(UITableViewCellStyleDefault) reuseIdentifier:CellReuseIdentifier];
    }
    cell.textLabel.text = [NSString stringWithFormat:@"%zd:%zd:%@",model.eventIndex, model.state ,model.methodName];

    return cell;
}

@end
