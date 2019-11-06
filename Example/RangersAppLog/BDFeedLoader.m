//
//  BDFeedLoader.m
//  RangersAppLog
//
//  Created by bob on 2019/9/9.
//  Copyright © 2019 Bytedance. All rights reserved.
//

#import "BDFeedLoader.h"
#import "BDFeedModel.h"
#import "BDAdapter.h"

@implementation BDFeedLoader

+ (NSArray<BDFeedModel *> *)loadDemoFeedList {
    NSMutableArray<BDFeedModel *> *array = [NSMutableArray array];
    
    [array addObject:({
        BDFeedModel *model = [BDFeedModel new];
        model.title = @"Login with an ID";
        model.actionBlock = ^{
            [BDAdapter login];
        };
        model;
    })];

    [array addObject:({
        BDFeedModel *model = [BDFeedModel new];
        model.title = @"Logout";
        model.actionBlock = ^{
            [BDAdapter logout];
        };
        model;
    })];

    [array addObject:({
        BDFeedModel *model = [BDFeedModel new];
        model.title = @"Read ABTest Value";
        model.actionBlock = ^{
            id value = [BDAdapter ABTestValue];
            NSLog(@"value read from ABTest:(%@)",value);
        };
        
        model;
    })];

    [array addObject:({
        BDFeedModel *model = [BDFeedModel new];
        model.title = @"report a event called test_event ";
        model.actionBlock = ^{
            [BDAdapter eventV3:@"test_event" params:nil];
        };

        model;
    })];

    [array addObject:({
        BDFeedModel *model = [BDFeedModel new];
        model.title = @"open rangersapplog";
        model.actionBlock = ^{
            NSURL *URL = [NSURL URLWithString:@"rangersapplog://xxx"];
            if ([[UIApplication sharedApplication] canOpenURL:URL]) {
                if (@available(iOS 10.0, *)) {
                    [[UIApplication sharedApplication] openURL:URL options:@{} completionHandler:^(BOOL success) {
                        NSLog(@"Open success");
                    }];
                } else {
                    
                }
            }
        };

        model;
    })];


    return array;
}

@end
