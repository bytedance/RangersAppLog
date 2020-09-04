//
//  BDChinesePaintingSectionController.m
//  ObjCExample
//
//  Created by 朱元清 on 2020/8/24.
//  Copyright © 2020 bytedance. All rights reserved.
//

#import "BDChinesePaintingSectionController.h"

@interface BDChinesePaintingSectionController ()

@end


@implementation BDChinesePaintingSectionController


- (NSInteger)numberOfItems {
    return 1;
}

- (CGSize)sizeForItemAtIndex:(NSInteger)index {
    CGFloat width = [[self collectionContext] containerSize].width ?: 0;
    return CGSizeMake(width, width);
}

- (__kindof UICollectionViewCell *)cellForItemAtIndex:(NSInteger)index {
    id<IGListCollectionContext> ctx = [self collectionContext];
    
    UICollectionViewCell * cell = [ctx dequeueReusableCellOfClass:[UICollectionViewCell class] forSectionController:self atIndex:index];
    
    UIImage *img = [UIImage imageNamed:self.picName];
    UIImageView *imgView = [[UIImageView alloc] initWithImage:img];
    imgView.frame = cell.contentView.bounds;
    [cell.contentView addSubview:imgView];
    
    return cell;
}

@end
