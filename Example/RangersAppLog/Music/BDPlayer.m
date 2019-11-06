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

@interface BDPlayer ()

@property (nonatomic, strong) AVAudioPlayer *player;

@end

@implementation BDPlayer

- (instancetype)init {
    self = [super init];
    if (self) {
        AVAudioSession *session = [AVAudioSession sharedInstance];
        [session setActive:YES error:nil];
        [session setCategory:AVAudioSessionCategoryPlayback error:nil];

        [[UIApplication sharedApplication] beginReceivingRemoteControlEvents];

        NSString *musicPath = [[NSBundle mainBundle] pathForResource:@"test_song" ofType:@"mp3"];
        NSURL *url = [[NSURL alloc] initFileURLWithPath:musicPath];

        NSError *error;
        AVAudioPlayer *player = [[AVAudioPlayer alloc] initWithContentsOfURL:url error:&error];
        [player prepareToPlay];
        [player setVolume:1];
        player.numberOfLoops = -1;
        self.player = player;
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

    [[UIApplication sharedApplication] endReceivingRemoteControlEvents];
}


@end
