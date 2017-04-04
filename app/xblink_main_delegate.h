#ifndef XBLINK_APP_MAIN_DELEGATE_H_
#define XBLINK_APP_MAIN_DELEGATE_H_

#include <memory>

#include "base/compiler_specific.h"
#include "base/macros.h"
#include "build/build_config.h"
#include "content/public/app/content_main_delegate.h"

namespace content {
class ContentClient;
class XBContentBrowserClient;
class XBContentRendererClient;
class XBContentUtilityClient;
}

namespace XB {

class XBMainDelegate : public content::ContentMainDelegate {
public:
  XBMainDelegate();
  ~XBMainDelegate() override;

  // ContentMainDelegate implementation:
  void PreSandboxStartup() override;
  bool BasicStartupComplete(int* exit_code) override;
  int RunProcess(const std::string& process_type,
                 const content::MainFunctionParams& main_function_params) override;

#if defined(OS_POSIX) && !defined(OS_ANDROID) && !defined(OS_MACOSX)
  void ZygoteForked() override;
#endif

  content::ContentBrowserClient* CreateContentBrowserClient() override;
  content::ContentRendererClient* CreateContentRendererClient() override;
  content::ContentUtilityClient* CreateContentUtilityClient() override;

  static void InitializeResourceBundle();

private:
  //std::unique_ptr<content::ContentClient> content_client_;
  /* XBTODO: enable follow late
  std::unique_ptr<XBContentUtilityClient> utility_client_;
  std::unique_ptr<XBContentBrowserClient> browser_client_;
  std::unique_ptr<XBContentRendererClient> renderer_client_;
  */

  DISALLOW_COPY_AND_ASSIGN(XBMainDelegate);
};

}  // namespace XB

#endif
