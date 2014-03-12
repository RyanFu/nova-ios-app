//
//  SSPhotoViewController.h
//  NovaCamera
//
//  Created by Mike Matz on 1/9/14.
//  Copyright (c) 2014 Sneaky Squid. All rights reserved.
//

#import <UIKit/UIKit.h>

@class ALAsset;
@class SSChronologicalAssetsLibraryService;
@class SSStatsService;

/**
 * Photo viewer; UIImageView embedded in a UIScrollView allowing user to
 * pan and zoom around image.
 */
@interface SSPhotoViewController : UIViewController <UIScrollViewDelegate>

/**
 * Assets library service used to retrieve full resolution images
 */
@property (nonatomic, weak) SSChronologicalAssetsLibraryService *libraryService;

@property (nonatomic, strong) SSStatsService *statsService;

/**
 * Asset URL of photo
 */
@property (nonatomic, strong) NSURL *assetURL;

/**
 * Image view containing the target image
 */
@property (nonatomic, strong) IBOutlet UIImageView *imageView;

/**
 * Scroll view allowing for zooming and panning. This will actually
 * be assigned an SSCenteredScrollView instance in the storyboard to
 * ensure that the image remains centered on the screen when zoom
 * scale allows for margins.
 */
@property (nonatomic, strong) IBOutlet UIScrollView *scrollView;

/**
 * Image width contraint; modified when image is changed
 */
@property (nonatomic, strong) IBOutlet NSLayoutConstraint *imageWidthConstraint;

/**
 * Image height constraint; modified when image is changed
 */
@property (nonatomic, strong) IBOutlet NSLayoutConstraint *imageHeightConstraint;

/**
 * Reset zoom, fitting the current image if larger than the screen, but
 * not zooming beyind 1x.
 */
- (void)resetZoom;

@end
