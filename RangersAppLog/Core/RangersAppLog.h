//
//  RangersAppLog.h
//  RangersAppLog
//
//  Created by bob on 2020/4/1.
//

#ifndef RangersAppLog_h
#define RangersAppLog_h

#import <Foundation/Foundation.h>

#if __has_include(<RangersAppLog/BDCommonDefine.h>)

#import <UIKit/UIKit.h>
#import <AdSupport/AdSupport.h>
#import <Security/Security.h>
#import <CoreFoundation/CoreFoundation.h>
#import <CoreTelephony/CTCarrier.h>
#import <SystemConfiguration/SystemConfiguration.h>
#import <CoreGraphics/CoreGraphics.h>
#import <zlib.h>
#import <sqlite3.h>

#import <RangersAppLog/BDCommonDefine.h>
#import <RangersAppLog/BDAutoTrackConfig.h>
#import <RangersAppLog/BDAutoTrackConfig+AppLog.h>
#import <RangersAppLog/BDAutoTrack.h>
#import <RangersAppLog/BDAutoTrack+Game.h>
#import <RangersAppLog/BDAutoTrack+GameTrack.h>
#import <RangersAppLog/BDAutoTrack+Special.h>
#import <RangersAppLog/BDAutoTrack+OhayooGameTrack.h>
#import <RangersAppLog/BDAutoTrackSchemeHandler.h>
#import <RangersAppLog/BDAutoTrackNotifications.h>
#endif

#if __has_include(<RangersAppLog/UIBarButtonItem+TrackInfo.h>)

#import <WebKit/WebKit.h>

#import <RangersAppLog/UIBarButtonItem+TrackInfo.h>
#import <RangersAppLog/UIView+TrackInfo.h>
#import <RangersAppLog/UIViewController+TrackInfo.h>
#import <RangersAppLog/BDKeyWindowTracker.h>
#endif

#if __has_include(<RangersAppLog/RangersAppLogPicker.h>)
#import <CoreText/CoreText.h>
#endif

#endif /* RangersAppLog_h */

