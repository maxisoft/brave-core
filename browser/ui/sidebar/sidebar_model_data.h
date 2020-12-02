/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_BROWSER_UI_SIDEBAR_SIDEBAR_MODEL_DATA_H_
#define BRAVE_BROWSER_UI_SIDEBAR_SIDEBAR_MODEL_DATA_H_

#include <memory>

#include "brave/components/sidebar/sidebar_item.h"

namespace content {
class WebContents;
}  // namespace content

namespace sidebar {

// Each SidebarModelData represents sidebar item's runtime state.
class SidebarModelData {
 public:
  explicit SidebarModelData(const SidebarItem& sidebar_item);
  virtual ~SidebarModelData();

 private:
  const SidebarItem sidebar_item_;
  // Each sidebar item uses its own WebContents.
  std::unique_ptr<content::WebContents> contents_;
};

}  // namespace sidebar

#endif  // BRAVE_BROWSER_UI_SIDEBAR_SIDEBAR_MODEL_DATA_H_
