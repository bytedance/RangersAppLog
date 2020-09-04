//
//  BDIGListKitTesterImp.m
//  ObjCExample
//
//  Created by 朱元清 on 2020/8/21.
//  Copyright © 2020 bytedance. All rights reserved.
//

#import "BDIGListKitTesterImp.h"
#import <IGListKit.h>
#import "IGListTesterModel.h"
#import "BDChinesePaintingSectionController.h"

@interface BDIGListKitTesterImp () <IGListAdapterDataSource>

@property (strong, nonatomic) UICollectionView *collectionView;
@property (strong, nonatomic) IGListAdapter *adapter;

@end

@implementation BDIGListKitTesterImp

- (void)viewDidLoad {
    [super viewDidLoad];
    
    self.collectionView = [[UICollectionView alloc] initWithFrame:self.view.bounds
                                             collectionViewLayout:UICollectionViewFlowLayout.new];
    self.collectionView.backgroundColor = [UIColor colorWithRed:100.0/255 green:155.0/255 blue:100.0/255 alpha:1.0];
    
    self.adapter.collectionView = self.collectionView;
    self.adapter.dataSource = self;
    [self.view addSubview:self.collectionView];
}

#pragma mark - ListAdapterDataSource

- (nonnull NSArray<id<IGListDiffable>> *)objectsForListAdapter:(nonnull IGListAdapter *)listAdapter {
    return @[@"猫国画", @"荷花国画", @"梅花国画", @"迎客松国画",
             @"果树国画", @"竹子国画", @"山花烂漫国画"];
}

- (nonnull IGListSectionController *)listAdapter:(nonnull IGListAdapter *)listAdapter sectionControllerForObject:(nonnull id)object {
    BDChinesePaintingSectionController *sectionController = [BDChinesePaintingSectionController new];
    if ([object isKindOfClass:NSString.class]) {
        sectionController.picName = object;
    }
    return sectionController;
}

- (nullable UIView *)emptyViewForListAdapter:(nonnull IGListAdapter *)listAdapter {
    return nil;
}


#pragma mark - getter
- (IGListAdapter *)adapter {
    if (!_adapter) {
        IGListAdapterUpdater *updater = [[IGListAdapterUpdater alloc] init];
        _adapter = [[IGListAdapter alloc] initWithUpdater:updater
                                           viewController:self
                                         workingRangeSize:1];
    }
    return _adapter;
}

@end

