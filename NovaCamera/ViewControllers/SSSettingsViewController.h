//
//  SSSettingsViewController.h
//  NovaCamera
//
//  Created by Mike Matz on 1/29/14.
//  Copyright (c) 2014 Sneaky Squid. All rights reserved.
//

#import <UIKit/UIKit.h>

@class SSSettingsService;

/**
 * Simple UITableViewController subclass that displays settings as
 * defined in SSSettingsService
 */
@interface SSSettingsViewController : UITableViewController

@property (nonatomic, strong) SSSettingsService *settingsService;
@property (nonatomic, copy) NSArray *settingsItems;

@end
