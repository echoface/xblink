
#include "boom_bar_view.h"
#include "ui/views/controls/label.h"
#include "ui/views/background.h"
#include "ui/views/border.h"
#include "base/strings/utf_string_conversions.h"
#include "ui/views/controls/focus_ring.h"

const int KBlurColor = 0xDDf6f5ec;

const int KFocusColor = 0xDDFF4500;

const int kBackgroundColor = KBlurColor;

namespace XB {

TLabel::TLabel(base::string16 label) :
  views::Label(label) {
}
TLabel::~TLabel() {
}

void TLabel::OnBlur() {
  set_background(views::Background::CreateSolidBackground(KBlurColor));
  views::Label::OnBlur();
  SchedulePaint();
}
void TLabel::OnFocus() {
  set_background(views::Background::CreateSolidBackground(KFocusColor));
  views::Label::OnFocus();
  SchedulePaint();
}

BoomBarView::BoomBarView() {
  set_background(views::Background::CreateSolidBackground(kBackgroundColor));
  //SetBorder(views::CreateRoundedRectBorder(6, 3, kBackgroundColor));

  home_ = new TLabel(base::UTF8ToUTF16("Home Page"));
  //home_->set_background(views::Background::CreateSolidBackground(kBackgroundColor));
  pages_view_ = new TLabel(base::UTF8ToUTF16("Pages"));
  //pages_view_->set_background(views::Background::CreateSolidBackground(kBackgroundColor));
  uri_input_ = new TLabel(base::UTF8ToUTF16("Go URL"));
  uri_input_->set_background(views::Background::CreateSolidBackground(KFocusColor));
  page_action_ = new TLabel(base::UTF8ToUTF16("Action"));
  //page_action_->set_background(views::Background::CreateSolidBackground(kBackgroundColor));
  settings_ = new TLabel(base::UTF8ToUTF16("Settings"));
  //settings_->set_background(views::Background::CreateSolidBackground(kBackgroundColor));
  //views::FocusRing::Install(settings_);
  AddChildView(home_);
  AddChildView(pages_view_);
  AddChildView(uri_input_);
  AddChildView(page_action_);
  AddChildView(settings_);
  SetFocusBehavior(views::View::FocusBehavior::ALWAYS);
}

BoomBarView::~BoomBarView() {
}

void BoomBarView::OnBlur() {
  SetBorder(views::CreateEmptyBorder(gfx::Insets(2)));
  views::View::OnFocus();
  SchedulePaint();
}
void BoomBarView::OnFocus() {
  SetBorder(views::CreateRoundedRectBorder(6, 3, KFocusColor));
  views::View::OnBlur();
  SchedulePaint();
}
bool BoomBarView::OnKeyPressed(const ui::KeyEvent& event) {;
  //if (event.key_code() == ui::VKEY_LEFT)
  printf("\n\x1b[31m==%s %s <<%s>> [%d]====\x1b[0m", __FILE__, __FUNCTION__, "", 0);
  return views::View::OnKeyPressed(event);
}
bool BoomBarView::OnKeyReleased(const ui::KeyEvent& event) {
  printf("\n\x1b[31m==%s %s <<%s>> [%d]====\x1b[0m", __FILE__, __FUNCTION__, "", 0);
  return views::View::OnKeyReleased(event);
}
void BoomBarView::Layout() {
  views::View::Layout();
}

void BoomBarView::OnBoundsChanged(const gfx::Rect& previous_bounds) {
  int design_size = height() - 40;

  int off_set = (width() - child_count()*design_size) / (child_count() + 1);

  int w_and_off = design_size + off_set;//(width()-off_set) / child_count();
  int av_width = design_size;
  int pos_y = 20;

  home_->SetBounds(off_set, pos_y, av_width, av_width);
  pages_view_->SetBounds(off_set+w_and_off, pos_y, av_width, av_width);
  uri_input_->SetBounds(off_set+2*w_and_off, pos_y, av_width, av_width);
  page_action_->SetBounds(off_set+3*w_and_off, pos_y, av_width, av_width);
  settings_->SetBounds(off_set+4*w_and_off, pos_y, av_width, av_width);
  views::View::OnBoundsChanged(previous_bounds);
}

}//end namespace
