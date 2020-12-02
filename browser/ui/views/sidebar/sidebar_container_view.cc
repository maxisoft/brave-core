/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include <memory>

#include "brave/browser/ui/views/sidebar/sidebar_container_view.h"

#include "brave/browser/ui/views/sidebar/sidebar_items_container_view.h"
#include "ui/views/border.h"
#include "ui/views/controls/webview/webview.h"
#include "url/gurl.h"

namespace {
constexpr int kBorderThickness = 1;
constexpr int kSidebarItemsViewWidth = 40;
}

SidebarContainerView::SidebarContainerView(
    content::BrowserContext* browser_context) {
  SetBorder(views::CreateSolidSidedBorder(0, 0, 0, kBorderThickness,
                                          SkColorSetRGB(0xD9, 0xDC, 0xDF)));
  sidebar_items_container_view_ =
      AddChildView(std::make_unique<SidebarItemsContainerView>());
  webview_ = AddChildView(std::make_unique<views::WebView>(browser_context));
  webview_->LoadInitialURL(GURL("https://together.brave.com/"));
}

SidebarContainerView::~SidebarContainerView() = default;

void SidebarContainerView::Layout() {
  sidebar_items_container_view_->SetBounds(
      0, 0, kSidebarItemsViewWidth, height());
  webview_->SetBounds(kSidebarItemsViewWidth,
                      0,
                      width() - kSidebarItemsViewWidth - kBorderThickness,
                      height());
}
