
#include "boom_bar_view.h"
#include "ui/views/background.h"
#include "ui/views/border.h"

namespace XB {

BoomBarView::BoomBarView() {
  //set_background(views::Background::CreateSolidBackground(0xff0000ee));
  SetBorder(views::CreateRoundedRectBorder(6, 4, 0xEEFF4500));
  home_ = new views::View();
  home_->set_background(views::Background::CreateSolidBackground(0xEEFF4500));

  pages_view_ = new views::View();
  pages_view_->set_background(views::Background::CreateSolidBackground(0xEEFF4500));
  uri_input_ = new views::View();
  uri_input_->set_background(views::Background::CreateSolidBackground(0xEEFF4500));
  page_action_ = new views::View();
  page_action_->set_background(views::Background::CreateSolidBackground(0xEEFF4500));
  settings_ = new views::View();
  settings_->set_background(views::Background::CreateSolidBackground(0xEEFF4500));
  AddChildView(home_);
  AddChildView(pages_view_);
  AddChildView(uri_input_);
  AddChildView(page_action_);
  AddChildView(settings_);
}

BoomBarView::~BoomBarView() {
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
