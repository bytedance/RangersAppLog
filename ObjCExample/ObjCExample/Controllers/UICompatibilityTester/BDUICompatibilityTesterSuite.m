//
//  BDUICompatibilityTesterSuite.m
//  ObjCExample
//
//  Created by 朱元清 on 2020/8/21.
//  Copyright © 2020 bytedance. All rights reserved.
//

#import "BDUICompatibilityTesterSuite.h"
#import "BDFeedModel.h"
#import "BDModelSectionHeader.h"
#import "BDIGListKitTesterImp.h"
#import "BDOverlapWindowTesterImp.h"
#import "BDSubviewToWindowTesterImp.h"

@interface BDUICompatibilityTesterSuite ()

@end

@implementation BDUICompatibilityTesterSuite

- (void)viewDidLoad {
    [super viewDidLoad];
    
    self.title = @"UI兼容性测试";
    
    self.feedModels = [NSMutableArray arrayWithObjects:[
     [BDFeedModel alloc] initWithTitle:@"IGListKit" actionBlock:^{
        __auto_type vc = [[BDIGListKitTesterImp alloc] init];
        [self.navigationController pushViewController:vc animated:YES];
    }],
     [[BDFeedModel alloc] initWithTitle:@"overlapped window" actionBlock:^{
        __auto_type vc = [[BDOverlapWindowTesterImp alloc] init];
        [self.navigationController pushViewController:vc animated:YES];
    }],
     [[BDFeedModel alloc] initWithTitle:@"add buttons as window's subviews" actionBlock:^{
        __auto_type vc = [[BDSubviewToWindowTesterImp alloc] init];
        [self.navigationController pushViewController:vc animated:YES];
    }],
     nil
     ];
}

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

@end
