/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_CHROMIUM_SRC_COMPONENTS_SYNC_DRIVER_SYNC_AUTH_MANAGER_H_
#define BRAVE_CHROMIUM_SRC_COMPONENTS_SYNC_DRIVER_SYNC_AUTH_MANAGER_H_

namespace syncer {
class BraveSyncAuthManager;
}  // namespace syncer

#define BRAVE_SYNC_AUTH_MANAGER_H_ \
  friend BraveSyncAuthManager; \
  virtual

#define RequestAccessToken virtual RequestAccessToken

#include "../../../../../components/sync/driver/sync_auth_manager.h"

#undef BRAVE_SYNC_AUTH_MANAGER_H_
#undef RequestAccessToken
#endif  // BRAVE_CHROMIUM_SRC_COMPONENTS_SYNC_DRIVER_SYNC_AUTH_MANAGER_H_