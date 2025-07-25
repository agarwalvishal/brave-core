// Copyright 2024 The Brave Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

import Foundation
import Preferences

extension Preferences {
  public struct AIChat {
    /// A boolean indicating whether the user has seen the AI-Chat intro screen at least once
    public static let hasSeenIntro = Option<Bool>(
      key: "aichat.intro.hasBeenSeen",
      default: false
    )

    /// The date the user's current AI-Chat subscription expires
    public static let subscriptionExpirationDate = Option<Date?>(
      key: "aichat.expiration-date",
      default: nil
    )

    /// A boolean indicating whether or not the user has dismissed the Premium Prompt on the Feedback Form
    public static let showPremiumFeedbackAd = Option<Bool>(
      key: "aichat.show-premium-feedback-ad",
      default: true
    )

    /// A boolean indicating whether or not to show Leo button inside the Quick Search Engines Bar
    public static let leoInQuickSearchBarEnabled = Option<Bool>(
      key: "aichat.leo-in-quick-search-bar-enabled",
      default: true
    )

    /// Flag that determines whether or not to show the Feedback Privacy Warning
    public static let showFeedbackPrivacyWarning = Option<Bool>(
      key: "aichat.feedback-privacy-warning",
      default: true
    )
  }
}
