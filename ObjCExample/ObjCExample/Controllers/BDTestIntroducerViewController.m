//
//  BDTestIntroducerViewController.m
//  rangersAppLogObjCExample
//
//  Created by 朱元清 on 2020/8/17.
//  Copyright © 2020 bytedance. All rights reserved.
//  各测试项的分流入口

#import "BDFeedModel.h"
#import "BDFeedModelDictionary.h"
#import "BDTesterControllers.h"


@interface BDTestIntroducerViewController ()

@end

static NSString *cellReuseID = @"testIntro_1";

@implementation BDTestIntroducerViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.title = @"导航首页";
}

#pragma mark - getter
// 重写父类的getter
- (NSMutableArray *)feedModels {
    NSMutableArray *models = [super feedModels];
    if (!models) {
        __weak typeof(self) wself = self;
        NSArray *tmpModels = @[
            [[BDModelSectionHeader alloc] initWithSectionName:@"功能测试" desc:@""],
            [[BDFeedModel alloc] initWithTitle:@"测试DataFinder功能" actionBlock:^{
                __auto_type vc = [[BDFinderTesterImp alloc] init];
                [wself.navigationController pushViewController:vc animated:YES];
            }],
            [[BDFeedModel alloc] initWithTitle:@"测试DataPlayer功能" actionBlock:^{
                __auto_type vc = [[BDPlayerTesterImp alloc] init];
                [wself.navigationController pushViewController:vc animated:YES];
            }],
            [[BDFeedModel alloc] initWithTitle:@"测试圈选" actionBlock:^{
                __auto_type vc = [[BDUITrackTesterImp alloc] init];
                vc.shouldTestPicker = true;
                [wself.navigationController pushViewController:vc animated:YES];
            }],
            [[BDFeedModel alloc] initWithTitle:@"测试无埋点" actionBlock:^{
                __auto_type vc = [[BDUITrackTesterImp alloc] initWithNibName:@"BDUITrackTesterImp" bundle:NSBundle.mainBundle];
                vc.shouldTestPicker = false;
                [wself.navigationController pushViewController:vc animated:YES];
            }],
            
            [[BDModelSectionHeader alloc] initWithSectionName:@"兼容性测试" desc:@""],
            [[BDFeedModel alloc] initWithTitle:@"测试UI库兼容性" actionBlock:^{
                __auto_type vc = [[BDUICompatibilityTesterSuite alloc] init];
                [wself.navigationController pushViewController:vc animated:YES];
            }],
            [[BDFeedModel alloc] initWithTitle:@"测试Hook库兼容性" actionBlock:^{
                __auto_type vc = [[BDHookCompatibilityTesterSuite alloc] init];
                [wself.navigationController pushViewController:vc animated:YES];
            }],
            [[BDFeedModel alloc] initWithTitle:@"测试竞品SDK兼容性" actionBlock:^{}],
            
            [[BDModelSectionHeader alloc] initWithSectionName:@"查看SDK配置参数" desc:@""],
            [[BDFeedModel alloc] initWithTitle:@"查看初始化配置" actionBlock:^{
                __auto_type vc = [[BDTesterSDKConfigViewer alloc] init];
                [wself.navigationController pushViewController:vc animated:YES];
            }]
        ];
        
        models = [NSMutableArray arrayWithArray:tmpModels];
        [self setFeedModels:models];
    }
    return models;
}


@end
