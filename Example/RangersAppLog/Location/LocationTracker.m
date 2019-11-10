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
#import "BDAdapter.h"
#import "BackgroundTask.h"

@interface LocationTracker ()<CLLocationManagerDelegate>

@property (nonatomic, strong) CLLocationManager *locationManager;
@property (nonatomic, strong) BackgroundTask *task;
@property (nonatomic, assign) CLLocationCoordinate2D center;


@end

@implementation LocationTracker

- (void)dealloc {
    [[NSNotificationCenter defaultCenter] removeObserver:self];
}

- (void)onDidEnterBackground {
    if (!self.enabled) {
        return;
    }
    self.enabled = NO;
    [self startBackgroundLocation];
}

- (void)onWillEnterForeground {
    [self stopLocation];
    [self stopMonitor];
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
        locationManager.distanceFilter = 100;

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
        self.enabled = NO;
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
}

- (void)startLocation {
    [self requestAuthorization];
    [self.locationManager startUpdatingLocation];
    /// 500 米一次
    [self.locationManager startMonitoringSignificantLocationChanges];
}

- (CLCircularRegion *)monitorRegion {

    CLLocationDistance distance = 20;
    CLCircularRegion *region = [[CLCircularRegion alloc] initWithCenter:self.center
                                                                 radius:distance
                                                             identifier:@"com.applog.location"];
    region.notifyOnExit = YES;
    region.notifyOnEntry = YES;

    return region;
}

- (void)startMonitor {
    if (![CLLocationManager isMonitoringAvailableForClass:CLCircularRegion.class]) {
        return;
    }
    CLLocationManager *locationManager = self.locationManager;
    [locationManager startMonitoringForRegion:[self monitorRegion]];
}

- (void)stopMonitor {
    if (![CLLocationManager isMonitoringAvailableForClass:CLCircularRegion.class]) {
        return;
    }

    CLLocationManager *locationManager = self.locationManager;
    [locationManager stopMonitoringForRegion:[self monitorRegion]];
}

- (void)requestAuthorization {
    [self.locationManager requestAlwaysAuthorization];
}

- (void)stopLocation {
    [self.locationManager stopUpdatingLocation];
}

#pragma mark - CLLocationManagerDelegate

- (void)locationManager:(CLLocationManager *)manager didEnterRegion:(CLRegion *)region {
    [manager stopMonitoringForRegion:region];
    [BDAdapter trackCallback:NSStringFromSelector(_cmd) state:[UIApplication sharedApplication].applicationState];
}
- (void)locationManager:(CLLocationManager *)manager
          didExitRegion:(CLRegion *)region {
    [manager stopMonitoringForRegion:region];
    [BDAdapter trackCallback:NSStringFromSelector(_cmd) state:[UIApplication sharedApplication].applicationState];
}

- (void)locationManager:(CLLocationManager *)manager
     didUpdateLocations:(NSArray<CLLocation *> *)locations {
    CLLocation *location  = [locations lastObject];
    self.center = location.coordinate;
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
