//
//  UIView+AutoTrack.h
//  Applog
//
//  Created by bob on 2019/1/15.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface UIView (TrackInfo)

/*! @abstract 手动设置的ViewID
 @discussion 如果设置，被点击的时候会采集，可以唯一标志该View
 */
@property (nonatomic, copy) NSString *bdAutoTrackViewID;

/*! @abstract 手动设置的ViewContent
 @discussion如果设置，被点击的时候会采集
 */
@property (nonatomic, copy) NSString *bdAutoTrackViewContent;

/*! @abstract 手动设置的extra信息
 @discussion 如果设置，被点击的时候会采集
 */
@property (nonatomic, copy) NSDictionary<NSString*, NSString *> *bdAutoTrackExtraInfos;

@end

NS_ASSUME_NONNULL_END
