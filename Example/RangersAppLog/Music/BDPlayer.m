//
//  BDPlayer.m
//  RangersAppLog
//
//  Created by bob on 2019/11/6.
//  Copyright © 2019 Bytedance. All rights reserved.
//

#import "BDPlayer.h"
#import <AVFoundation/AVFoundation.h>
#import <UIKit/UIKit.h>
#import <MediaPlayer/MediaPlayer.h>

#define BDWeakSelf __weak typeof(self) wself = self
#define BDStrongSelf __strong typeof(wself) self = wself


@interface BDPlayer ()

@property (nonatomic, strong) AVAudioPlayer *player;

@property (nonatomic, assign) BOOL infoShown;
@property (nonatomic, assign) BOOL handlerRegistered;

@end

@implementation BDPlayer

- (void)dealloc {
    [[NSNotificationCenter defaultCenter] removeObserver:self];
}

- (void)onSessionInterruption:(NSNotification *)not {
    NSLog(@"%@",not.userInfo);
    [self pause];
}

- (void)onWillTerminate {
    [[UIApplication sharedApplication] endReceivingRemoteControlEvents];
}

- (instancetype)init {
    self = [super init];
    if (self) {
        [[UIApplication sharedApplication] beginReceivingRemoteControlEvents];
        AVAudioSession *session = [AVAudioSession sharedInstance];
        [session setActive:YES error:nil];
        [session setCategory:AVAudioSessionCategoryPlayback error:nil];

        NSString *musicPath = [[NSBundle mainBundle] pathForResource:@"test_song" ofType:@"mp3"];
        NSURL *url = [[NSURL alloc] initFileURLWithPath:musicPath];

        NSError *error;
        AVAudioPlayer *player = [[AVAudioPlayer alloc] initWithContentsOfURL:url error:&error];
        [player prepareToPlay];
        player.numberOfLoops = -1;
        self.player = player;

        [[NSNotificationCenter defaultCenter] addObserver:self
                                                 selector:@selector(onWillTerminate)
                                                     name:UIApplicationWillTerminateNotification
                                                   object:nil];

        [[NSNotificationCenter defaultCenter] addObserver:self
                                                 selector:@selector(onSessionInterruption:)
                                                     name:AVAudioSessionInterruptionNotification
                                                   object:nil];
    }
    
    return self;
}

+ (instancetype)sharedInstance {
    static BDPlayer *sharedInstance = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        sharedInstance = [self new];
    });

    return sharedInstance;
}

- (void)play {
    if (self.player.isPlaying) {
        return;
    }
    [self.player play];
    [self showPlayingInfo];
    [self registerRemoteControlEventHandler];
}

- (void)pause {
    if (self.player.isPlaying) {
        [self.player pause];
    }
}

- (void)stop {
    if (self.player.isPlaying) {
        [self.player stop];
    }
}

- (void)playAndPause {
    if (self.player.isPlaying) {
        [self.player pause];
    } else {
         [self.player play];
    }
}

-(void)showPlayingInfo {
    if (self.infoShown) {
        return;
    }
    self.infoShown = YES;
    NSMutableDictionary *songDict=[NSMutableDictionary dictionary];
    [songDict setObject:@"Test" forKey:MPMediaItemPropertyTitle];
    [songDict setObject:@"Test" forKey:MPMediaItemPropertyArtist];
    [songDict setObject:@(240) forKeyedSubscript:MPMediaItemPropertyPlaybackDuration];
    MPMediaItemArtwork *imageItem= [[MPMediaItemArtwork alloc]initWithImage:[UIImage imageNamed:@"test_song.jpg"]];
    [songDict setObject:imageItem forKey:MPMediaItemPropertyArtwork];
    [[MPNowPlayingInfoCenter defaultCenter] setNowPlayingInfo:songDict];
}

- (void)registerRemoteControlEventHandler {
    if (self.handlerRegistered) {
        return;
    }
    self.handlerRegistered = YES;

    MPRemoteCommandCenter *commandCenter = [MPRemoteCommandCenter sharedCommandCenter];
    commandCenter.playCommand.enabled = YES;
    BDWeakSelf;
    [commandCenter.playCommand addTargetWithHandler:^MPRemoteCommandHandlerStatus(MPRemoteCommandEvent * _Nonnull event) {
        BDStrongSelf;
        [self play];
        return MPRemoteCommandHandlerStatusSuccess;
    }];
    commandCenter.pauseCommand.enabled = YES;
    [commandCenter.pauseCommand addTargetWithHandler:^MPRemoteCommandHandlerStatus(MPRemoteCommandEvent * _Nonnull event) {
        BDStrongSelf;
        [self pause];
        return MPRemoteCommandHandlerStatusSuccess;
    }];
    commandCenter.previousTrackCommand.enabled = YES;
    [commandCenter.previousTrackCommand addTargetWithHandler:^MPRemoteCommandHandlerStatus(MPRemoteCommandEvent * _Nonnull event) {
        BDStrongSelf;
        [self play];
        return MPRemoteCommandHandlerStatusSuccess;
    }];
    commandCenter.nextTrackCommand.enabled = YES;
    [commandCenter.nextTrackCommand addTargetWithHandler:^MPRemoteCommandHandlerStatus(MPRemoteCommandEvent * _Nonnull event) {
        BDStrongSelf;
        [self play];
        return MPRemoteCommandHandlerStatusSuccess;
    }];

    commandCenter.togglePlayPauseCommand.enabled = YES;
    [commandCenter.togglePlayPauseCommand addTargetWithHandler:^MPRemoteCommandHandlerStatus(MPRemoteCommandEvent * _Nonnull event) {
        BDStrongSelf;
        [self playAndPause];
        return MPRemoteCommandHandlerStatusSuccess;
    }];
}

@end
