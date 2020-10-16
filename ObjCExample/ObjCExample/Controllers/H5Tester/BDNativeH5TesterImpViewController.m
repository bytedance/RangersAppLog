//
//  BDNativeH5TesterImpViewController.m
//  ObjCExample
//
//  Created by 朱元清 on 2020/9/23.
//  Copyright © 2020 bytedance. All rights reserved.
//

#import "BDNativeH5TesterImpViewController.h"
#import <WebKit/WebKit.h>

@interface BDNativeH5TesterImpViewController () <WKUIDelegate, WKNavigationDelegate>

@property (strong, nonatomic) WKWebView *webView;

@end

@implementation BDNativeH5TesterImpViewController

- (WKWebView *)webView {
    if (!_webView) {
        WKWebViewConfiguration *webViewConfig = [[WKWebViewConfiguration alloc] init];
        _webView = [[WKWebView alloc] initWithFrame:CGRectZero configuration:webViewConfig];
        _webView.UIDelegate = self;
        _webView.navigationDelegate = self;
    }
    return _webView;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    self.view.backgroundColor = [UIColor whiteColor];
    
    NSString *htmlFilePath = [NSBundle.mainBundle pathForResource:@"h5_page" ofType:@"html"];
    NSString *htmlContent = [NSString stringWithContentsOfFile:htmlFilePath encoding:NSUTF8StringEncoding error:nil];
    [self.webView loadHTMLString:htmlContent baseURL:nil];
    
    self.view = self.webView;
}

- (void)webView:(WKWebView *)webView didFinishNavigation:(WKNavigation *)navigation {
    // 页面加载完成
    NSString *script = [NSString stringWithFormat:@"document.querySelector('#webview_class').innerHTML='本H5页面使用%@';", NSStringFromClass([self.webView class])];
    [self.webView evaluateJavaScript:script
               completionHandler:^(id _Nullable ret, NSError * _Nullable error) {
//        NSLog(@"%@", ret);
    }];
}

@end
