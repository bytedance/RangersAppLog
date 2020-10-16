//
//  BDProfileAPITester_UI.m
//  ObjCExample
//
//  Created by 朱元清 on 2020/10/10.
//  Copyright © 2020 bytedance. All rights reserved.
//

#import "BDProfileAPITester_UI.h"
#import <RangersAppLog/RangersAppLog.h>

typedef enum : NSUInteger {
    ProfileRequestTypeSet,
    ProfileRequestTypeSetOnce,
    ProfileRequestTypeAppend,
    ProfileRequestTypeIncrement,
    ProfileRequestTypeUnset,
    ProfileRequestTypeUnknown
} ProfileRequestType;

@interface BDProfileAPITester_UI ()
// 数据组1
@property (weak, nonatomic) IBOutlet UITextField *g1_data1_key;
@property (weak, nonatomic) IBOutlet UITextField *g1_data1_val;
@property (weak, nonatomic) IBOutlet UISwitch *g1_data1_switch;

@property (weak, nonatomic) IBOutlet UITextField *g1_data2_key;
@property (weak, nonatomic) IBOutlet UITextField *g1_data2_val;
@property (weak, nonatomic) IBOutlet UISwitch *g1_data2_switch;

@property (weak, nonatomic) IBOutlet UITextField *g1_data3_key;
@property (weak, nonatomic) IBOutlet UITextField *g1_data3_val;
@property (weak, nonatomic) IBOutlet UISwitch *g1_data3_switch;

@property (weak, nonatomic) IBOutlet UISegmentedControl *g1_segmentedControl;
@property (weak, nonatomic) IBOutlet UIButton *g1_sendButton;

// 数据组2
@property (weak, nonatomic) IBOutlet UITextField *g2_data1_key;
@property (weak, nonatomic) IBOutlet UITextField *g2_data1_val;
@property (weak, nonatomic) IBOutlet UISwitch *g2_data1_switch;

@property (weak, nonatomic) IBOutlet UITextField *g2_data2_key;
@property (weak, nonatomic) IBOutlet UITextField *g2_data2_val;
@property (weak, nonatomic) IBOutlet UISwitch *g2_data2_switch;

@property (weak, nonatomic) IBOutlet UITextField *g2_data3_key;
@property (weak, nonatomic) IBOutlet UITextField *g2_data3_val;
@property (weak, nonatomic) IBOutlet UISwitch *g2_data3_switch;

@property (weak, nonatomic) IBOutlet UISegmentedControl *g2_segmentedControl;
@property (weak, nonatomic) IBOutlet UIButton *g2_sendButton;

@end

@implementation BDProfileAPITester_UI

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
    
}

- (IBAction)handleSendButtonTouched:(UIButton *)sender forEvent:(UIEvent *)event {
    NSMutableDictionary<NSString *, id> *sendingData = [NSMutableDictionary new];
    ProfileRequestType profileType = ProfileRequestTypeUnknown;
    
    /* 获取控件数据 */
    NSString *key1, *key2, *key3, *reqTypeStr;
    NSObject *val1, *val2, *val3;
    if (sender == self.g1_sendButton) {
        if (self.g1_data1_switch.on) {
            key1 = self.g1_data1_key.text;
            val1 = [self objectForString:self.g1_data1_val.text];
        }
        if (self.g1_data2_switch.on) {
            key2 = self.g1_data2_key.text;
            val2 = [self objectForString:self.g1_data2_val.text];
        }
        if (self.g1_data3_switch.on) {
            key3 = self.g1_data3_key.text;
            val3 = [self objectForString:self.g1_data3_val.text];
        }
        reqTypeStr = [self.g1_segmentedControl titleForSegmentAtIndex:self.g1_segmentedControl.selectedSegmentIndex];
    }
    else if (sender == self.g2_sendButton) {
        if (self.g2_data1_switch.on) {
            key1 = self.g2_data1_key.text;
            val1 = [self objectForString:self.g2_data1_val.text];
        }
        if (self.g2_data2_switch.on) {
            key2 = self.g2_data2_key.text;
            val2 = [self objectForString:self.g2_data2_val.text];
        }
        if (self.g2_data3_switch.on) {
            key3 = self.g2_data3_key.text;
            val3 = [self objectForString:self.g2_data3_val.text];
        }
        reqTypeStr = [self.g2_segmentedControl titleForSegmentAtIndex:self.g2_segmentedControl.selectedSegmentIndex];
    } else {
        return;
    }
    
    /* 拼接sendingData */
    if (key1.length && val1) {
        [sendingData setObject:val1 forKey:key1];
    }
    if (key2.length && val2) {
        [sendingData setObject:val2 forKey:key2];
    }
    if (key3.length && val3) {
        [sendingData setObject:val3 forKey:key3];
    }
    
    /* 确定profileType。对increment类型做atoi */
    if ([reqTypeStr isEqualToString:@"set"]) {
        [self numberize:sendingData];
        profileType = ProfileRequestTypeSet;
    } else if ([reqTypeStr isEqualToString:@"setOnce"]) {
        [self numberize:sendingData];
        profileType = ProfileRequestTypeSetOnce;
    } else if ([reqTypeStr isEqualToString:@"append"]) {
        profileType = ProfileRequestTypeAppend;
    } else if ([reqTypeStr isEqualToString:@"incre"]) {
        [self numberize:sendingData];
        profileType = ProfileRequestTypeIncrement;
    } else if ([reqTypeStr isEqualToString:@"unset"]) {
        profileType = ProfileRequestTypeUnset;
    }
    
    if (sendingData.count > 0) {
        [self performSend:sendingData profileRequestType:profileType];
    }
}

