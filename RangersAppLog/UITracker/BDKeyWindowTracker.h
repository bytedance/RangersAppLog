//
//  BDKeyWindowTracker.h
//  RangersAppLog
//
//  Created by bob on 2019/8/12.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

UIKIT_EXTERN NSString * const BDDefaultSceneName;

@interface BDKeyWindowTracker : NSObject

/*! @abstract keyWindow for keyScene
 @discussion setter等同于调用`-[BDKeyWindowTracker trackScene:keyScene keyWindow:keyWindow]`
 @discussion getter等同于调用`-[BDKeyWindowTracker keyWindowForScene:keyScene]`
 @discussion 如果只有一个Scene，或者说没有Scene，比如低于iOS 13，则可以只使用keyWindow属性即可
 */
@property (nonatomic, strong) UIWindow *keyWindow;

/*! @abstract key Scene
 @discussion 默认值是 BDDefaultSceneName
 */
@property (atomic, copy) NSString *keyScene;

+ (instancetype)sharedInstance;

- (void)trackScene:(NSString *)name keyWindow:(nullable UIWindow *)keyWindow;
- (UIWindow *)keyWindowForScene:(NSString *)name;
- (void)removeKeyWindowForScene:(NSString *)name; // when you want set nil

@end

NS_ASSUME_NONNULL_END
