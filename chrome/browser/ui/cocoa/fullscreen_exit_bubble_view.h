// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_COCOA_FULLSCREEN_EXIT_BUBBLE_VIEW_H_
#define CHROME_BROWSER_UI_COCOA_FULLSCREEN_EXIT_BUBBLE_VIEW_H_
#pragma once

#import <Cocoa/Cocoa.h>

#include "chrome/browser/ui/cocoa/background_gradient_view.h"

// A view that handles painting the background for the Fullscreen Exit Bubble.
@interface FullscreenExitBubbleView : BackgroundGradientView

// Specifies that mouse events over this view should be ignored by the
// render host.
- (BOOL)nonWebContentView;

@end

#endif  // CHROME_BROWSER_UI_COCOA_FULLSCREEN_EXIT_BUBBLE_VIEW_H_
