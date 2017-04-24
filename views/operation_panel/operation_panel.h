#ifndef XBLINK_OPERATION_PANNEL_H_
#define XBLINK_OPERATION_PANNEL_H_

#include <stdlib.h>
#include "ui/views/widget/widget.h"
#include "ui/views/widget/widget_delegate.h"
#include "ui/views/widget/widget_observer.h"

#include "Xblink/browser/ui/views/boom_bar_view.h"

namespace XB {

class OperationPanel : public views::WidgetDelegateView,
                       public views::WidgetObserver {
public:
  OperationPanel(views::Widget* parent);
  ~OperationPanel() override;

  void InitPanel();

  void Show();
  void Hide();
  void ChangePanelOpacity(float opacity);
  void SetBackgroundColor(int argb_color);
  bool IsActive();
  bool IsVisible();

  void Resize(const gfx::Rect& bounds);

  //views::View
  void Layout() override;
  void OnBoundsChanged(const gfx::Rect& previous_bounds) override;
  bool AcceleratorPressed(const ui::Accelerator& accelerator) override;

  //override from views::widgetDelegate
  //bool CanActivate() const override; can call widgetdelegate::set_can_active(true);
  bool ShouldShowWindowTitle() const override;
  bool ShouldShowCloseButton() const override;
  ui::ModalType GetModalType() const override;
  //virtual View* CreateOverlayView();

  //override from  widgetobserver
  void OnWidgetActivationChanged(views::Widget* widget, bool active) override;
  void OnWidgetVisibilityChanged(views::Widget* widget, bool visible) override;
private:
  views::Widget* parent_;
  views::Widget* widget_;

  BoomBarView* boom_bar_;
  views::View* uri_input_view_;
};

}
#endif
