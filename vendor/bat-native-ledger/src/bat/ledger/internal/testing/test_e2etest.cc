/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "bat/ledger/internal/testing/ledger_test.h"
#include "bat/ledger/option_keys.h"

// npm run test -- brave_unit_tests --filter=TestE2ETest.*

namespace ledger {
namespace testing {

class TestE2ETest : public LedgerTest {};

TEST_F(TestE2ETest, LinkBraveWallet) {
  // We'll need to set up:
  // - insert unblinded tokens
  // - insert promotions
  // - mock post_claim_brave

  client()->SetOptionForTesting(ledger::option::kClaimUGP, base::Value(true));

  ExecuteSQL(R"sql(

    INSERT INTO promotion (
      promotion_id, version, type, public_keys, suggestions,
      approximate_value, status, expires_at, claimed_at, legacy
    ) VALUES (
      'p0', 0, 0, '-', 0, 0, 0, 0, 0, FALSE
    );

    INSERT INTO promotion (
      promotion_id, version, type, public_keys, suggestions,
      approximate_value, status, expires_at, claimed_at, legacy
    ) VALUES (
      'p1', 0, 0, '-', 0, 0, 0, 0, 0, FALSE
    );

    /* creds_id needs to match creds_batch.creds_id */
    INSERT INTO unblinded_token (
      token_id, token_value, public_key, value, creds_id, expires_at
    ) VALUES (
      ?, ?, ?, ?, ?, ?
    );

    /* trigger_id needs to match promotion.promotion_id */
    INSERT INTO creds_batch (
      creds_id, trigger_id, trigger_type, creds, blinded_creds,
      signed_creds, public_key, batch_proof, status
    ) VALUES (
      ?, ?, ?, ?, ?, ?, ?, ?, ?
    );

  )sql");

  ASSERT_TRUE(true);
}

}  // namespace testing
}  // namespace ledger
