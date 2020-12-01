//
//  BDAutoTrackSchemeHandler.h
//  RangersAppLog
//
//  Created by bob on 2019/9/24.
//

#import <Foundation/Foundation.h>
#import "BDCommonDefine.h"

NS_ASSUME_NONNULL_BEGIN

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

- (BOOL)handleURL:(NSURL *)URL appID:(NSString *)appID scene:(nullable id)scene;

- (void)registerHandler:(id<BDAutoTrackSchemeHandler>)handler;
- (void)unregisterHandler:(id<BDAutoTrackSchemeHandler>)handler;

@end

NS_ASSUME_NONNULL_END
