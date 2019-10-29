//
//  BDUIEventPicker.h
//  Applog
//
//  Created by bob on 2019/1/25.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 BDUIEventPicker 圈选SDK入口
 */
@interface BDUIEventPicker : NSObject

@property (nonatomic, strong, readonly) UIWindow *exposedWrapper;
@property (nonatomic, strong, readonly) UIButton *exposedPickerButton;

/*! @abstract  适配 iOS 13.0
 @discussion 如果App在iOS 13 使用了 UIWindowScene，则需要进行如下操作。
 如果App在iOS 13没有使用UIWindowScene，还是和之前的一样。
 */
/**
 // if use UIWindowSceneDelegate
 @implementation BDSceneDelegate<UIWindowSceneDelegate>

 - (void)scene:(UIScene *)scene willConnectToSession:(UISceneSession *)session options:(UISceneConnectionOptions *)connectionOptions {
     if ([scene isKindOfClass:[UIWindowScene class]] && ...) {
            ...
            UIWindowScene *ws = (UIWindowScene *)scene;
            [[BDUIEventPicker pickerWithAppID:@"appid"] showPicker];
            [BDUIEventPicker pickerWithAppID:@"appid"].exposedWrapper.windowScene = ws;
            [BDUIEventPicker pickerWithAppID:@"appid"].exposedPickerButton.window.windowScene = ws;
     }
 }
 @end

 // if use UIApplicationDelegate
 @implementation BDAppDelegate<UIApplicationDelegate>

 - (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
     [[BDUIEventPicker pickerWithAppID:@"appid"] showPicker];
     return YES;
 }
 */

/*! @abstract 圈选SDK单例
 @discussion 获取圈选SDK单例 注意，请先初始化 BDAutoTrack，才可以获取圈选实例
 @result 返回圈选SDK单例
 */
+ (nullable instancetype)pickerWithAppID:(NSString *)appID;

/*! @abstract 圈选SDK单例
@discussion 获取圈选SDK单例, 注意，请先初始化 BDAutoTrack，才可以获取圈选实例
@result 返回圈选SDK单例
*/
+ (nullable instancetype)picker;

/*! @abstract 展示圈选按钮
 @discussion 需要圈选的时候调用一次,适配 iOS 13.0请参考以下说明
 */
- (void)showPicker;

/*! @abstract 隐藏圈选按钮
 @discussion 不想要圈选的时候，调用一次
 */
- (void)hidePicker;

@end

NS_ASSUME_NONNULL_END
