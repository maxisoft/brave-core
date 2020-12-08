/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 3.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

<<<<<<< HEAD
#ifndef BRAVE_BROWSER_BRAVE_COSMETIC_RESOURCES_TAB_HELPER_H_
#define BRAVE_BROWSER_BRAVE_COSMETIC_RESOURCES_TAB_HELPER_H_

#include <memory>
#include <string>
=======
#ifndef BRAVE_BROWSER_ANDROID_BRAVE_COSMETIC_RESOURCES_TAB_HELPER_H_
#define BRAVE_BROWSER_ANDROID_BRAVE_COSMETIC_RESOURCES_TAB_HELPER_H_

>>>>>>> enable cf on desktop/disable extension
#include <vector>

#include "base/memory/weak_ptr.h"
#include "brave/content/browser/cosmetic_filters_observer.h"
#include "content/public/browser/web_contents_observer.h"
#include "content/public/browser/web_contents_user_data.h"

class BraveCosmeticResourcesTabHelper
    : public content::CosmeticFiltersObserver,
      public content::WebContentsObserver,
      public content::WebContentsUserData<BraveCosmeticResourcesTabHelper>,
      public base::SupportsWeakPtr<BraveCosmeticResourcesTabHelper> {
 public:
<<<<<<< HEAD
  static std::string* observing_script_;

=======
>>>>>>> enable cf on desktop/disable extension
  explicit BraveCosmeticResourcesTabHelper(content::WebContents* contents);
  ~BraveCosmeticResourcesTabHelper() override;

  // content::WebContentsObserver overrides:
  void DidFinishNavigation(
      content::NavigationHandle* navigation_handle) override;
  void ResourceLoadComplete(
      content::RenderFrameHost* render_frame_host,
      const content::GlobalRequestID& request_id,
      const blink::mojom::ResourceLoadInfo& resource_load_info) override;
  bool OnMessageReceived(const IPC::Message& message,
      content::RenderFrameHost* render_frame_host) override;
  bool OnMessageReceived(const IPC::Message& message) override;
  //

  // content::CosmeticFiltersObserver overrides:
  void HiddenClassIdSelectors(content::RenderFrameHost* render_frame_host,
      const std::vector<std::string>& classes,
      const std::vector<std::string>& ids) override;
  //

  WEB_CONTENTS_USER_DATA_KEY_DECL();

 private:
  void ProcessURL(content::RenderFrameHost* render_frame_host, const GURL& url,
      const bool& main_frame);

  std::unique_ptr<base::ListValue> GetUrlCosmeticResourcesOnTaskRunner(
      const std::string& url);
<<<<<<< HEAD
  void GetUrlCosmeticResourcesOnUI(content::GlobalFrameRoutingId frame_id,
=======
  void GetUrlCosmeticResourcesOnUI(content::RenderFrameHost* render_frame_host,
>>>>>>> enable cf on desktop/disable extension
      const std::string& url, bool main_frame,
      std::unique_ptr<base::ListValue> resources);
  void CSSRulesRoutine(const std::string& url,
      base::DictionaryValue* resources_dict,
<<<<<<< HEAD
      content::GlobalFrameRoutingId frame_id);
=======
      content::RenderFrameHost* render_frame_host);
>>>>>>> enable cf on desktop/disable extension

  std::unique_ptr<base::ListValue> GetHiddenClassIdSelectorsOnTaskRunner(
      const std::vector<std::string>& classes,
      const std::vector<std::string>& ids);
  void GetHiddenClassIdSelectorsOnUI(
      content::RenderFrameHost* render_frame_host,
      std::unique_ptr<base::ListValue> selectors);

  std::vector<std::string> exceptions_;
  bool enabled_1st_party_cf_filtering_;

  DISALLOW_COPY_AND_ASSIGN(BraveCosmeticResourcesTabHelper);
};

<<<<<<< HEAD
#endif  // BRAVE_BROWSER_BRAVE_COSMETIC_RESOURCES_TAB_HELPER_H_
=======
#endif  // BRAVE_BROWSER_ANDROID_BRAVE_COSMETIC_RESOURCES_TAB_HELPER_H_
>>>>>>> enable cf on desktop/disable extension
