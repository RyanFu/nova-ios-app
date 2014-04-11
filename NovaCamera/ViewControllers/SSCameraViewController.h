//
//  SSCameraViewController.h
//  NovaCamera
//
//  Created by Mike Matz on 12/20/13.
//  Copyright (c) 2013 Sneaky Squid. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SSFlashSettingsViewController.h"

@class SSCameraPreviewView;
@class SSNovaFlashService;
@class SSSettingsService;
@class SSStatsService;

/**
 * Camera capture view; handles preview, camera capture, displaying of
 * various settings, and transitions to library view
 */
@interface SSCameraViewController : UIViewController <UIImagePickerControllerDelegate, UINavigationControllerDelegate, UIGestureRecognizerDelegate, SSFlashSettingsViewControllerDelegate>

@property (nonatomic, strong) IBOutlet SSCameraPreviewView *previewView;
@property (nonatomic, strong) IBOutlet UIButton *captureButton;
@property (nonatomic, strong) IBOutlet UIButton *libraryButton;
@property (nonatomic, strong) IBOutlet UIButton *flashSettingsButton;
@property (nonatomic, strong) IBOutlet UIButton *generalSettingsButton;
@property (nonatomic, strong) IBOutlet UIButton *toggleCameraButton;
@property (nonatomic, strong) IBOutlet UIImageView *flashIconImage;

@property (nonatomic, strong) IBOutlet SSFlashSettingsViewController *flashSettingsViewController;

@property (nonatomic, strong) SSNovaFlashService *flashService;
@property (nonatomic, strong) SSSettingsService *settingsService;
@property (nonatomic, strong) SSStatsService *statsService;

- (IBAction)capture:(id)sender;
- (IBAction)showGeneralSettings:(id)sender;
- (IBAction)showFlashSettings:(id)sender;
- (IBAction)showLibrary:(id)sender;
- (IBAction)toggleCamera:(id)sender;
- (void)handleTapFrom:(UITapGestureRecognizer *)recognizer;
- (void)handlePinchFrom:(UIPinchGestureRecognizer *)recognizer;
- (void)resetZoom;

@end
