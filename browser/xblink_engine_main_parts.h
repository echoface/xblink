#ifndef XBLINK_ENGINE_MAIN_PARTS_H
#define XBLINK_ENGINE_MAIN_PARTS_H

#include <memory>

#include "base/macros.h"
#include "build/build_config.h"
#include "content/public/browser/browser_main_parts.h"
#include "content/public/common/main_function_params.h"
#include "content/public/browser/browser_context.h"
//#include "content/shell/browser/shell_browser_context.h"

namespace XB {

class XblinkEngineMainParts : public content::BrowserMainParts {
public:
  explicit XblinkEngineMainParts(const content::MainFunctionParams& parameters);
  ~XblinkEngineMainParts() override;

  static XblinkEngineMainParts* Get();
  // BrowserMainParts overrides.
  void PreEarlyInitialization() override;
#if defined(OS_ANDROID)
  int PreCreateThreads() override;
#endif
  void PreMainMessageLoopStart() override;
  void PostMainMessageLoopStart() override;
  void PreMainMessageLoopRun() override;
  bool MainMessageLoopRun(int* result_code) override;
  void PostMainMessageLoopRun() override;
  void PostDestroyThreads() override;

  content::BrowserContext* browser_context() { return browser_context_.get(); }

  //net::NetLog* net_log() { return net_log_.get(); }

protected:
  virtual void InitializeBrowserContexts();
  virtual void InitializeMessageLoopContext();

private:
  //std::unique_ptr<net::NetLog> net_log_;
  std::unique_ptr<content::BrowserContext> browser_context_;

  //For running content_browsertests.
  const content::MainFunctionParams parameters_;
  bool run_message_loop_;

  DISALLOW_COPY_AND_ASSIGN(XblinkEngineMainParts);
};

}

#endif
