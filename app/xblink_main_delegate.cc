
#include "xblink_main_delegate.h"
#include "content_client_xb.h"

#include "base/base_switches.h"
#include "base/command_line.h"
#include "base/cpu.h"
#include "base/files/file.h"
#include "base/files/file_path.h"
#include "base/lazy_instance.h"
#include "base/logging.h"
#include "base/path_service.h"
#include "build/build_config.h"
#include "cc/base/switches.h"
#include "content/common/content_constants_internal.h"
#include "content/public/browser/browser_main_runner.h"
#include "content/public/common/content_switches.h"
#include "content/public/common/url_constants.h"
#include "content/public/test/layouttest_support.h"
#include "content/public/test/ppapi_test_utils.h"
#include "gpu/config/gpu_switches.h"
#include "media/base/media_switches.h"
#include "media/base/mime_util.h"
#include "net/cookies/cookie_monster.h"
#include "ppapi/features/features.h"
#include "ui/base/resource/resource_bundle.h"
#include "ui/base/ui_base_paths.h"
#include "ui/base/ui_base_switches.h"
#include "ui/display/display_switches.h"
#include "ui/gl/gl_implementation.h"
#include "ui/gl/gl_switches.h"

#include "ipc/ipc_message.h"  // For IPC_MESSAGE_LOG_ENABLED.

#include "components/crash/content/app/breakpad_linux.h"
/*
#include "content/shell/app/shell_crash_reporter_client.h"
#include "content/shell/browser/shell_browser_main.h"
#include "content/shell/browser/shell_content_browser_client.h"
#include "content/shell/common/shell_content_client.h"
#include "content/shell/common/shell_switches.h"
#include "content/shell/renderer/shell_content_renderer_client.h"
#include "content/shell/utility/shell_content_utility_client.h"
*/
#include "../browser/content_browser_client_xb.h"

namespace XB {
/*
base::LazyInstance<content::ShellCrashReporterClient>::Leaky
    g_shell_crash_client = LAZY_INSTANCE_INITIALIZER;
    */

XBMainDelegate::XBMainDelegate() {
}
XBMainDelegate::~XBMainDelegate() {
}

  // ContentMainDelegate implementation:
void XBMainDelegate::PreSandboxStartup() {
  /*
  if (base::CommandLine::ForCurrentProcess()->HasSwitch(switches::kEnableCrashReporter)) {
    std::string process_type =
        base::CommandLine::ForCurrentProcess()->GetSwitchValueASCII(switches::kProcessType);
    crash_reporter::SetCrashReporterClient(g_shell_crash_client.Pointer());
  }*/

  InitializeResourceBundle();
}

bool XBMainDelegate::BasicStartupComplete(int* exit_code) {
  //base::CommandLine& command_line = *base::CommandLine::ForCurrentProcess();
  int dummy;
  if (!exit_code)
    exit_code = &dummy;

  //XBTODO:enable late
  //InitLogging();

  content_client_.reset(new XBContentClient());
  SetContentClient(content_client_.get());

  return false;
}

int XBMainDelegate::RunProcess(const std::string& process_type,
                               const content::MainFunctionParams& main_function_params) {
  if (!process_type.empty())
    return -1;

  base::trace_event::TraceLog::GetInstance()->SetProcessName("Browser");
  base::trace_event::TraceLog::GetInstance()->SetProcessSortIndex(content::kTraceEventBrowserProcessSortIndex);

  //base::CommandLine& command_line = *base::CommandLine::ForCurrentProcess();

  std::unique_ptr<content::BrowserMainRunner> browser_runner_;
  browser_runner_.reset(content::BrowserMainRunner::Create());

  //XBTODO: later create this
  //return ShellBrowserMain(main_function_params, browser_runner_);
  return -1;
}

#if defined(OS_POSIX) && !defined(OS_ANDROID) && !defined(OS_MACOSX)
void XBMainDelegate::ZygoteForked() {
  //XBTODO: we not need it
  if (base::CommandLine::ForCurrentProcess()->HasSwitch(switches::kEnableCrashReporter)) {
    std::string process_type =
      base::CommandLine::ForCurrentProcess()->GetSwitchValueASCII(switches::kProcessType);
    breakpad::InitCrashReporter(process_type);
  }
}
#endif

content::ContentBrowserClient* XBMainDelegate::CreateContentBrowserClient() {
  return new ContentBrowserClientXb();
}

content::ContentRendererClient* XBMainDelegate::CreateContentRendererClient() {
  return NULL;
}

content::ContentUtilityClient* XBMainDelegate::CreateContentUtilityClient() {
  return NULL;
}

void XBMainDelegate::InitializeResourceBundle() {
  base::FilePath pak_file;
  bool r = PathService::Get(base::DIR_MODULE, &pak_file);
  DCHECK(r);
  pak_file = pak_file.Append(FILE_PATH_LITERAL("content_shell.pak"));
  ui::ResourceBundle::InitSharedInstanceWithPakPath(pak_file);
}

}//namespace XB end
