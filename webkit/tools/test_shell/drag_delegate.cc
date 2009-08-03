// Copyright (c) 2009 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "webkit/tools/test_shell/drag_delegate.h"

#include "webkit/api/public/WebPoint.h"
#include "webkit/glue/webview.h"

using WebKit::WebPoint;

namespace {

void GetCursorPositions(HWND hwnd, gfx::Point* client, gfx::Point* screen) {
  // GetCursorPos will fail if the input desktop isn't the current desktop.
  // See http://b/1173534. (0,0) is wrong, but better than uninitialized.
  POINT pos;
  if (!GetCursorPos(&pos)) {
    pos.x = 0;
    pos.y = 0;
  }

  *screen = gfx::Point(pos);
  ScreenToClient(hwnd, &pos);
  *client = gfx::Point(pos);
}

}  // anonymous namespace

void TestDragDelegate::OnDragSourceCancel() {
  OnDragSourceDrop();
}

void TestDragDelegate::OnDragSourceDrop() {
  gfx::Point client;
  gfx::Point screen;
  GetCursorPositions(source_hwnd_, &client, &screen);
  webview_->DragSourceEndedAt(client, screen);
}

void TestDragDelegate::OnDragSourceMove() {
  gfx::Point client;
  gfx::Point screen;
  GetCursorPositions(source_hwnd_, &client, &screen);
  webview_->DragSourceMovedTo(client, screen);
}
