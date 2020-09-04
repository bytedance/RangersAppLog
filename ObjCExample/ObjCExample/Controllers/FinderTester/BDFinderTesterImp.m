//
//  BDFinderTesterImp.m
//  ObjCExample
//
//  Created by 朱元清 on 2020/8/21.
//  Copyright © 2020 bytedance. All rights reserved.
//

#import "BDFinderTesterImp.h"
#import "BDFeedModel.h"
#import "BDAdapter.h"
#import <RangersAppLog/RangersAppLog.h>

@interface BDFinderTesterImp ()


@end

static NSString *cellReuseID = @"finderTester_1";

@implementation BDFinderTesterImp

- (void)viewDidLoad {
    [super viewDidLoad];
    self.title = @"Finder场景测试页";
    
    NSDictionary *sharedParams = @{
        @"from": @"testerFinder"
    };
    
    self.feedModels = [NSMutableArray arrayWithObjects:
        [[BDFeedModel alloc] initWithTitle:@"注册" actionBlock:^{
            [BDAutoTrack eventV3:@"user_register" params:sharedParams];
        }],
        [[BDFeedModel alloc] initWithTitle:@"登录" actionBlock:^{
            [BDAutoTrack eventV3:@"user_login" params:sharedParams];
        }],
        [[BDFeedModel alloc] initWithTitle:@"绑定社交账号" actionBlock:^{
            [BDAutoTrack eventV3:@"user_bind_social_account" params:sharedParams];
        }],
        [[BDFeedModel alloc] initWithTitle:@"打开视频" actionBlock:^{
            [BDAutoTrack eventV3:@"user_open_video" params:sharedParams];
        }],
        [[BDFeedModel alloc] initWithTitle:@"点赞" actionBlock:^{
            [BDAutoTrack eventV3:@"user_like" params:sharedParams];
        }],
        [[BDFeedModel alloc] initWithTitle:@"评论" actionBlock:^{
            [BDAutoTrack eventV3:@"user_comment" params:sharedParams];
        }],
        [[BDFeedModel alloc] initWithTitle:@"分享" actionBlock:^{
            [BDAutoTrack eventV3:@"user_share" params:sharedParams];
        }],
        [[BDFeedModel alloc] initWithTitle:@"创建订单" actionBlock:^{
            [BDAutoTrack eventV3:@"user_place_order" params:sharedParams];
        }],
        [[BDFeedModel alloc] initWithTitle:@"支付" actionBlock:^{
            [BDAutoTrack eventV3:@"user_payment" params:sharedParams];
        }],
        [[BDFeedModel alloc] initWithTitle:@"购买虚拟物品" actionBlock:^{
            [BDAutoTrack eventV3:@"user_purchase_virtual_item" params:sharedParams];
        }],
        nil
    ];
}


@end

