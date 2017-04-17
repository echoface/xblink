#include "engine_window.h"
#include "ui/views/background.h"

#include "ui/views/widget/widget.h"
#include "ui/views/controls/webview/webview.h"

#include "Xblink/app/xblink_main_delegate.h"
#include "Xblink/browser/xblink_engine_main_parts.h"


namespace XB {
EngineWindow::EngineWindow() : window_widget_(NULL) {

  content::BrowserContext* browser_context = XblinkEngineMainParts::Get()->browser_context();
  web_view_ = new views::WebView(browser_context);
  AddChildView(web_view_);

  child_view_ = new View();
  child_view_->set_background(views::Background::CreateSolidBackground(0xffff0090));
  AddChildView(child_view_);

  circle_button_ = new View();
  circle_button_->set_background(views::Background::CreateSolidBackground(0xff0000ff));
  AddChildView(circle_button_);

  boom_bar_ = new BoomBarView();
  AddChildView(boom_bar_);

  uri_input_view_ = new View();
  uri_input_view_->set_background(views::Background::CreateSolidBackground(0xAAff4c00));
  AddChildView(uri_input_view_);

  window_widget_ = new views::Widget;
  views::Widget::InitParams params;
  params.bounds = gfx::Rect(0, 0, 800, 600);

  params.delegate = this;
  params.wm_class_class = "EngineWindow";
  params.wm_class_name = params.wm_class_class;
  window_widget_->Init(params);

  //window_ = window_widget_->GetNativeWindow();
  // Call ShowRootWindow on RootWindow created by WMTestHelper without
  // which XWindow owned by RootWindow doesn't get mapped.
  //window_->GetHost()->Show();
  set_background(views::Background::CreateSolidBackground(0xFFe0eee8));

  window_widget_->Show();

  timer_.Start(FROM_HERE, base::TimeDelta::FromSeconds(4), this, &EngineWindow::timer_shot);
//       timer_.Start(FROM_HERE, TimeDelta::FromSeconds(1),
//                    this, &MyClass::DoStuff);
//     }

  GURL url("http://www.apple.com/");
  web_view_->LoadInitialURL(url);
}
void EngineWindow::timer_shot() {
  child_view_->SetVisible(!child_view_->visible());
  web_view_->SetVisible(!child_view_->visible());
  //boom_bar_->SetVisible(!boom_bar_->visible());
}

EngineWindow::~EngineWindow() {
  window_widget_ = NULL;
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
  printf("\n\x1b[31m==%s %s <<%s>> [%d]====\x1b[0m", __FILE__, __FUNCTION__, "", 0);
  web_view_->SetBoundsRect(bounds());

  child_view_->SetBounds(0, 0, 300, bounds().height());

  //circle_button_->SetSize(gfx::Size(32, 32));
  gfx::Point p = bounds().bottom_right();
  p.Offset(-64,-64);
  gfx::Rect rect(32, 32);
  rect.set_origin(p);
  circle_button_->SetBoundsRect(rect);
  boom_bar_->SetBounds(bounds().width()/2 - bounds().width()/4, bounds().height()/2 - 128, bounds().width()/2, 96);
  uri_input_view_->SetBounds(0, 0, width(), 32);
}

void EngineWindow::Layout() {
  printf("\n\x1b[31m==%s %s <<%s>> [%d]====\x1b[0m", __FILE__, __FUNCTION__, "", 0);
  View::Layout();
}

} //end of namespace
