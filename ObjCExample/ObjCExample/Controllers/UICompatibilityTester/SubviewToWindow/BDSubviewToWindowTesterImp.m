//
//  BDSubviewToWindowTesterImp.m
//  ObjCExample
//
//  Created by 朱元清 on 2020/8/24.
//  Copyright © 2020 bytedance. All rights reserved.
//

#import "BDSubviewToWindowTesterImp.h"
#import "BDColors.h"

@interface BDSubviewToWindowTesterImp ()

@property (weak, nonatomic) UIWindow *keyWindow;
@property (weak, nonatomic) UIButton *button1;
@property (weak, nonatomic) UIButton *button2;

@end

@implementation BDSubviewToWindowTesterImp

- (void)viewDidLoad {
    [super viewDidLoad];
    self.view.backgroundColor = [BDColors.sharedInstance lightGreen];
    [self addTestButtonInWindow:self.keyWindow];
    
}

- (void)addTestButtonInWindow:(UIWindow *)window {
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(0.5 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        CGFloat top = window.bounds.size.height - 144;
        CGFloat left = (window.bounds.size.width - 200)/2;
        UIButton *button = [[UIButton alloc] initWithFrame:CGRectMake(left, top, 200, 44)];
        button.backgroundColor = [BDColors.sharedInstance lightBlue];
        [button setTitle:@"Button 2" forState:(UIControlStateNormal)];
        [button addTarget:self action:@selector(handleButtonEvent:) forControlEvents:(UIControlEventTouchUpInside)];
        self.button1 = button;
        [window addSubview:button];

        top -= 60;
        button = [[UIButton alloc] initWithFrame:CGRectMake(left, top, 200, 44)];
        button.backgroundColor = [BDColors.sharedInstance lightBlue];
        [button setTitle:@"Button 1" forState:(UIControlStateNormal)];
        [button addTarget:self action:@selector(handleButtonEvent:) forControlEvents:(UIControlEventTouchUpInside)];
        self.button2 = button;
        [window addSubview:button];
    });
}

- (void)viewWillDisappear:(BOOL)animated {
    [self.button1 removeFromSuperview];
    [self.button2 removeFromSuperview];
}

#pragma mark - handlers
- (void)handleButtonEvent:(UIButton *)sender {
    NSLog(@"%@ is touched", sender.class);
}

#pragma mark - getter
- (UIWindow *)keyWindow {
    return [UIApplication.sharedApplication keyWindow];
}


@end
