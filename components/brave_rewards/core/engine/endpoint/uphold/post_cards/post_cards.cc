/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "brave/components/brave_rewards/core/engine/endpoint/uphold/post_cards/post_cards.h"

#include <optional>
#include <utility>

#include "base/check.h"
#include "base/json/json_reader.h"
#include "base/json/json_writer.h"
#include "brave/components/brave_rewards/core/engine/rewards_engine.h"
#include "brave/components/brave_rewards/core/engine/uphold/uphold_card.h"
#include "brave/components/brave_rewards/core/engine/util/environment_config.h"
#include "brave/components/brave_rewards/core/engine/util/url_loader.h"
#include "net/http/http_status_code.h"

namespace brave_rewards::internal::endpoint::uphold {

PostCards::PostCards(RewardsEngine& engine) : engine_(engine) {}

PostCards::~PostCards() = default;

std::string PostCards::GetUrl() const {
  return engine_->Get<EnvironmentConfig>()
      .uphold_api_url()
      .Resolve("/v0/me/cards")
      .spec();
}

std::string PostCards::GeneratePayload() const {
  base::Value::Dict payload;
  payload.Set("label", internal::uphold::kCardName);
  payload.Set("currency", "BAT");

  std::string json;
  base::JSONWriter::Write(payload, &json);
  return json;
}

mojom::Result PostCards::CheckStatusCode(int status_code) const {
  if (status_code == net::HTTP_UNAUTHORIZED) {
    engine_->LogError(FROM_HERE) << "Unauthorized access";
    return mojom::Result::EXPIRED_TOKEN;
  }

  if (!URLLoader::IsSuccessCode(status_code)) {
    engine_->LogError(FROM_HERE) << "Unexpected HTTP status: " << status_code;
    return mojom::Result::FAILED;
  }

  return mojom::Result::OK;
}

mojom::Result PostCards::ParseBody(const std::string& body,
                                   std::string* id) const {
  DCHECK(id);

  std::optional<base::Value::Dict> value = base::JSONReader::ReadDict(body);
  if (!value) {
    engine_->LogError(FROM_HERE) << "Invalid JSON";
    return mojom::Result::FAILED;
  }

  const base::Value::Dict& dict = *value;
  const auto* id_str = dict.FindString("id");
  if (!id_str) {
    engine_->LogError(FROM_HERE) << "Missing id";
    return mojom::Result::FAILED;
  }

  *id = *id_str;

  return mojom::Result::OK;
}

void PostCards::Request(const std::string& token,
                        PostCardsCallback callback) const {
  auto request = mojom::UrlRequest::New();
  request->url = GetUrl();
  request->content = GeneratePayload();
  request->headers = {"Authorization: Bearer " + token};
  request->content_type = "application/json; charset=utf-8";
  request->method = mojom::UrlMethod::POST;

  engine_->Get<URLLoader>().Load(
      std::move(request), URLLoader::LogLevel::kNone,
      base::BindOnce(&PostCards::OnRequest, base::Unretained(this),
                     std::move(callback)));
}

void PostCards::OnRequest(PostCardsCallback callback,
                          mojom::UrlResponsePtr response) const {
  DCHECK(response);

  mojom::Result result = CheckStatusCode(response->status_code);
  if (result != mojom::Result::OK) {
    return std::move(callback).Run(result, "");
  }

  std::string id;
  result = ParseBody(response->body, &id);
  std::move(callback).Run(result, std::move(id));
}

}  // namespace brave_rewards::internal::endpoint::uphold
