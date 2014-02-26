//
//  SSNovaFlashService.h
//  NovaCamera
//
//  Created by Mike Matz on 1/28/14.
//  Copyright (c) 2014 Sneaky Squid. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 * Different modes of flash, including the three built-in modes, off and custom.
 */
typedef enum {
    SSFlashModeOff = 0,
    SSFlashModeGentle,
    SSFlashModeWarm,
    SSFlashModeBright,
    SSFlashModeCustom,
    SSFlashModeUnknown = -1,
} SSFlashMode;

/**
 * Struct combining all flash settings: mode, color temp and brightness.
 */
typedef struct {
    SSFlashMode flashMode;
    double flashColorTemperature;
    double flashBrightness;
} SSFlashSettings;

/**
 * Predefined flash settings
 */
static const SSFlashSettings SSFlashSettingsGentle = { SSFlashModeGentle, 0.5, 0.25 };
static const SSFlashSettings SSFlashSettingsWarm = { SSFlashModeWarm, 1.0, 0.75 };
static const SSFlashSettings SSFlashSettingsBright = { SSFlashModeBright, 0.5, 1.0 };
static const SSFlashSettings SSFlashSettingsCustomDefault = { SSFlashModeCustom, 0.5, 0.5 };

/**
 * Flash status
 */
typedef enum {
    SSNovaFlashStatusDisabled = 0,
    SSNovaFlashStatusSearching,
    SSNovaFlashStatusOK,
    SSNovaFlashStatusError,
    SSNovaFlashStatusUnknown = -1,
} SSNovaFlashStatus;

/**
 * Notifications
 */
static const NSString *SSNovaFlashServiceStatusChanged;

@class NVFlashService;

/**
 * Abstraction for Nova Flash, handling persistence of flash settings as well as
 * Nova Flash SDK interaction.
 */

@interface SSNovaFlashService : NSObject

/**
 * NVFlashService from the Nova SDK
 */
@property (nonatomic, strong) NVFlashService *nvFlashService;

/**
 * SSFlashSettings struct containing the current flash settings.
 * Setting this property will result in this service asynchronously
 * saving new settings to NSUseDefaults.
 */
@property (nonatomic, assign) SSFlashSettings flashSettings;

/**
 * SSNovaFlashStatus describing the status of the flash unit (or units).
 */
@property (nonatomic, readonly) SSNovaFlashStatus status;

/**
 * Flag determining whether multiple Nova units should be used.
 * If NO, use only the nearest Nova unit.
 */
@property (nonatomic, assign) BOOL useMultipleNovas;

/**
 * Singleton accessor
 */
+ (id)sharedService;

/**
 * Apply current configuration to flash device
 */
- (void)configureFlash;

/**
 * Enabe flash (if it was disabled)
 */
- (void)enableFlash;

/**
 * Disable flash.
 */
- (void)disableFlash;

/**
 * Forget any paired devices and re-scan.
 */
- (void)refreshFlash;

/**
 * Perform actual flash
 */
- (void)beginFlashWithCallback:(void (^)(BOOL status))callback;

/**
 * End flash; send when image is captured
 */
- (void)endFlashWithCallback:(void (^)(BOOL status))callback;

@end
