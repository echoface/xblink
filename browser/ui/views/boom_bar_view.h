#ifndef XBLINK_BOOM_BAR_VIEW_H
#define XBLINK_BOOM_BAR_VIEW_H

#include "ui/views/view.h"
#include "ui/views/widget/widget_delegate.h"

namespace XB {

class BoomBarView : public views::View {
public:
  BoomBarView();
  ~BoomBarView() override;

  void Layout() override;
  void OnBoundsChanged(const gfx::Rect& previous_bounds) override;
private:

  views::View* home_;
  views::View* pages_view_;
  views::View* uri_input_;
  views::View* page_action_;
  views::View* settings_;
};

}// end namespace XB
#endif
