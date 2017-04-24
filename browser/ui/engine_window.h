#ifndef XBLINK_ENGINE_WINDOW_H
#define XBLINK_ENGINE_WINDOW_H

#include <iostream>
#include "base/timer/timer.h"
#include "views/boom_bar_view.h"
#include "ui/views/widget/widget_delegate.h"
#include "ui/events/platform/platform_event_observer.h"
//#include "ui/events/platform/platform_event_dispatcher.h"

namespace views {
  class WebView;
}

namespace XB {

class OperationPanel;

class EngineWindow : public views::WidgetDelegateView,
                     public ui::PlatformEventObserver {
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
  bool AcceleratorPressed(const ui::Accelerator& accelerator) override;

  void Layout() override;
  void OnBoundsChanged(const gfx::Rect& previous_bounds) override;

  // widget delegate
  View* CreateOverlayView() override;

  void WillProcessEvent(const ui::PlatformEvent& event) override;
  void DidProcessEvent(const ui::PlatformEvent& event) override;
private:
  void InitAccelerators();
  void timer_shot();
  base::RepeatingTimer timer_;

  views::WebView* web_view_;

  //View* child_view_;
  //View* circle_button_;
  views::Widget* window_widget_;

  //views::View* overlay_view_;
  OperationPanel* operation_panel_;
};

} //end namespace XB
#endif
