//
//  BDUITrackTesterImp.m
//  ObjCExample
//
//  Created by 朱元清 on 2020/8/21.
//  Copyright © 2020 bytedance. All rights reserved.
//

#import "BDUITrackTesterImp.h"

@interface BDUITrackTesterImp ()

@end

@implementation BDUITrackTesterImp

- (void)viewDidLoad {
    [super viewDidLoad];
    self.title = self.shouldTestPicker ? @"圈选测试" : @"无埋点测试";
    
    CGRect frame =  self.navigationController.navigationBar.frame;
    CGFloat top = frame.origin.y + frame.size.height;
    CGRect newFrame = self.view.frame;
    newFrame.origin.y = top;
    newFrame.size.height -= top;
    [self.view setFrame:newFrame]; // bug：UI被NavBar覆盖了
    
    if(self.shouldTestPicker) {
        // todo
    }
}



@end
