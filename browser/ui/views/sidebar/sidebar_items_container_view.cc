/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "brave/browser/ui/views/sidebar/sidebar_items_container_view.h"

#include "brave/grit/brave_theme_resources.h"
#include "ui/base/resource/resource_bundle.h"
#include "ui/views/background.h"
#include "ui/views/border.h"
#include "ui/views/controls/image_view.h"
#include "ui/views/layout/box_layout.h"

SidebarItemsContainerView::SidebarItemsContainerView() {
  SetBackground(views::CreateSolidBackground(SkColorSetRGB(0xF3, 0xF3, 0xF5)));
  SetBorder(views::CreateSolidSidedBorder(0, 0, 0, 1,
                                          SkColorSetRGB(0xD9, 0xDC, 0xDF)));
  SetLayoutManager(std::make_unique<views::BoxLayout>(
      views::BoxLayout::Orientation::kVertical, gfx::Insets(15, 0), 26));
  InitItems();
}

SidebarItemsContainerView::~SidebarItemsContainerView() = default;

void SidebarItemsContainerView::InitItems() {
  auto& bundle = ui::ResourceBundle::GetSharedInstance();
  auto* image_view = AddChildView(std::make_unique<views::ImageView>());
  image_view->SetImage(bundle.GetImageSkiaNamed(IDR_SIDEBAR_BRAVE_TOGETHER));
  image_view = AddChildView(std::make_unique<views::ImageView>());
  image_view->SetImage(bundle.GetImageSkiaNamed(IDR_SIDEBAR_BRAVE_TOGETHER));
  image_view = AddChildView(std::make_unique<views::ImageView>());
  image_view->SetImage(bundle.GetImageSkiaNamed(IDR_SIDEBAR_BRAVE_TOGETHER));
}
