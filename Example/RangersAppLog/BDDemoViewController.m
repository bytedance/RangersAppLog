//
//  BDDemoViewController.m
//  RangersAppLog
//
//  Created by bob on 2019/9/9.
//  Copyright © 2019 Bytedance. All rights reserved.
//

#import "BDDemoViewController.h"
#import "BDFeedModel.h"
#import "BDFeedLoader.h"

@interface BDDemoViewController ()

@end

@implementation BDDemoViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.feedList = [BDFeedLoader loadDemoFeedList];
    self.navigationItem.title = @"Demo";
}

@end
