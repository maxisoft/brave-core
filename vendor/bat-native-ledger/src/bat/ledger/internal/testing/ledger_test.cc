/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "bat/ledger/internal/testing/ledger_test.h"

namespace ledger {
namespace testing {

LedgerTest::LedgerTest() : client_(), ledger_(&client_) {}

void LedgerTest::SetUp() {
  auto result = WaitFor<type::Result>([this](auto done) {
    ledger()->Initialize(false, done);
  });
  ASSERT_EQ(result, type::Result::LEDGER_OK);
}

void LedgerTest::ExecuteSQL(const std::string& sql) {
  auto response = WaitFor<type::DBCommandResponsePtr>(
    [this, &sql](auto done) {
      auto command = type::DBCommand::New();
      command->type = type::DBCommand::Type::EXECUTE;
      command->command = sql;

      auto transaction = type::DBTransaction::New();
      transaction->commands.push_back(std::move(command));
      client_.RunDBTransaction(std::move(transaction), done);
    });
  ASSERT_TRUE(response);
  ASSERT_EQ(response->status, type::DBCommandResponse::Status::RESPONSE_OK);
}

}  // namespace testing
}  // namespace ledger
