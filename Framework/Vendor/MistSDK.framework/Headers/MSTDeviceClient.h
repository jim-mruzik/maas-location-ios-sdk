//
//  MSTClient.h
//  Mist
//
//  Created by Cisco on 3/2/16.
//  Copyright © 2016 Cisco. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface MSTDeviceClient : NSObject

@property (nonatomic, strong) NSString *orgName;
@property (nonatomic, strong) NSString *orgID;
@property (nonatomic, strong) NSString *name;

@end
