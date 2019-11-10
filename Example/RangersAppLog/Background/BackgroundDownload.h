//
//  BackgroundDownload.h
//  RangersAppLog
//
//  Created by bob on 2019/11/7.
//  Copyright © 2019 Bytedance. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface BackgroundDownload : NSObject

@property (nonatomic, assign) BOOL backgroundDownloadEnabled;

+ (instancetype)sharedInstance;

- (void)addBackgroundHandler:(dispatch_block_t)completionHandler forSession:(NSString *)identifier;

@end

NS_ASSUME_NONNULL_END
