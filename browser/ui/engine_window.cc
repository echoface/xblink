#include "engine_window.h"
#include "ui/views/background.h"

#include "ui/views/widget/widget.h"


namespace XB {
EngineWindow::EngineWindow() : window_widget_(NULL) {

  child_view_ = new View();
  child_view_->set_background(views::Background::CreateSolidBackground(0xffff0090));
  AddChildView(child_view_);

  circle_button_ = new View();
  circle_button_->set_background(views::Background::CreateSolidBackground(0xff0000ff));
  AddChildView(circle_button_);

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
  set_background(views::Background::CreateSolidBackground(0xff90aa90));

  window_widget_->Show();

  timer_.Start(FROM_HERE, base::TimeDelta::FromSeconds(4), this, &EngineWindow::timer_shot);
//       timer_.Start(FROM_HERE, TimeDelta::FromSeconds(1),
//                    this, &MyClass::DoStuff);
//     }

}
void EngineWindow::timer_shot() {
  child_view_->SetVisible(!child_view_->visible());
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
  child_view_->SetBounds(0, 0, 300, bounds().height());
  circle_button_->SetBounds(20, 20, 32, 32);
}

void EngineWindow::Layout() {
  printf("\n\x1b[31m==%s %s <<%s>> [%d]====\x1b[0m", __FILE__, __FUNCTION__, "", 0);
  View::Layout();
}

} //end of namespace
