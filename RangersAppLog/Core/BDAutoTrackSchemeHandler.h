//
//  BDAutoTrackSchemeHandler.h
//  RangersAppLog
//
//  Created by bob on 2019/9/24.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@protocol BDAutoTrackSchemeHandler <NSObject>

/*! @abstract 处理scheme
 @discussion 请参考下面接口调用示例
 @param URL scheme的完整URL，透传参数
 @param appID 初始化SDK的AppID
 @param scene 适配iOS 13的参数，透传参数
 @result 返回YES，表示已经处理了该URL，NO表示没有处理
*/
- (BOOL)handleURL:(NSURL *)URL appID:(NSString *)appID scene:(nullable id)scene;

@end

/* 如果是iOS 13中重写UISceneDelegate的回调，则按照i以下code
- (void)scene:(UIScene *)scene openURLContexts:(NSSet<UIOpenURLContext *> *)URLContexts {
    for (UIOpenURLContext *context in URLContexts) {
        NSURL *URL = context.URL;
        if ([[BDAutoTrackSchemeHandler sharedHandler] handleURL:URL appID:@"appid" scene:scene]) {
            continue;
        }

        /// your handle code for the URL
    }
}

如果是iOS 13一下，重写UIApplicationDelegate的回调方法，则参考以下code
- (BOOL)application:(UIApplication *)app openURL:(NSURL *)url options:(NSDictionary<UIApplicationOpenURLOptionsKey, id> *)options {
    if ([[BDAutoTrackSchemeHandler sharedHandler] handleURL:url appID:@"appid" scene:nil]) {
        return YES;
    }

    /// your handle code

    return NO;
}
*/

@interface BDAutoTrackSchemeHandler : NSObject<BDAutoTrackSchemeHandler>

+ (instancetype)sharedHandler;

- (void)registerHandler:(id<BDAutoTrackSchemeHandler>)handler;
- (void)unregisterHandler:(id<BDAutoTrackSchemeHandler>)handler;

@end

NS_ASSUME_NONNULL_END
