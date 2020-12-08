/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "bat/ledger/internal/testing/test_ledger_client.h"

#include <utility>

#include "base/logging.h"
#include "base/strings/string_number_conversions.h"
#include "net/base/escape.h"
#include "net/http/http_status_code.h"

namespace ledger {
namespace testing {

TestLedgerClient::TestLedgerClient() :
    ledger_database_(base::FilePath("")),
    state_store_(base::Value::Type::DICTIONARY),
    encrypted_state_store_(base::Value::Type::DICTIONARY),
    option_store_(base::Value::Type::DICTIONARY) {
  ledger_database_.OpenTemporaryForTesting();
}

TestLedgerClient::~TestLedgerClient() = default;

void TestLedgerClient::OnReconcileComplete(
    const type::Result result,
    type::ContributionInfoPtr contribution) {}

void TestLedgerClient::LoadLedgerState(client::OnLoadCallback callback) {
  callback(type::Result::NO_LEDGER_STATE, "");
}

void TestLedgerClient::LoadPublisherState(client::OnLoadCallback callback) {
  callback(type::Result::NO_PUBLISHER_STATE, "");
}

void TestLedgerClient::OnPanelPublisherInfo(
    type::Result result,
    type::PublisherInfoPtr publisher_info,
    uint64_t windowId) {}

void TestLedgerClient::FetchFavIcon(
    const std::string& url,
    const std::string& favicon_key,
    client::FetchIconCallback callback) {
  callback(true, favicon_key);
}

std::string TestLedgerClient::URIEncode(const std::string& value) {
  return net::EscapeQueryParamValue(value, false);
}

void TestLedgerClient::LoadURL(
    type::UrlRequestPtr request,
    client::LoadURLCallback callback) {
  DCHECK(request);
  type::UrlResponse response;
  response.url = request->url;
  response.status_code = net::HTTP_BAD_REQUEST;

  if (!network_results_.empty()) {
    TestNetworkResult front(std::move(network_results_.front()));
    network_results_.pop_front();

    bool matches = front.url == request->url && front.method == request->method;
    if (matches && front.response) {
      response = std::move(*front.response);
    }
  }

  callback(response);
}

void TestLedgerClient::Log(
    const char* file,
    const int line,
    const int verbose_level,
    const std::string& message) {
  int vlog_level = logging::GetVlogLevelHelper(file, strlen(file));
  if (verbose_level <= vlog_level) {
    logging::LogMessage(file, line, -verbose_level).stream() << message;
  }
}

void TestLedgerClient::PublisherListNormalized(type::PublisherInfoList list) {}

void TestLedgerClient::SetBooleanState(const std::string& name, bool value) {
  state_store_.SetBoolPath(name, value);
}

bool TestLedgerClient::GetBooleanState(const std::string& name) const {
  auto opt = state_store_.FindBoolPath(name);
  return opt ? *opt : false;
}

void TestLedgerClient::SetIntegerState(const std::string& name, int value) {
  state_store_.SetIntPath(name, value);
}

int TestLedgerClient::GetIntegerState(const std::string& name) const {
  auto opt = state_store_.FindIntPath(name);
  return opt ? *opt : 0;
}

void TestLedgerClient::SetDoubleState(const std::string& name, double value) {
  state_store_.SetDoublePath(name, value);
}

double TestLedgerClient::GetDoubleState(const std::string& name) const {
  auto opt = state_store_.FindDoublePath(name);
  return opt ? *opt : 0.0;
}

void TestLedgerClient::SetStringState(
    const std::string& name,
    const std::string& value) {
  state_store_.SetStringPath(name, value);
}

std::string TestLedgerClient::GetStringState(const std::string& name) const {
  auto opt = state_store_.FindStringPath(name);
  return opt ? *opt : "";
}

void TestLedgerClient::SetInt64State(const std::string& name, int64_t value) {
  state_store_.SetStringPath(name, base::NumberToString(value));
}

int64_t TestLedgerClient::GetInt64State(const std::string& name) const {
  if (auto opt = state_store_.FindStringPath(name)) {
    int64_t value;
    if (base::StringToInt64(*opt, &value)) {
      return value;
    }
  }
  return 0;
}

void TestLedgerClient::SetUint64State(
    const std::string& name,
    uint64_t value) {
  state_store_.SetStringPath(name, base::NumberToString(value));
}

uint64_t TestLedgerClient::GetUint64State(const std::string& name) const {
  if (auto opt = state_store_.FindStringPath(name)) {
    uint64_t value;
    if (base::StringToUint64(*opt, &value)) {
      return value;
    }
  }
  return 0;
}

void TestLedgerClient::ClearState(const std::string& name) {
  state_store_.RemovePath(name);
}

bool TestLedgerClient::GetBooleanOption(const std::string& name) const {
  // TODO(zenparsing):
  return false;
}

int TestLedgerClient::GetIntegerOption(const std::string& name) const {
  return 0;
}

double TestLedgerClient::GetDoubleOption(const std::string& name) const {
  return 0.0;
}

std::string TestLedgerClient::GetStringOption(const std::string& name) const {
  return "";
}

int64_t TestLedgerClient::GetInt64Option(const std::string& name) const {
  return 0;
}

uint64_t TestLedgerClient::GetUint64Option(const std::string& name) const {
  return 0;
}

void TestLedgerClient::OnContributeUnverifiedPublishers(
    type::Result result,
    const std::string& publisher_key,
    const std::string& publisher_name) {}

std::string TestLedgerClient::GetLegacyWallet() {
  return "???";
}

void TestLedgerClient::ShowNotification(
    const std::string& type,
    const std::vector<std::string>& args,
    client::ResultCallback callback) {}

type::ClientInfoPtr TestLedgerClient::GetClientInfo() {
  auto info = type::ClientInfo::New();
  info->platform = type::Platform::DESKTOP;
  info->os = type::OperatingSystem::UNDEFINED;
  return info;
}

void TestLedgerClient::UnblindedTokensReady() {}

void TestLedgerClient::ReconcileStampReset() {}

void TestLedgerClient::RunDBTransaction(
    type::DBTransactionPtr transaction,
    client::RunDBTransactionCallback callback) {
  // TODO(zenparsing): Do this in a separate task? All of these methods that
  // accept callbacks should post and reply
  auto response = type::DBCommandResponse::New();
  ledger_database_.RunTransaction(std::move(transaction), response.get());
  callback(std::move(response));
}

void TestLedgerClient::GetCreateScript(
    client::GetCreateScriptCallback callback) {
  callback("", 0);
}

void TestLedgerClient::PendingContributionSaved(const type::Result result) {}

void TestLedgerClient::ClearAllNotifications() {}

void TestLedgerClient::WalletDisconnected(const std::string& wallet_type) {}

void TestLedgerClient::DeleteLog(client::ResultCallback callback) {
  callback(type::Result::LEDGER_OK);
}

bool TestLedgerClient::SetEncryptedStringState(
    const std::string& name,
    const std::string& value) {
  encrypted_state_store_.SetStringPath(name, value);
  return true;
}

std::string TestLedgerClient::GetEncryptedStringState(const std::string& name) {
  auto opt = encrypted_state_store_.FindStringPath(name);
  return opt ? *opt : "";
}

void TestLedgerClient::SetOptionForTesting(
    const std::string& name,
    base::Value&& value) {
  option_store_.SetPath(name, std::move(value));
}

void TestLedgerClient::SetNetworkResultsForTesting(
    std::list<TestNetworkResult>&& list) {
  network_results_ = std::move(list);
}

}  // namespace testing
}  // namespace ledger
