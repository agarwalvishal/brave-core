/* Copyright (c) 2019 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "brave/components/search_engines/brave_prepopulated_engines.h"

#include "build/build_config.h"
#include "components/search_engines/search_engine_type.h"
#include "third_party/search_engines_data/resources/definitions/prepopulated_engines.h"

namespace TemplateURLPrepopulateData {

// ****************************************************************************
// IMPORTANT! Make sure to bump the value of kBraveCurrentDataVersion in
// brave_prepopulated_engines.h if you add, remove, or make changes
// to the engines in here or to mappings in
// chromium_src/components/regional_capabilities/regional_capabilities_utils.cc.
// ****************************************************************************

namespace {

PrepopulatedEngine MakeBravePrepopulatedEngine(
    const char16_t* const name,
    const char16_t* const keyword,
    const char* const favicon_url,
    const char* const base_builtin_resource_id,
    const char* const search_url,
    const char* const encoding,
    const char* const suggest_url,
    SearchEngineType type,
    const int id) {
  return {name,
          keyword,
          favicon_url,
          base_builtin_resource_id,
          search_url,
          encoding,
          suggest_url,
          /*image_url=*/nullptr,
          /*image_translate_url=*/nullptr,
          /*new_tab_url=*/nullptr,
          /*contextual_search_url=*/nullptr,
          /*logo_url=*/nullptr,
          /*doodle_url=*/nullptr,
          /*search_url_post_params=*/nullptr,
          /*suggest_url_post_params=*/nullptr,
          /*image_url_post_params=*/nullptr,
          /*image_translate_source_language_param_key=*/nullptr,
          /*image_translate_target_language_param_key=*/nullptr,
          /*image_search_branding_label=*/nullptr,
          /*search_intent_params=*/{},
          /*alternate_urls=*/{},
          type,
          /*preconnect_to_search_url=*/nullptr,
          /*prefetch_likely_navigations=*/nullptr,
          id,
          /*regulatory_extensions=*/{}};
}

PrepopulatedEngine ModifyEngineParams(const PrepopulatedEngine& engine,
                                      const char16_t* const name,
                                      const char16_t* const keyword,
                                      const char* const search_url,
                                      const char* const suggest_url,
                                      const char* const image_url,
                                      int id) {
  return {name ? name : engine.name,
          keyword ? keyword : engine.keyword,
          engine.favicon_url,
          engine.base_builtin_resource_id,
          search_url ? search_url : engine.search_url,
          engine.encoding,
          suggest_url ? suggest_url : engine.suggest_url,
          image_url ? image_url : engine.image_url,
          engine.image_translate_url,
          engine.new_tab_url,
          engine.contextual_search_url,
          engine.logo_url,
          engine.doodle_url,
          engine.search_url_post_params,
          engine.suggest_url_post_params,
          engine.image_url_post_params,
          engine.image_translate_source_language_param_key,
          engine.image_translate_target_language_param_key,
          engine.image_search_branding_label,
          engine.search_intent_params,
          engine.alternate_urls,
          engine.type,
          engine.preconnect_to_search_url,
          engine.prefetch_likely_navigations,
          id > 0 ? id : engine.id};
}

}  // namespace

// LINT.IfChange
const PrepopulatedEngine duckduckgo = MakeBravePrepopulatedEngine(
    u"DuckDuckGo",
    u":d",
    "https://duckduckgo.com/favicon.ico",
    "IDR_SEARCH_ENGINE_DUCKDUCKGO",
    "https://duckduckgo.com/?q={searchTerms}&t=brave",
    "UTF-8",
    "https://ac.duckduckgo.com/ac/?q={searchTerms}&type=list",
    SEARCH_ENGINE_DUCKDUCKGO,
    PREPOPULATED_ENGINE_ID_DUCKDUCKGO);
// LINT.ThenChange(//brave/components/search_engines/brave_prepopulated_engines.h:kBraveCurrentDataVersion)

// LINT.IfChange
const PrepopulatedEngine duckduckgo_de =
    ModifyEngineParams(duckduckgo,
                       nullptr,
                       nullptr,
                       "https://duckduckgo.com/?q={searchTerms}&t=bravened",
                       nullptr,
                       nullptr,
                       PREPOPULATED_ENGINE_ID_DUCKDUCKGO_DE);
