#include "engine_window.h"
#include "ui/views/background.h"

#include "ui/views/widget/widget.h"
#include "ui/views/controls/webview/webview.h"
#include "ui/events/platform/platform_event_source.h"

#include "Xblink/app/xblink_main_delegate.h"
#include "Xblink/browser/xblink_engine_main_parts.h"

#include "Xblink/views/operation_panel/operation_panel.h"

#include <X11/extensions/shape.h>
#include <X11/extensions/XInput2.h>
#include <X11/Xatom.h>
#include <X11/Xregion.h>
#include <X11/Xutil.h>


namespace XB {
EngineWindow::EngineWindow() : window_widget_(NULL) {
  operation_panel_ = NULL;

  /*
  overlay_view_ = new View();
  overlay_view_->set_background(views::Background::CreateSolidBackground(0x5500FF90));
  */

  content::BrowserContext* browser_context = XblinkEngineMainParts::Get()->browser_context();
  web_view_ = new views::WebView(browser_context);
  AddChildView(web_view_);
  /*
  child_view_ = new View();
  child_view_->set_background(views::Background::CreateSolidBackground(0xffff0090));
  AddChildView(child_view_);

  circle_button_ = new View();
  circle_button_->set_background(views::Background::CreateSolidBackground(0xff0000ff));
  AddChildView(circle_button_);

  */

  window_widget_ = new views::Widget;
  views::Widget::InitParams params;
  params.bounds = gfx::Rect(0, 0, 800, 600);

  params.delegate = this;
  params.wm_class_class = "EngineWindow";
  params.wm_class_name = params.wm_class_class;
  window_widget_->Init(params);

  window_widget_->Show();
  //InitAccelerators();

  timer_.Start(FROM_HERE, base::TimeDelta::FromSeconds(4), this, &EngineWindow::timer_shot);

  GURL url("http://www.wiki.org");
  web_view_->LoadInitialURL(url);

  operation_panel_ = new OperationPanel(window_widget_);
  operation_panel_->InitPanel();

  if (ui::PlatformEventSource::GetInstance()) {
    printf("\n\x1b[31m==%s %s <<%s>> [%d]====\x1b[0m", __FILE__, __FUNCTION__, "add event thing", 0);
    ui::PlatformEventSource::GetInstance()->AddPlatformEventObserver(this);
  }
}

void EngineWindow::timer_shot() {
  //child_view_->SetVisible(!child_view_->visible());
}

EngineWindow::~EngineWindow() {
  window_widget_ = NULL;
}

void EngineWindow::InitAccelerators() {
  const ui::KeyboardCode keys[] = { ui::VKEY_F5,
                                    ui::VKEY_W,
                                    ui::VKEY_A,
                                    ui::VKEY_S,
                                    ui::VKEY_D};

  for (size_t i = 0; i < arraysize(keys); ++i) {
    GetFocusManager()->RegisterAccelerator(ui::Accelerator(keys[i], ui::EF_NONE),
                                           ui::AcceleratorManager::kNormalPriority,
                                           this);
  }
}
bool EngineWindow::AcceleratorPressed(const ui::Accelerator& accelerator) {
  switch (accelerator.key_code()) {
  case ui::VKEY_F5:
    if (operation_panel_)
      operation_panel_->IsVisible() ? operation_panel_->Hide() : operation_panel_->Show();
    return true;
  case ui::VKEY_W:
    return true;
  case ui::VKEY_A:
    return true;
  case ui::VKEY_S:
    return true;
  case ui::VKEY_D:
    return true;
  default:
    return views::WidgetDelegateView::AcceleratorPressed(accelerator);
  }
}

  // WidgetDelegate:
void EngineWindow::DeleteDelegate() {
  delete this;
}
views::Widget* EngineWindow::GetWidget() {
  return window_widget_;
}
const views::Widget* EngineWindow::GetWidget() const {
  return window_widget_;
}
views::View* EngineWindow::GetContentsView() {
  return this;
}
// View:
const char* EngineWindow::GetClassName() const {
  return "EngineWindow";
}

void EngineWindow::OnBoundsChanged(const gfx::Rect& previous_bounds) {
  web_view_->SetBoundsRect(bounds());
  /*
  child_view_->SetBounds(0, 0, 300, bounds().height());

  //circle_button_->SetSize(gfx::Size(32, 32));
  gfx::Point p = bounds().bottom_right();
  p.Offset(-64,-64);
  gfx::Rect rect(32, 32);
  rect.set_origin(p);
  circle_button_->SetBoundsRect(rect);
  */
  if (operation_panel_)
    operation_panel_->Resize(bounds());
}

void EngineWindow::Layout() {
  View::Layout();
}

views::View* EngineWindow::CreateOverlayView() {
  return NULL;//return overlay_view_;
}
void EngineWindow::WillProcessEvent(const ui::PlatformEvent& event) {
  XEvent* xev = event;
  if (xev->type == KeyPress || xev->type == KeyRelease) {
    ui::KeyEvent keyevent(xev);
    if (keyevent.key_code() == ui::VKEY_F5 && keyevent.type() == ui::ET_KEY_PRESSED) {
      if (operation_panel_->IsVisible())
        operation_panel_->Hide();
      else
        operation_panel_->Show();
    }
  }
}

void EngineWindow::DidProcessEvent(const ui::PlatformEvent& event) {
}

} //end of namespace
