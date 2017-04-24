#include "operation_panel.h"

#include "ui/views/background.h"
#include "ui/views/controls/textfield/textfield.h"
#include "ui/views/layout/fill_layout.h"
#include "ui/views/layout/box_layout.h"

namespace XB {

OperationPanel::OperationPanel(views::Widget* parent)
  : parent_(parent),
    widget_(NULL) {
  set_background(views::Background::CreateSolidBackground(0x33130c0e));
  SetFocusBehavior(views::View::FocusBehavior::NEVER);
}

//call by widgetdelegate::deletedelegate interface
OperationPanel::~OperationPanel() {
}

void OperationPanel::InitPanel() {
  if (widget_)
    return;

  boom_bar_ = new BoomBarView();
  AddChildView(boom_bar_);

  uri_input_view_ = new View();
  uri_input_view_->set_background(views::Background::CreateSolidBackground(0xDDF15A22));
  AddChildView(uri_input_view_);

  views::Textfield* textfield = new views::Textfield();
  textfield->SetBounds(5, 5, 800, 42);
  views::BoxLayout* layout = new views::BoxLayout(views::BoxLayout::Orientation::kHorizontal, 5, 5, 10);
  layout->set_inside_border_insets(gfx::Insets(5));
  uri_input_view_->SetLayoutManager(layout);
  uri_input_view_->AddChildView(textfield);
  uri_input_view_->SetVisible(false);

  views::Widget::InitParams params(views::Widget::InitParams::TYPE_WINDOW_FRAMELESS);
  params.opacity = views::Widget::InitParams::TRANSLUCENT_WINDOW;
  params.remove_standard_frame = true;
  params.bounds = gfx::Rect(0, 0, 800, 600);
  params.parent = parent_->GetNativeView();
  params.delegate = this;

  widget_ = new views::Widget();
  widget_->AddObserver(this);
  widget_->Init(params);
/*
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
  */
  widget_->Show();
}

void OperationPanel::Show() {
  if (widget_)
    widget_->Show();
}
void OperationPanel::Hide() {
  if (widget_)
    widget_->Hide();
}

bool OperationPanel::AcceleratorPressed(const ui::Accelerator& accelerator) {
  switch (accelerator.key_code()) {
  case ui::VKEY_F5:
    IsDrawn() ? Hide() : Show();
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

void OperationPanel::Layout() {
  WidgetDelegateView::Layout();
}

void OperationPanel::OnBoundsChanged(const gfx::Rect& previous_bounds) {
  boom_bar_->SetBounds(bounds().width()/2 - bounds().width()/4, bounds().height()/2 - 128, bounds().width()/2, 96);
  uri_input_view_->SetBounds(0, 0, width(), 48);
}

void OperationPanel::Resize(const gfx::Rect& bounds) {
  widget_->CenterWindow(bounds.size());
}

void OperationPanel::ChangePanelOpacity(float opacity) {
  if (widget_)
    widget_->SetOpacity(opacity);
}

void OperationPanel::SetBackgroundColor(int argb_color) {
  set_background(views::Background::CreateSolidBackground(argb_color));
}

bool OperationPanel::IsActive() {
  return widget_ ? widget_->IsActive() : false;
}
bool OperationPanel::IsVisible() {
  return widget_ ? widget_->IsVisible() : false;
}
//override from views::widgetDelegate
ui::ModalType OperationPanel::GetModalType() const {
  return ui::MODAL_TYPE_CHILD;
}
bool OperationPanel::ShouldShowWindowTitle() const {
  return false;
}
bool OperationPanel::ShouldShowCloseButton() const {;
  return false;
}

void OperationPanel::OnWidgetVisibilityChanged(views::Widget* widget, bool visible) {
  if (widget == widget_ && visible) {
    boom_bar_->RequestFocus();
  }
}
void OperationPanel::OnWidgetActivationChanged(views::Widget* widget, bool active) {
}

}//end namespace
