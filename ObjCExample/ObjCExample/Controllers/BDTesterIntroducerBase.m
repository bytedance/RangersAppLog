//
//  BDTesterIntroducerBase.m
//  ObjCExample
//
//  Created by 朱元清 on 2020/8/22.
//  Copyright © 2020 bytedance. All rights reserved.
//

#import "BDTesterIntroducerBase.h"
#import "BDFeedModel.h"
#import "BDModelSectionHeader.h"

@interface BDTesterIntroducerBase () <UITableViewDelegate, UITableViewDataSource>

@end


@implementation BDTesterIntroducerBase
- (void)viewDidLoad {
    [super viewDidLoad];
    self.tableView = [[UITableView alloc] init];
    self.tableView.frame = self.view.bounds;
    self.tableView.delegate = self;
    self.tableView.dataSource = self;
    [self registerTableViewCell];
    [self.view addSubview:self.tableView];
    
    self.view.backgroundColor = UIColor.whiteColor;
//    self.title = ;
}

- (void)registerTableViewCell {
    [self.tableView registerClass:[UITableViewCell class] forCellReuseIdentifier:[self cellReuseID1]];
}

#pragma mark - table view delegate
- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return [self.modelObject numSections];
}
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return [self.modelObject numOfItemsInSection:section];
}
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:[self cellReuseID1]];
    BDFeedModel *model = [[self.modelObject itemsForSection:indexPath.section] objectAtIndex:indexPath.row];
    cell.textLabel.text = model.title;
    if (model.actionBlock) {
        cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
    }
    return cell;
}
- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    [tableView deselectRowAtIndexPath:indexPath animated:YES];
    // handle VC push
    BDFeedModel *model = [[self.modelObject itemsForSection:indexPath.section] objectAtIndex:indexPath.row];
    if (model.actionBlock) {
        model.actionBlock();
    }
}
- (NSString *)tableView:(UITableView *)tableView titleForHeaderInSection:(NSInteger)section {
    BDModelSectionHeader *sectionDevider = [self.modelObject sectionDeviderForSection:section];
    return sectionDevider.sectionName;
}

#pragma mark - getter

- (BDFeedModelDictionary *)modelObject {
    if (!_modelObject) {
        _modelObject  = [[BDFeedModelDictionary alloc] initWithModelArray:self.feedModels];
    }
    return _modelObject;
}

//- (NSMutableArray *)feedModels {
//    if (!_feedModels) {
////        __weak typeof(self) wself = self;
//        NSArray *tmpModels = @[];
//        
//        _feedModels = [NSMutableArray arrayWithArray:tmpModels];
//    }
//    return _feedModels;
//}


#pragma mark - cell reuse ID
- (NSString *)cellReuseID1 {
    return @"base_cellReuseID1";
}

@end
