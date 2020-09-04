//
//  BDHookCompatibilityTesterSuite.m
//  ObjCExample
//
//  Created by 朱元清 on 2020/8/21.
//  Copyright © 2020 bytedance. All rights reserved.
//

#import "BDHookCompatibilityTesterSuite.h"
#import "BDFeedModel.h"
#import "BDModelSectionHeader.h"
#import "BDAspectTesterImp.h"
#import "BDReactiveObjcTesterImp.h"


@interface BDHookCompatibilityTesterSuite ()

@end

@implementation BDHookCompatibilityTesterSuite

- (void)viewDidLoad {
    [super viewDidLoad];
    self.feedModels = [NSMutableArray arrayWithObjects:[
     [BDFeedModel alloc] initWithTitle:@"Aspect库兼容性测试" actionBlock:^{
        __auto_type vc = [[BDAspectTesterImp alloc] init];
        [self.navigationController pushViewController:vc animated:YES];
    }],
     [[BDFeedModel alloc] initWithTitle:@"ReactiveObjc库兼容性测试" actionBlock:^{
        __auto_type vc = [[BDReactiveObjcTesterImp alloc] init];
        [self.navigationController pushViewController:vc animated:YES];
    }],
     [[BDFeedModel alloc] initWithTitle:@"" actionBlock:^{
//        __auto_type vc = [[ alloc] init];
//        [self.navigationController pushViewController:vc animated:YES];
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