- (void)performSend:(NSDictionary *)sendingData profileRequestType:(ProfileRequestType)action {
    switch (action) {
        case ProfileRequestTypeSet:
            [BDAutoTrack profileSet:sendingData];
            break;
        case ProfileRequestTypeSetOnce:
            [BDAutoTrack profileSetOnce:sendingData];
            break;
        case ProfileRequestTypeAppend:
            [BDAutoTrack profileAppend:sendingData];
            break;
        case ProfileRequestTypeIncrement:
            [BDAutoTrack profileIncrement:sendingData];
            break;
        case ProfileRequestTypeUnset:
            for (NSString *key in sendingData) {
                [BDAutoTrack profileUnset:key];
            }
            break;
        default:
            NSLog(@"%s:%i error: unknow profile request type", __FILE__, __LINE__);
            break;
    }
}

- (NSObject *)objectForString:(NSString *)val {
    if (val && [self isJSONString:val]) {
        // 替换中文左引号
        val = [val stringByReplacingOccurrencesOfString:@"“" withString:@"\""];
        // 替换中文右引号
        val = [val stringByReplacingOccurrencesOfString:@"”" withString:@"\""];
        // 替换中文冒号
        val = [val stringByReplacingOccurrencesOfString:@"：" withString:@":"];
        // 替换中文逗号
        val = [val stringByReplacingOccurrencesOfString:@"，" withString:@","];
        
        NSError *err;
        NSObject *obj = [NSJSONSerialization
                JSONObjectWithData:[val dataUsingEncoding:NSUTF8StringEncoding]
                           options:0
                             error:&err];
        return obj;
    }
    
    return val;
}

- (BOOL)isJSONString:(NSString *)JSON {
    return ([JSON hasPrefix:@"["] && [JSON hasSuffix:@"]"]);// ||
         //([JSON hasPrefix:@"{"] && [JSON hasSuffix:@"}"]);
}

- (void)numberize:(NSMutableDictionary<NSString *, id> *)sendingData {
    NSRegularExpression *regex = [NSRegularExpression regularExpressionWithPattern:@"^-?(?:|0|[1-9]\\d*)(?:\\.\\d*)?$" options:0 error:nil];
    
    for (NSString *key in sendingData.allKeys) {
        NSString *val = sendingData[key];
        if ([val isKindOfClass:NSString.class]) {
            if ([regex firstMatchInString:val options:0 range: NSMakeRange(0, val.length)]) {
                NSNumberFormatter *f = [[NSNumberFormatter alloc] init];
                f.numberStyle = NSNumberFormatterDecimalStyle;
                NSNumber *newVal = [f numberFromString:val];
                if (newVal) {
                    [sendingData setObject:newVal forKey:key];
                }
            }
        }
    }
}
@end
