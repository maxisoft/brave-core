/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "brave/browser/ui/sidebar/sidebar_model.h"

#include "base/logging.h"
#include "brave/browser/ui/sidebar/sidebar_model_data.h"
#include "brave/browser/ui/sidebar/sidebar_service_factory.h"
#include "brave/components/sidebar/sidebar_item.h"
#include "brave/components/sidebar/sidebar_service.h"

namespace sidebar {

SidebarModel::SidebarModel(Profile* profile) {
  SidebarService* service =
      SidebarServiceFactory::GetForProfile(profile);
  DCHECK(service);

  std::vector<SidebarItem> items = service->GetSidebarItems();
  if (items.empty()) {
    AddDefaultItemsData();
    return;
  }
}

SidebarModel::~SidebarModel() = default;

void SidebarModel::AddDefaultItemsData() {
  // brave together
  // crypto wallet
  // bookmarks
  // history
}

}  // namespace sidebar
