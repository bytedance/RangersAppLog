//
//  BackgroundDownload.m
//  RangersAppLog
//
//  Created by bob on 2019/11/7.
//  Copyright © 2019 Bytedance. All rights reserved.
//

#import "BackgroundDownload.h"
#import <UIKit/UIKit.h>

@interface BackgroundDownload ()<NSURLSessionDownloadDelegate>

@property (nonatomic, strong) NSURLSession *session;
@property (nonatomic, strong) NSMutableDictionary<NSString *, dispatch_block_t> *handlers;


@end

@implementation BackgroundDownload

- (void)dealloc {
    [[NSNotificationCenter defaultCenter] removeObserver:self];
}

- (void)onDidEnterBackground {
    if (!self.backgroundDownloadEnabled) {
        return;
    }
    [self beginBackgroundDownload];
}

- (instancetype)init {
    self = [super init];
    if (self) {
        NSURLSessionConfiguration *configuration = [NSURLSessionConfiguration backgroundSessionConfigurationWithIdentifier:@"com.applog.background"];
        self.session = [NSURLSession sessionWithConfiguration:configuration delegate:self delegateQueue:nil];
        self.handlers = [NSMutableDictionary new];
        [[NSNotificationCenter defaultCenter] addObserver:self
                                                 selector:@selector(onDidEnterBackground)
                                                     name:UIApplicationDidEnterBackgroundNotification
                                                   object:nil];
    }

    return self;
}

+ (instancetype)sharedInstance {
    static BackgroundDownload *sharedInstance = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        sharedInstance = [self new];
    });

    return sharedInstance;
}

- (void)beginBackgroundDownload {
    NSString *downloadURLString = @"https://github.com/bytedance/RangersAppLog/blob/feature-demo/Example/RangersAppLog/Music/test_song.mp3";
    NSURL* downloadURL = [NSURL URLWithString:downloadURLString];
    NSURLRequest *request = [NSURLRequest requestWithURL:downloadURL];
    NSURLSessionDownloadTask *task = [self.session downloadTaskWithRequest:request];
    task.taskDescription = @"com.applog.background";
    [task resume];
}

- (void)addBackgroundHandler:(dispatch_block_t)completionHandler forSession:(NSString *)identifier {
    if (identifier.length > 0 && completionHandler) {
        if ([self.handlers objectForKey:identifier]) {
            NSLog(@"error");
        }
        [self.handlers setValue:completionHandler forKey:identifier];
    }
}

#pragma mark - NSURLSessionDelegate

- (void)URLSessionDidFinishEventsForBackgroundURLSession:(NSURLSession *)session {
    NSString *identifier = session.configuration.identifier;
    if (identifier.length > 0) {
        dispatch_block_t handler = [self.handlers objectForKey:identifier];
        if (handler) {
            [self.handlers removeObjectForKey:identifier];
            handler();
        }
    }
}

#pragma mark - NSURLSessionDownloadDelegate

- (void)URLSession:(NSURLSession *)session
      downloadTask:(NSURLSessionDownloadTask *)downloadTask didFinishDownloadingToURL:(NSURL *)location {

}


- (void)URLSession:(NSURLSession *)session downloadTask:(NSURLSessionDownloadTask *)downloadTask
                                           didWriteData:(int64_t)bytesWritten
                                      totalBytesWritten:(int64_t)totalBytesWritten totalBytesExpectedToWrite:(int64_t)totalBytesExpectedToWrite {

}

- (void)URLSession:(NSURLSession *)session downloadTask:(NSURLSessionDownloadTask *)downloadTask
                                      didResumeAtOffset:(int64_t)fileOffset expectedTotalBytes:(int64_t)expectedTotalBytes {

}


@end
