//
//  BDNativeH5TesterImpViewController.h
//  ObjCExample
//
//  Created by 朱元清 on 2020/9/23.
//  Copyright © 2020 bytedance. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

/// H5页面打通无埋点.
/// App内嵌的H5元素UI内的无埋点事件，通过App的无埋点上报渠道采集上报，从而和App关联起来。
/// 1. UIWebView
/// - H5页面要允许注入JS
/// - UIWebView需要设置delegate且delegate不为nil
/// @code
/// UIWebView *webView;
/// webView.delegate = delegate;
/// @endcode
/// 2. WKWebView
/// - WKWebView需要通过initWithFrame: configuration:方法初始化
/// - 如果自己重写初始化方法，请务必调用[[WKWebView alloc] initWithFrame: configuration:]方法
/// @code
/// WKWebView *webView = [[WKWebView alloc] initWithFrame:frame configuration:config];
/// @endcode
/// 上述操作完成之后再调用[webView loadRequest:request];
@interface BDNativeH5TesterImpViewController : UIViewController

@end

NS_ASSUME_NONNULL_END
