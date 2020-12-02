/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "brave/components/sidebar/sidebar_service.h"

#include "base/feature_list.h"
#include "base/values.h"
#include "brave/components/sidebar/features.h"
#include "brave/components/sidebar/pref_names.h"
#include "components/prefs/pref_registry_simple.h"
#include "components/prefs/pref_service.h"

namespace sidebar {

// static void
void SidebarService::RegisterPrefs(PrefRegistrySimple* registry) {
  if (!base::FeatureList::IsEnabled(kSidebarFeature))
    return;

  registry->RegisterListPref(kSidebarItems);
}

SidebarService::SidebarService(PrefService* prefs) : prefs_(prefs) {
  DCHECK(prefs_);
}

SidebarService::~SidebarService() = default;

void SidebarService::AddItem(const SidebarItem& item) {
}

void SidebarService::RemoveItem(const SidebarItem& item) {
}

std::vector<SidebarItem> SidebarService::GetSidebarItems() const {
  std::vector<SidebarItem> items;

  auto* items_value = prefs_->Get(kSidebarItems);
  if (items_value->GetList().empty())
    return items;

  // TODO(): Load stored items from prefs.
  return items;
}

}  // namespace sidebar
