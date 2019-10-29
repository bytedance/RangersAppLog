//
//  UIViewController+AutoTrack.h
//  Applog
//
//  Created by bob on 2019/1/20.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface UIViewController (TrackInfo)

/*! @abstract 手动设置的PageTitle
 @discussion 如果设置，页面切换的时候会采集
 @discussion 如果设置，该VC里面的View被点击的时候会采集
 */
@property (nonatomic, copy) NSString *bdAutoTrackPageTitle;

/*! @abstract 手动设置的PageID
 @discussion 如果设置，页面切换的时候会采集
 @discussion 如果设置，该VC里面的View被点击的时候会采集
 */
@property (nonatomic, copy) NSString *bdAutoTrackPageID;

/*! @abstract 手动设置的extra信息
 @discussion 如果设置，页面切换的时候会采集
 @discussion 如果设置，该VC里面的View被点击的时候会采集
 */
@property (nonatomic, copy) NSDictionary<NSString*, NSString *> *bdAutoTrackExtraInfos;

@end

NS_ASSUME_NONNULL_END