// LINT.ThenChange(//brave/components/search_engines/brave_prepopulated_engines.h:kBraveCurrentDataVersion)

// LINT.IfChange
const PrepopulatedEngine duckduckgo_au_nz_ie =
    ModifyEngineParams(duckduckgo,
                       nullptr,
                       nullptr,
                       "https://duckduckgo.com/?q={searchTerms}&t=braveed",
                       nullptr,
                       nullptr,
                       PREPOPULATED_ENGINE_ID_DUCKDUCKGO_AU_NZ_IE);
// LINT.ThenChange(//brave/components/search_engines/brave_prepopulated_engines.h:kBraveCurrentDataVersion)

#if BUILDFLAG(IS_ANDROID)
// LINT.IfChange
const PrepopulatedEngine duckduckgo_lite = MakeBravePrepopulatedEngine(
    u"DuckDuckGo Lite",
    u":dl",
    "https://duckduckgo.com/favicon.ico",
    "IDR_SEARCH_ENGINE_DUCKDUCKGO",
    "https://duckduckgo.com/lite/?q={searchTerms}&t=brave",
    "UTF-8",
    "https://ac.duckduckgo.com/ac/?q={searchTerms}&type=list",
    SEARCH_ENGINE_DUCKDUCKGO,
    PREPOPULATED_ENGINE_ID_DUCKDUCKGO_LITE);
// LINT.ThenChange(//brave/components/search_engines/brave_prepopulated_engines.h:kBraveCurrentDataVersion)
#endif  // BUILDFLAG(IS_ANDROID)

// LINT.IfChange
const PrepopulatedEngine brave_ecosia =
    ModifyEngineParams(ecosia,
                       nullptr,
                       u":e",
                       "https://www.ecosia.org/search?tt="
#if BUILDFLAG(IS_ANDROID)
                       "42b8ae98"
#else
                       "e8eb07a6"
#endif
                       "&q={searchTerms}&addon=brave",
                       "https://ac.ecosia.org/?q={searchTerms}",
                       nullptr,
                       PREPOPULATED_ENGINE_ID_ECOSIA);
// LINT.ThenChange(//brave/components/search_engines/brave_prepopulated_engines.h:kBraveCurrentDataVersion)

// LINT.IfChange
const PrepopulatedEngine qwant = MakeBravePrepopulatedEngine(
    u"Qwant",
    u":q",
    "https://www.qwant.com/favicon.ico",
    "IDR_SEARCH_ENGINE_QWANT",
    "https://www.qwant.com/?q={searchTerms}&client=brz-brave",
    "UTF-8",
    "https://api.qwant.com/api/suggest/?q={searchTerms}&client=opensearch",
    SEARCH_ENGINE_QWANT,
    PREPOPULATED_ENGINE_ID_QWANT);
// LINT.ThenChange(//brave/components/search_engines/brave_prepopulated_engines.h:kBraveCurrentDataVersion)

// LINT.IfChange
const PrepopulatedEngine brave_startpage =
    ModifyEngineParams(startpage,
                       u"Startpage",
                       u":sp",
                       "https://www.startpage.com/do/"
                       "search?q={searchTerms}&segment=startpage.brave",
                       "https://www.startpage.com/cgi-bin/"
                       "csuggest?query={searchTerms}&limit=10&format=json",
                       nullptr,
                       PREPOPULATED_ENGINE_ID_STARTPAGE);
// LINT.ThenChange(//brave/components/search_engines/brave_prepopulated_engines.h:kBraveCurrentDataVersion)

// LINT.IfChange
const PrepopulatedEngine brave_yandex =
    ModifyEngineParams(yandex_com,
                       u"Yandex",
                       nullptr,
                       "https://yandex.ru/search/?clid="
#if BUILDFLAG(IS_ANDROID)
                       "2423859"
#else
                       "2353835"
#endif
                       "&text={searchTerms}",
                       "https://suggest.yandex.ru/suggest-ff.cgi?"
                       "part={searchTerms}&v=3&sn=5&srv=brave_desktop",
                       nullptr,
                       PREPOPULATED_ENGINE_ID_YANDEX);
