#ifndef XBLINK_ENGINE_WINDOW_H
#define XBLINK_ENGINE_WINDOW_H

#include "ui/views/widget/widget_delegate.h"
#include "base/timer/timer.h"

namespace XB {

class EngineWindow : public views::WidgetDelegateView {
public:
  EngineWindow();
  ~EngineWindow() override;

  // WidgetDelegate:
  void DeleteDelegate() override;
  views::Widget* GetWidget() override;
  const views::Widget* GetWidget() const override;
  views::View* GetContentsView() override;

  // View:
  const char* GetClassName() const override;

  void Layout() override;
  void OnBoundsChanged(const gfx::Rect& previous_bounds) override;

private:
  void timer_shot();
  base::RepeatingTimer timer_;
  View* child_view_;
  View* circle_button_;
  views::Widget* window_widget_;
};

} //end namespace XB
#endif
