//
//  SSSettingsService.m
//  NovaCamera
//
//  Created by Mike Matz on 1/29/14.
//  Copyright (c) 2014 Sneaky Squid. All rights reserved.
//

#import "SSSettingsService.h"

const NSString *kSettingsServicePreviewAfterCaptureKey = @"SettingsServicePreviewAfterCaptureKey";
const NSString *kSettingsServiceEditAfterCaptureKey = @"SettingsServiceEditAfterCaptureKey";
const NSString *kSettingsServiceShareAfterCaptureKey = @"SettingsServiceShareAfterCaptureKey";
const NSString *kSettingsServiceShowGridLinesKey = @"SettingsServiceShowGridLinesKey";
const NSString *kSettingsServiceSquarePhotosKey = @"SettingsServiceSquarePhotosKey";
const NSString *kSettingsServiceOptOutStatsKey = @"SettingsServiceOptOutStats";
const NSString *kSettingsServiceEnableVolumeButtonTriggerKey = @"SettingsServiceEnableVolumeButtonTrigger";
const NSString *kSettingsServiceLightBoostKey = @"SettingsServiceLightBoostKey";
const NSString *kSettingsServiceResetFocusOnSceneChangeKey = @"SettingsServiceResetFocusOnSceneChangeKey";
const NSString *kSettingsServiceMultipleNovasKey = @"SettingsServiceMultipleNovasKey";


// Private settings that are never shown to user
const NSString *kSettingsServiceOneTimeAskedOptOutQuestion = @"SettingsServiceOneTimeAskedOptOutQuestion";

@implementation SSSettingsService

- (id)init {
    self = [super init];
    if (self) {
    }
    return self;
}

+ (id)sharedService {
    static id _sharedService;
    static dispatch_once_t once;
    
    dispatch_once(&once, ^{
        _sharedService = [[self alloc] init];
    });
    
    return _sharedService;
}

- (void)initializeUserDefaults {
    NSArray *defaults = @[
                          @NO,      // kSettingsServicePreviewAfterCaptureKey
                          @NO,      // kSettingsServiceEditAfterCaptureKey
                          @NO,      // kSettingsServiceShareAfterCaptureKey
                          @YES,     // kSettingsServiceOptOutStatsKey
                          @YES,     // kSettingsServiceEnableVolumeButtonTriggerKey
                          @YES,     // kSettingsServiceLightBoostKey
                          @YES,     // kSettingsServiceResetFocusOnSceneChangeKey
                          @NO,      // kSettingsServiceMultipleNovasKey
                          ];
    NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];
    NSArray *keys = [self generalSettingsKeys];
    for (int idx = 0; idx < defaults.count; idx++) {
        NSString *key = keys[idx];
        if ([userDefaults objectForKey:key] == nil) {
            BOOL val = [defaults[idx] boolValue];
            DDLogVerbose(@"Setting NSUserDefaults key %@ to %d", key, val);
            [userDefaults setBool:val forKey:key];
        }
    }
    [userDefaults synchronize];
}

- (NSArray *)generalSettingsKeys {
    return @[
             kSettingsServicePreviewAfterCaptureKey,
             kSettingsServiceEditAfterCaptureKey,
             kSettingsServiceShareAfterCaptureKey,
             kSettingsServiceOptOutStatsKey,
             kSettingsServiceEnableVolumeButtonTriggerKey,
             kSettingsServiceLightBoostKey,
             kSettingsServiceResetFocusOnSceneChangeKey,
             kSettingsServiceMultipleNovasKey,
             ];
}

- (NSArray *)generalSettingsLocalizedTitles {
    return @[
             @"After photo: Preview",
             @"After photo: Edit",
             @"After photo: Share",
             @"Opt-out of usage stats",
             @"Volume keys trigger shutter",
             @"Night vision in low light",
             @"Scene change resets focus",
             @"Multiple Novas",
             ];
}

- (NSString *)localizedTitleForKey:(NSString *)key {
    NSUInteger idx = [[self generalSettingsKeys] indexOfObject:key];
    NSString *title = nil;
    if (NSNotFound != idx) {
        title = [[self generalSettingsLocalizedTitles] objectAtIndex:idx];
    }
    return title;
}

- (BOOL)isKeySet:(NSString *)key {
    return [[NSUserDefaults standardUserDefaults] objectForKey:key] != nil;
}

- (void)clearKey:(NSString *)key {
    [[NSUserDefaults standardUserDefaults] removeObjectForKey:key];
}

- (BOOL)boolForKey:(NSString *)key {
    return [[NSUserDefaults standardUserDefaults] boolForKey:key];
}

- (void)setBool:(BOOL)value forKey:(NSString *)key {
    [self willChangeValueForKey:key];
    [[NSUserDefaults standardUserDefaults] setBool:value forKey:key];
    [self didChangeValueForKey:key];
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_BACKGROUND, 0), ^{
        [[NSUserDefaults standardUserDefaults] synchronize];
        [self didChangeValueForKey:key];
    });
}

@end
