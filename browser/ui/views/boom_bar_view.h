#ifndef XBLINK_BOOM_BAR_VIEW_H
#define XBLINK_BOOM_BAR_VIEW_H

#include "ui/views/view.h"
#include "ui/views/widget/widget_delegate.h"
#include "ui/views/controls/label.h"

namespace XB {

class TLabel : public views::Label {
public:
  TLabel(base::string16 label);
  ~TLabel() override;

  void OnBlur() override;
  void OnFocus() override;
};

class BoomBarView : public views::View {
public:
  BoomBarView();
  ~BoomBarView() override;

  void Layout() override;
  void OnBoundsChanged(const gfx::Rect& previous_bounds) override;

  void OnBlur() override;
  void OnFocus() override;
  bool OnKeyPressed(const ui::KeyEvent& event) override;
  bool OnKeyReleased(const ui::KeyEvent& event) override;
private:

  views::View* home_;
  views::View* pages_view_;
  views::View* uri_input_;
  views::View* page_action_;
  views::View* settings_;
};

}// end namespace XB
#endif
