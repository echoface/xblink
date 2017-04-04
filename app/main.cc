#include "build/build_config.h"
#include "content/public/app/content_main.h"


#include "xblink_main_delegate.h"



int main(int argc, const char** argv) {

  XB::XBMainDelegate delegate;
  content::ContentMainParams params(&delegate);
  params.argc = argc;
  params.argv = argv;

  return content::ContentMain(params);
}
