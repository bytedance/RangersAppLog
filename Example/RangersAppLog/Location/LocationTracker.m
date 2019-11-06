//
//  LocationTracker.m
//  RangersAppLog
//
//  Created by bob on 2019/11/6.
//  Copyright © 2019 Bytedance. All rights reserved.
//

#import "LocationTracker.h"
#import <CoreLocation/CoreLocation.h>
#import <UIKit/UIKit.h>

#import "BackgroundTask.h"

@interface LocationTracker ()<CLLocationManagerDelegate>

@property (nonatomic, strong) CLLocationManager *locationManager;
@property (nonatomic, strong) BackgroundTask *task;

@end

@implementation LocationTracker

- (void)dealloc {
    [[NSNotificationCenter defaultCenter] removeObserver:self];
}

- (void)onDidEnterBackground {
    [self startBackgroundLocation];
}

- (void)onWillEnterForeground {
    [self stopLocation];
}

- (instancetype)init {
    self = [super init];
    if (self) {
        CLLocationManager *locationManager = [CLLocationManager new];
        locationManager.desiredAccuracy = kCLLocationAccuracyBestForNavigation;
        locationManager.allowsBackgroundLocationUpdates = YES;
        locationManager.pausesLocationUpdatesAutomatically = NO;
        locationManager.delegate = self;
        locationManager.desiredAccuracy = kCLLocationAccuracyBestForNavigation;
        locationManager.distanceFilter = kCLDistanceFilterNone;

        self.locationManager = locationManager;
        self.task = [BackgroundTask new];
        [[NSNotificationCenter defaultCenter] addObserver:self
                                                 selector:@selector(onDidEnterBackground)
                                                     name:UIApplicationDidEnterBackgroundNotification
                                                   object:nil];
        [[NSNotificationCenter defaultCenter] addObserver:self
                                                 selector:@selector(onWillEnterForeground)
                                                     name:UIApplicationWillEnterForegroundNotification
                                                   object:nil];
    }

    return self;
}

+ (instancetype)sharedInstance {
    static LocationTracker *sharedInstance = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        sharedInstance = [self new];
    });

    return sharedInstance;
}

- (void)startBackgroundLocation {
    [self startLocation];
    [self.task beginBackgroundTask];
}

- (void)startLocation {
    [self requestAuthorization];
    [self.locationManager startUpdatingLocation];
}

- (void)requestAuthorization {
    [self.locationManager requestAlwaysAuthorization];
}

- (void)stopLocation {
    [self.locationManager stopUpdatingLocation];
}

#pragma mark - CLLocationManagerDelegate

- (void)locationManager:(CLLocationManager *)manager
     didUpdateLocations:(NSArray<CLLocation *> *)locations {
    CLLocation *location  = [locations lastObject];
    NSLog(@"%@ %@",NSStringFromSelector(_cmd), location.description);
}

- (void)locationManager:(CLLocationManager *)manager didFailWithError:(NSError *)error {
    NSLog(@"%@ %@",NSStringFromSelector(_cmd), error.description);
}

- (void)locationManager:(CLLocationManager *)manager didChangeAuthorizationStatus:(CLAuthorizationStatus)status {
    NSLog(@"%@ %d",NSStringFromSelector(_cmd), status);
}

#pragma mark - Tool

+ (BOOL)checkLocationAbility {
    if ([CLLocationManager locationServicesEnabled] == NO)  {
        return NO;
    }

    CLAuthorizationStatus authorizationStatus= [CLLocationManager authorizationStatus];
    if( authorizationStatus == kCLAuthorizationStatusDenied
       || authorizationStatus == kCLAuthorizationStatusRestricted){
        return NO;
    }

    return YES;
}

@end
