//
//  BDPlayerTesterImp.m
//  ObjCExample
//
//  Created by 朱元清 on 2020/8/21.
//  Copyright © 2020 bytedance. All rights reserved.
//

#import "BDPlayerTesterImp.h"
#import "BDAutoTrack+Game.h"
#import "BDFeedModel.h"
#import "BDAdapter.h"
#import <RangersAppLog/RangersAppLog.h>

@interface BDPlayerTesterImp ()

@end

static NSString *cellReuseID = @"playerTester_1";

@implementation BDPlayerTesterImp

- (void)viewDidLoad {
    [super viewDidLoad];
    
    self.title = @"Player场景测试页";
    
    NSDictionary *sharedParams = @{
        @"from": @"testerPlayer"
    };
    static int level = 1;
    self.feedModels = [NSMutableArray arrayWithObjects:
        [[BDFeedModel alloc] initWithTitle:@"注册" actionBlock:^{
            [BDAutoTrack registerEventByMethod:@"wechat" isSuccess:YES];
        }],
        [[BDFeedModel alloc] initWithTitle:@"登陆" actionBlock:^{
            [BDAutoTrack loginEventByMethod:@"wechat" isSuccess:YES];
        }],
        [[BDFeedModel alloc] initWithTitle:@"绑定社交账号" actionBlock:^{
            [BDAutoTrack accessAccountEventByType:@"weibo" isSuccess:YES];
        }],
        [[BDFeedModel alloc] initWithTitle:@"游戏初始化" actionBlock:^{
            [BDAutoTrack eventV3:@"game_initialized" params:sharedParams];
        }],
        [[BDFeedModel alloc] initWithTitle:@"开始游戏" actionBlock:^{
            [BDAutoTrack eventV3:@"game_started" params:sharedParams];
        }],
        [[BDFeedModel alloc] initWithTitle:@"结束游戏" actionBlock:^{
            [BDAutoTrack eventV3:@"game_ended" params:sharedParams];
        }],
        [[BDFeedModel alloc] initWithTitle:@"升级" actionBlock:^{
            level += 1;
            [BDAutoTrack updateLevelEventWithLevel:level];
        }],
        [[BDFeedModel alloc] initWithTitle:@"开始展示广告位" actionBlock:^{
            [BDAutoTrack eventV3:@"start_display_ad" params:sharedParams];
        }],
        [[BDFeedModel alloc] initWithTitle:@"点击广告位" actionBlock:^{
            [BDAutoTrack eventV3:@"click_ad" params:sharedParams];
        }],
        [[BDFeedModel alloc] initWithTitle:@"结束展示广告位" actionBlock:^{
            [BDAutoTrack eventV3:@"end_display_ad" params:sharedParams];
        }],
        [[BDFeedModel alloc] initWithTitle:@"获取游戏币" actionBlock:^{
            [BDAutoTrack eventV3:@"acquire_game_coins" params:sharedParams];
        }],
        [[BDFeedModel alloc] initWithTitle:@"加入购物车" actionBlock:^{
            [BDAutoTrack addCartEventWithContentType:@"内购"
                                         contentName:@"传奇武器"
                                           contentID:@"contentId1234"
                                       contentNumber:1
                                           isSuccess:YES];
        }],
        [[BDFeedModel alloc] initWithTitle:@"提交购买/下单" actionBlock:^{
            [BDAutoTrack checkoutEventWithContentType:@"内购"
                                          contentName:@"传奇武器" contentID:@"contentId1234"
                                        contentNumber:100
                                    isVirtualCurrency:YES
                                      virtualCurrency:@"游戏币"
                                             currency:@"RMB"
                                      currency_amount:1
                                            isSuccess:YES];
        }],
        [[BDFeedModel alloc] initWithTitle:@"支付" actionBlock:^{
            [BDAutoTrack purchaseEventWithContentType:@"内购"
                                          contentName:@"传奇武器"
                                            contentID:@"contentId1234"
                                        contentNumber:100
                                       paymentChannel:@"App Store"
                                             currency:@"RMB" currency_amount:1 isSuccess:YES];
        }],
        [[BDFeedModel alloc] initWithTitle:@"自定义V3事件" actionBlock:^{
            [BDAdapter eventV3:@"player_custom_V3_event" params:@{@"from": @"playerTester"}];
        }],
        nil
    ];
}



@end
