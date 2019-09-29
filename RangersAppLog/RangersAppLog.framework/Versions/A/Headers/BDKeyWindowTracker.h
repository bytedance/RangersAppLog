//
//  BDKeyWindowTracker.h
//  RangersAppLog
//
//  Created by bob on 2019/8/12.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

UIKIT_EXTERN NSString * const BDDefaultScene;

@interface BDKeyWindowTracker : NSObject

/*! @abstract keyWindow for BDDefaultScene
 @discussion setter等同于调用`-[BDKeyWindowTracker trackScene:BDDefaultScene keyWindow:keyWindow]`
 @discussion getter等同于调用`-[BDKeyWindowTracker keyWindowForScene:BDDefaultScene]`
 @discussion 如果只有一个Scene，或者说没有Scene，比如低于iOS 13，则可以只使用keyWindow属性即可
 */
@property (nonatomic, strong, nullable) UIWindow *keyWindow;

+ (instancetype)sharedInstance;

/*! @abstract 设置scene的keywindow
 @discussion 发生变化可以更新，不需要一直重复设置
 @param scene 某个UIWindowScene的唯一标志，推荐使用 scene = [NSString stringWithFormat:@"%p",windowScene];
 @param keyWindow 该scene的keywindow
*/
- (void)trackScene:(NSString *)scene keyWindow:(nullable UIWindow *)keyWindow;

/*! @abstract 获取该scene的keywindow
 @param scene 某个UIWindowScene的唯一标志，推荐使用 scene = [NSString stringWithFormat:@"%p",windowScene];
 @result keyWindow 返回该scene的keywindow
*/
- (nullable UIWindow *)keyWindowForScene:(NSString *)scene;

/*! @abstract 移除scene的keywindow
 @param scene 某个UIWindowScene的唯一标志，推荐使用 scene = [NSString stringWithFormat:@"%p",windowScene];
*/
- (void)removeKeyWindowForScene:(NSString *)scene; /// when you want set nil

@end

NS_ASSUME_NONNULL_END
