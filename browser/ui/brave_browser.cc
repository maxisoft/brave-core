/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "brave/browser/ui/brave_browser.h"

#if BUILDFLAG(ENABLE_SIDEBAR)
#include "base/feature_list.h"
#include "brave/browser/ui/sidebar/sidebar_controller.h"
#include "brave/components/sidebar/features.h"
#endif

BraveBrowser::BraveBrowser(const CreateParams& params)
    : Browser(params) {
#if BUILDFLAG(ENABLE_SIDEBAR)
  // TODO(simonhong): Enable this after C88.
  // Before that Browser owns controller instead.
  // if (!base::FeatureList::IsEnabled(sidebar::kSidebarFeature) ||
  //      !is_type_normal()) {
  //   return;
  // }
  // sidebar_controller_.reset(new sidebar::SidebarController(profile()));
#endif
}

BraveBrowser::~BraveBrowser() = default;
