// Copyright (c) 2023 The Brave Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import * as React from 'react'
import Icon from '@brave/leo/react/icon'
import Tooltip from '@brave/leo/react/tooltip'
import Button from '@brave/leo/react/button'
import { getLocale, formatLocale } from '$web-common/locale'
import * as Mojom from '../../../common/mojom'
import { useAIChat } from '../../state/ai_chat_context'
import { useConversation } from '../../state/conversation_context'
import styles from './style.module.scss'
import { getKeysForMojomEnum } from '$web-common/mojomUtils'

function getCategoryName(category: Mojom.ModelCategory) {
  // To avoid problems when order of enum values change, we base the key
  // on the enum name rather than the number value, e.g. "CHAT" vs 0
  const categoryKey = getKeysForMojomEnum(Mojom.ModelCategory)[category]
  return getLocale('CHAT_UI_MODEL_CATEGORY_' + categoryKey)
}

function getIntroMessageKey(model: Mojom.Model) {
  return `CHAT_UI_INTRO_MESSAGE_${model.key.toUpperCase().replaceAll('-', '_')}`
}

export default function ModelIntro() {
  const aiChatContext = useAIChat()
  const conversationContext = useConversation()

  const model = conversationContext.currentModel
  if (!model) {
    return <></>
  }

  return (
    <div className={styles.modelInfo}>
      <div className={styles.modelIcon}>
        <Icon name='product-brave-leo' />
      </div>
      <div className={styles.meta}>
        <h4 className={styles.category}>
          {conversationContext.isCurrentModelLeo
            ? getCategoryName(model.options.leoModelOptions!.category)
            : model.displayName}
        </h4>
        <h3 className={styles.name}>
          {conversationContext.isCurrentModelLeo
            ? model.displayName
            : model.options.customModelOptions?.modelRequestName}
          {conversationContext.isCurrentModelLeo && (
            <Tooltip
              mode='default'
              className={styles.tooltip}
              offset={4}
            >
              <div
                slot='content'
                className={styles.tooltipContent}
              >
                {formatLocale(getIntroMessageKey(model), {
                  $1: (content) => {
                      return (
                        <button
                          key={content}
                          onClick={() =>
                            aiChatContext.uiHandler?.openModelSupportUrl()
                          }
                        >
                          {content}
                        </button>
                      )
                  }
                })}
              </div>
              <Button
                fab
                kind='plain-faint'
                className={styles.tooltipButton}
              >
                <Icon name='info-outline' />
              </Button>
            </Tooltip>
          )}
        </h3>
      </div>
    </div>
  )
}
