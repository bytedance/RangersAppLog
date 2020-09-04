//
//  BDTesterSDKConfigViewer.m
//  ObjCExample
//
//  Created by 朱元清 on 2020/8/25.
//  Copyright © 2020 bytedance. All rights reserved.
//

#import "BDTesterSDKConfigViewer.h"
#import "BDConfigViewModel.h"
#import "BDFeedModel.h"

@interface BDTesterSDKConfigViewer ()

@end

@implementation BDTesterSDKConfigViewer

- (void)viewDidLoad {
    [super viewDidLoad];
    self.feedModels = [NSMutableArray arrayWithObjects:
                       [[BDFeedModel alloc] initWithTitle:@"" actionBlock:nil],
                       nil];
}

- (void)registerTableViewCell {
    [super registerTableViewCell];
//    UINib *nib = [UINib nibWithNibName:@"BDConfigViewerCell" bundle:nil];
//    [self.tableView registerNib:nib forCellReuseIdentifier:[self cellReuseID1]];
}

#pragma mark - table view delegate


/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

@end
