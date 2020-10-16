//
//  BDProfileAPITesterImp.m
//  ObjCExample
//
//  Created by 朱元清 on 2020/9/14.
//  Copyright © 2020 bytedance. All rights reserved.
//

#import "BDProfileAPITesterImp.h"
#import "BDModelSectionHeader.h"
#import "BDProfileAPITester_UI.h"
#import <RangersAppLog/RangersAppLog.h>

static NSString *cellReuseID = @"finderTester_1";

@interface BDProfileAPITesterImp ()

@end

@implementation BDProfileAPITesterImp

- (void)viewDidLoad {
    [super viewDidLoad];
    self.title = @"Profile API测试页";
    
    NSDictionary *profileDict = @{@"user_level": @(100),
                                  @"interests": @[@"跑团", @"爬山", @"看书"]};
    __block int noInterest = 1;
    __weak BDAutoTrack *sharedTrack = [BDAutoTrack sharedTrack];
    __weak typeof(self) wself = self;
    self.feedModels = [NSMutableArray arrayWithObjects:
        [[BDFeedModel alloc] initWithTitle:@"切换user unique id（重新注册激活）" actionBlock:^{
            [sharedTrack setCurrentUserUniqueID:NSUUID.UUID.UUIDString];
        }],
       [[BDFeedModel alloc] initWithTitle:@"进入测试UI" actionBlock:^{
        __auto_type vc = [[BDProfileAPITester_UI alloc] init];
        [wself.navigationController pushViewController:vc animated:YES];
       }],
                       
//       [[BDModelSectionHeader alloc] initWithSectionName:@"set" desc:@""],
//        [[BDFeedModel alloc] initWithTitle:@"set" actionBlock:^{
//            [sharedTrack profileSet:profileDict];
//        }],
//
//       [[BDModelSectionHeader alloc] initWithSectionName:@"setOnce" desc:@""],
//        [[BDFeedModel alloc] initWithTitle:@"setOnce" actionBlock:^{
//            [sharedTrack profileSetOnce:profileDict];
//        }],
//
//
//       [[BDModelSectionHeader alloc] initWithSectionName:@"Increment" desc:@""],
//        [[BDFeedModel alloc] initWithTitle:@"Increment" actionBlock:^{
//            [sharedTrack profileIncrement:@{@"user_level": @(2)}];
//        }],
//
//        [[BDModelSectionHeader alloc] initWithSectionName:@"Append" desc:@""],
//        [[BDFeedModel alloc] initWithTitle:@"Append" actionBlock:^{
//            [sharedTrack profileAppend:@{
//                @"interests": [@"habbit-" stringByAppendingString:@(noInterest++).stringValue]
//            }];
//        }],
//
//       [[BDModelSectionHeader alloc] initWithSectionName:@"Unset" desc:@""],
//        [[BDFeedModel alloc] initWithTitle:@"Unset" actionBlock:^{
//            [sharedTrack profileUnset:@"user_level"];
//            [sharedTrack profileUnset:@"interests"];
//        }],
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
