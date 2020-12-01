//
//  UIBarButtonItem+TrackInfo.h
//  Applog
//
//  Created by bob on 2019/1/21.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface UIBarButtonItem (TrackInfo)

/*! @abstract 手动设置的导航栏按钮 ID
 @discussion 如果设置，被点击的时候会采集，可以唯一标志a该导航栏按钮
 */
@property (nonatomic, copy) NSString *bdAutoTrackID;

/*! @abstract 手动设置的导航栏按钮 content
 @discussion 如果设置，被点击的时候会采集
 */
@property (nonatomic, copy) NSString *bdAutoTrackContent;

/*! @abstract 手动设置的extra信息
 @discussion 如果设置，被点击的时候会采集
 */
@property (nonatomic, copy) NSDictionary<NSString*, NSString *> *bdAutoTrackExtraInfos;

@end

NS_ASSUME_NONNULL_END
