/* Copyright (c) 2019 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_CHROMIUM_SRC_CHROME_BROWSER_UI_BROWSER_H_
#define BRAVE_CHROMIUM_SRC_CHROME_BROWSER_UI_BROWSER_H_

#include "brave/browser/ui/sidebar/sidebar_controller.h"

// TODO(simonhong): Remove sidebar controller code.
// We can use BraveBrowser subclass easily after rebasing C88.
// All Browser instance creation will be done via Browser::Create().
#define BRAVE_BROWSER_H \
 public: \
  sidebar::SidebarController* sidebar_controller() { return sidebar_controller_.get(); } \
 private: \
  friend class BookmarkPrefsService; \
  friend class BraveBrowser; \
  std::unique_ptr<sidebar::SidebarController> sidebar_controller_;

#include "../../../../../chrome/browser/ui/browser.h"  // NOLINT

#undef BRAVE_BROWSER_H

#endif  // BRAVE_CHROMIUM_SRC_CHROME_BROWSER_UI_BROWSER_H_
