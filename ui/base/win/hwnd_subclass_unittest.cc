// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "base/basictypes.h"
#include "testing/gtest/include/gtest/gtest.h"
#include "ui/base/win/window_impl.h"
#include "ui/base/win/hwnd_subclass.h"

namespace ui {

typedef testing::Test HWNDSubclassTest;

namespace {

class TestWindow : public ui::WindowImpl {
 public:
  TestWindow() : saw_message(false) {}
  virtual ~TestWindow() {}

  bool saw_message;

 private:
   // Overridden from ui::WindowImpl:
  virtual BOOL ProcessWindowMessage(HWND window,
                                    UINT message,
                                    WPARAM w_param,
                                    LPARAM l_param,
                                    LRESULT& result,
                                    DWORD msg_map_id) OVERRIDE {
    if (message == WM_NCHITTEST)
      saw_message = true;

    return FALSE;  // Results in DefWindowProc().
  }

  DISALLOW_COPY_AND_ASSIGN(TestWindow);
};

class TestMessageFilter : public HWNDMessageFilter {
 public:
  TestMessageFilter() : consume_messages(false), saw_message(false) {}
  virtual ~TestMessageFilter() {}

  // Setting to true causes the filter subclass to stop messages from reaching
  // the subclassed window procedure.
  bool consume_messages;

  // True if the message filter saw the message.
  bool saw_message;

 private:
  // Overridden from HWNDMessageFilter:
  virtual bool FilterMessage(HWND hwnd,
                             UINT message,
                             WPARAM w_param,
                             LPARAM l_param,
                             LRESULT* l_result) OVERRIDE {
    if (message == WM_NCHITTEST) {
      saw_message = true;
      return consume_messages;
    }
    return false;
  }

  DISALLOW_COPY_AND_ASSIGN(TestMessageFilter);
};

}  // namespace

TEST_F(HWNDSubclassTest, Filtering) {
  TestWindow window;
  window.Init(NULL, gfx::Rect(0, 0, 100, 100));
  EXPECT_TRUE(window.hwnd() != NULL);

  {
    TestMessageFilter* mf = new TestMessageFilter;
    HWNDSubclass subclass(window.hwnd());
    subclass.SetFilter(mf);

    // We are not filtering, so both the filter and the window should receive
    // this message:
    ::SendMessage(window.hwnd(), WM_NCHITTEST, 0, 0);

    EXPECT_TRUE(mf->saw_message);
    EXPECT_TRUE(window.saw_message);

    mf->saw_message = false;
    window.saw_message = false;

    mf->consume_messages = true;

    // We are now filtering, so only the filter should see this message:
    ::SendMessage(window.hwnd(), WM_NCHITTEST, 0, 0);

    EXPECT_TRUE(mf->saw_message);
    EXPECT_FALSE(window.saw_message);
  }
}

}  // namespace ui
