// Copyright (c) 2024 The Brave Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import * as React from 'react'

// Mock Data
import {
  mockBasicAttentionToken, //
} from '../../../../stories/mock-data/mock-asset-options'

// Components
import {
  WalletPageStory, //
} from '../../../../stories/wrappers/wallet-page-story-wrapper'
import { EditTokenModal } from './edit_token_modal'

export const _EditTokenModal = {}

export default {
  component: EditTokenModal,
  title: 'Wallet/Desktop/Components/Popup Modals',
  render: () => (
    <WalletPageStory>
      <EditTokenModal
        onClose={() => {}}
        token={mockBasicAttentionToken}
      />
    </WalletPageStory>
  ),
}
