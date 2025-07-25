/* Copyright (c) 2024 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_BROWSER_UI_VIEWS_SPLIT_VIEW_SPLIT_VIEW_SEPARATOR_H_
#define BRAVE_BROWSER_UI_VIEWS_SPLIT_VIEW_SPLIT_VIEW_SEPARATOR_H_

#include <memory>

#include "base/gtest_prod_util.h"
#include "base/memory/raw_ptr.h"
#include "base/scoped_observation.h"
#include "brave/browser/ui/views/split_view/split_view_separator_delegate.h"
#include "ui/views/controls/resize_area.h"
#include "ui/views/controls/resize_area_delegate.h"
#include "ui/views/view.h"
#include "ui/views/widget/widget.h"
#include "ui/views/widget/widget_observer.h"

class Browser;

// A separator view that is located between contents web views in BrowserView.
// This separator is used to resize the contents web views.
class SplitViewSeparator : public views::ResizeArea,
                           public views::ResizeAreaDelegate,
                           public views::WidgetObserver,
                           public views::ViewObserver {
  METADATA_HEADER(SplitViewSeparator, views::ResizeArea)
 public:
  explicit SplitViewSeparator(Browser* browser);
  ~SplitViewSeparator() override;

  void set_resize_delegate(views::ResizeAreaDelegate* delegate) {
    resize_area_delegate_ = delegate;
  }

  void set_separator_delegate(SplitViewSeparatorDelegate* delegate) {
    separator_delegate_ = delegate;
  }

  void ShowMenuButtonWidget();

  // views::View:
  void AddedToWidget() override;
  void VisibilityChanged(views::View* starting_from, bool is_visible) override;
  bool OnMousePressed(const ui::MouseEvent& event) override;
  void Layout(PassKey) override;
  void ViewHierarchyChanged(
      const views::ViewHierarchyChangedDetails& details) override;
  void OnBoundsChanged(const gfx::Rect& previous_bounds) override;
  void OnPaintBackground(gfx::Canvas* canvas) override;

  // views::ResizeAreaDelegate:
  void OnResize(int resize_amount, bool done_resizing) override;

  // views::WidgetObserver:
  void OnWidgetBoundsChanged(views::Widget* widget,
                             const gfx::Rect& new_bounds) override;

  // views::ViewObserver:
  void OnViewBoundsChanged(views::View* observed_view) override;

 private:
  FRIEND_TEST_ALL_PREFIXES(SideBySideEnabledBrowserTest,
                           BraveMultiContentsViewTest);
  FRIEND_TEST_ALL_PREFIXES(SideBySideEnabledBrowserTest, SelectTabTest);
  FRIEND_TEST_ALL_PREFIXES(SplitViewBrowserTest,
                           TilingTwoTabsMakesSecondaryWebViewVisible);
  FRIEND_TEST_ALL_PREFIXES(SplitViewBrowserTest,
                           BreakingTileMakesSecondaryWebViewHidden);
  FRIEND_TEST_ALL_PREFIXES(SplitViewBrowserTest,
                           ActivateNonTiledTabShouldHideSecondaryWebView);

  void CreateMenuButton();
  void LayoutMenuButton();

  raw_ptr<Browser> browser_ = nullptr;

  raw_ptr<views::ResizeAreaDelegate> resize_area_delegate_ = nullptr;

  raw_ptr<SplitViewSeparatorDelegate> separator_delegate_ = nullptr;

  std::unique_ptr<views::Widget> menu_button_widget_;

  base::ScopedObservation<views::Widget, views::WidgetObserver>
      parent_widget_observation_{this};

  base::ScopedObservation<views::View, views::ViewObserver>
      parent_view_observation_{this};
};

#endif  // BRAVE_BROWSER_UI_VIEWS_SPLIT_VIEW_SPLIT_VIEW_SEPARATOR_H_