// LINT.ThenChange(//brave/components/search_engines/brave_prepopulated_engines.h:kBraveCurrentDataVersion)

// LINT.IfChange
const PrepopulatedEngine brave_search = MakeBravePrepopulatedEngine(
    u"Brave",
    u":br",
    "https://cdn.search.brave.com/serp/favicon.ico",
    "IDR_SEARCH_ENGINE_BRAVE",
    "https://search.brave.com/search?q={searchTerms}&source="
#if BUILDFLAG(IS_ANDROID)
    "android",
#else
    "desktop",
#endif
    "UTF-8",
    "https://search.brave.com/api/"
    "suggest?q={searchTerms}&rich=true&source="
#if BUILDFLAG(IS_ANDROID)
    "android",
#else
    "desktop",
#endif
    SEARCH_ENGINE_OTHER,
    PREPOPULATED_ENGINE_ID_BRAVE);
// LINT.ThenChange(//brave/components/search_engines/brave_prepopulated_engines.h:kBraveCurrentDataVersion)

// LINT.IfChange
const PrepopulatedEngine brave_search_tor = ModifyEngineParams(
    brave_search,
    nullptr,
    u":search.brave4u7jddbv7cyviptqjc7jusxh72uik7zt6adtckl5f4nwy2v72qd.onion",
    "https://"
    "search.brave4u7jddbv7cyviptqjc7jusxh72uik7zt6adtckl5f4nwy2v72qd.onion/"
    "search?q={searchTerms}",
    "https://"
    "search.brave4u7jddbv7cyviptqjc7jusxh72uik7zt6adtckl5f4nwy2v72qd.onion/api/"
    "suggest?q={searchTerms}",
    nullptr,
    PREPOPULATED_ENGINE_ID_BRAVE_TOR);
// LINT.ThenChange(//brave/components/search_engines/brave_prepopulated_engines.h:kBraveCurrentDataVersion)

// LINT.IfChange
const PrepopulatedEngine brave_bing = ModifyEngineParams(
    bing,
    u"Bing",
    u":b",
    "https://www.bing.com/search?q={searchTerms}",
    "https://www.bing.com/osjson.aspx?query={searchTerms}&language={language}",
    "https://www.bing.com/images/detail/search?iss=sbiupload#enterInsights",
    PREPOPULATED_ENGINE_ID_BING);
// LINT.ThenChange(//brave/components/search_engines/brave_prepopulated_engines.h:kBraveCurrentDataVersion)

// LINT.IfChange
const PrepopulatedEngine brave_yahoo_jp = ModifyEngineParams(
    yahoo_jp,
    u"Yahoo! JAPAN",
    nullptr,  // keyword
    // search url
    "https://search.yahoo.co.jp/search?p={searchTerms}&ei={inputEncoding}&fr="
#if BUILDFLAG(IS_ANDROID)
    "brave-mobile_ext",
#else
    "brave-desktop_ext",
#endif
    // suggest url
    "https://search.yahooapis.jp/AssistSearchService/V2/"
    "webassistSearch?p={searchTerms}&appid="
    "dj00aiZpPXVyZmc2WDgzWnA5SSZzPWNvbnN1bWVyc2VjcmV0Jng9MTE-"
    "&output=fxjson&fr="
#if BUILDFLAG(IS_ANDROID)
    "brave-mobile_ext",
#else
    "brave-desktop_ext",
#endif
    // image url
    "https://search.yahoo.co.jp/image/"
    "search?p={searchTerms}&ei={inputEncoding}&fr="
#if BUILDFLAG(IS_ANDROID)
    "brave-mobile_ext",
#else
    "brave-desktop_ext",
#endif
    PREPOPULATED_ENGINE_ID_YAHOO_JP);
// LINT.ThenChange(//brave/components/search_engines/brave_prepopulated_engines.h:kBraveCurrentDataVersion)

// LINT.IfChange
const PrepopulatedEngine brave_google =
    ModifyEngineParams(google, nullptr, u":g", nullptr, nullptr, nullptr, 0);
// LINT.ThenChange(//brave/components/search_engines/brave_prepopulated_engines.h:kBraveCurrentDataVersion)

}  // namespace TemplateURLPrepopulateData
