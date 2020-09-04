//
//  BDOverlapWindowTesterImp.m
//  ObjCExample
//
//  Created by 朱元清 on 2020/8/21.
//  Copyright © 2020 bytedance. All rights reserved.
//

#import "BDOverlapWindowTesterImp.h"
#import "BDColors.h"

@interface BDOverlapWindowTesterImp ()
@property (strong, nonatomic) UIWindow *overlappedWindow;
@end

@implementation BDOverlapWindowTesterImp

- (void)viewDidLoad {
    [super viewDidLoad];
    self.view.backgroundColor = [[BDColors sharedInstance] lightRed];
    
    self.overlappedWindow.hidden = false;
}

#pragma mark - getter
- (UIWindow *)overlappedWindow {
    if (!_overlappedWindow) {
        UIImage *img = [UIImage imageNamed:@"cenci"];
        CGFloat imgWidth = img.size.width, imgHeight = img.size.height;
        UIImageView *imgView = [[UIImageView alloc] initWithImage:img];
        
        UIWindow *keyWindow = [UIApplication.sharedApplication keyWindow];
        CGFloat keyWindowWidth = keyWindow.bounds.size.width;
        
        CGRect frame = CGRectMake(0, 150, keyWindowWidth, keyWindowWidth / imgWidth * imgHeight);
        _overlappedWindow = [[UIWindow alloc] initWithFrame:frame];
        
        imgView.frame = CGRectMake(0, 0, frame.size.width, frame.size.height);
        
        [_overlappedWindow addSubview:imgView];
    }
    return _overlappedWindow;
}

@end
