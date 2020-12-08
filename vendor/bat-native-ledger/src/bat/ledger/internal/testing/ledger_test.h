/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "base/run_loop.h"
#include "base/test/task_environment.h"
#include "bat/ledger/internal/ledger_impl.h"
#include "bat/ledger/internal/testing/test_ledger_client.h"
#include "testing/gtest/include/gtest/gtest.h"

namespace ledger {
namespace testing {

template<typename R, typename F>
R WaitFor(F fn) {
  R result;
  base::RunLoop run_loop;
  fn([&run_loop, &result](auto value) {
    result = std::move(value);
    run_loop.Quit();
  });
  run_loop.Run();
  return result;
}

class LedgerTest : public ::testing::Test {
 protected:
  LedgerTest();

  void SetUp() override;

  void ExecuteSQL(const std::string& sql);

  Ledger* ledger() { return &ledger_; }
  TestLedgerClient* client() { return &client_; }

  base::test::TaskEnvironment task_environment_;
  TestLedgerClient client_;
  LedgerImpl ledger_;
};

}  // namespace testing
}  // namespace ledger
