//
//  BDBaseTableViewController.m
//  RangersAppLog
//
//  Created by bob on 2019/9/9.
//  Copyright © 2019 Bytedance. All rights reserved.
//

#import "BDBaseTableViewController.h"
#import "BDAdapter.h"
#import "BDFeedLoader.h"
#import "BDFeedModel.h"

static NSString * const CellReuseIdentifier = @"UITableViewCell_";

@interface BDBaseTableViewController ()

@end

@implementation BDBaseTableViewController

- (void)loadView {
    [super loadView];
    self.feedList = @[];
    [self.tableView registerClass:[UITableViewCell class] forCellReuseIdentifier:CellReuseIdentifier];
}

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return self.feedList.count;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    BDFeedModel *model = [self.feedList objectAtIndex:indexPath.row];
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CellReuseIdentifier];
    if (!cell) {
        cell = [[UITableViewCell alloc] initWithStyle:(UITableViewCellStyleDefault) reuseIdentifier:CellReuseIdentifier];
    }
    cell.textLabel.text = [NSString stringWithFormat:@"%zd: %@",(NSInteger)(indexPath.row + 1),model.title];

    return cell;
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath {
    return 44;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    BDFeedModel *model = [self.feedList objectAtIndex:indexPath.row];

    if (model.actionBlock) {
        model.actionBlock();
    } else if (model.nextVCName.length) {
        UIViewController *vc = [NSClassFromString(model.nextVCName) new];
        if (vc) {
            [self.navigationController pushViewController:vc animated:YES];
        }
    }

//    [BDAdapter eventV3:@"cellClick" params:@{@"text":model.title?:@""}];
}


@end
