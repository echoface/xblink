#include "xblink_engine_main_parts.h"
#include "xblink_engine_context.h"

#include "device/bluetooth/bluetooth_adapter_factory.h"
#include "device/geolocation/geolocation_delegate.h"
#include "device/geolocation/geolocation_provider.h"

#if defined(OS_LINUX)
#include "device/bluetooth/dbus/dbus_bluez_manager_wrapper_linux.h"
#endif

#if defined(USE_AURA) && defined(USE_X11)
#include "ui/events/devices/x11/touch_factory_x11.h"  // nogncheck
#endif

#include "ui/engine_window.h"
#include "ui/display/screen.h"

#include "ui/views/test/desktop_test_views_delegate.h"
#include "ui/views/widget/desktop_aura/desktop_screen.h"
#include "ui/base/ime/input_method_initializer.h"

#if defined(USE_AURA)
#include "ui/wm/core/wm_state.h"
#endif
namespace XB {

static XblinkEngineMainParts* g_main_parts = NULL;

XblinkEngineMainParts* XblinkEngineMainParts::Get() {
  return g_main_parts;
}
XblinkEngineMainParts::XblinkEngineMainParts(const content::MainFunctionParams& parameters)
  : parameters_(parameters),
    run_message_loop_(true) {
  printf("\n\x1b[31m==%s %s <<%s>> [%d]====\x1b[0m", __FILE__, __FUNCTION__, "", 0);
  g_main_parts = this;
}

XblinkEngineMainParts::~XblinkEngineMainParts() {
}

void XblinkEngineMainParts::PreEarlyInitialization() {
  printf("\n\x1b[31m==%s %s <<%s>> [%d]====\x1b[0m", __FILE__, __FUNCTION__, "", 0);
  //this is very important, without this will crash
  ui::InitializeInputMethodForTesting();
}

#if defined(OS_ANDROID)
int XblinkEngineMainParts::PreCreateThreads() {
  return 1;
}
#endif

void XblinkEngineMainParts::PreMainMessageLoopStart() {
#if defined(USE_AURA) && defined(USE_X11)
  ui::TouchFactory::SetTouchDeviceListFromCommandLine();
#endif
  printf("\n\x1b[31m==%s %s <<%s>> [%d]====\x1b[0m", __FILE__, __FUNCTION__, "", 0);
}

void XblinkEngineMainParts::PostMainMessageLoopStart() {
  printf("\n\x1b[31m==%s %s <<%s>> [%d]====\x1b[0m", __FILE__, __FUNCTION__, "", 0);
#if defined(OS_LINUX)
  bluez::DBusBluezManagerWrapperLinux::Initialize();
#endif
}

void XblinkEngineMainParts::PreMainMessageLoopRun() {
  printf("\n\x1b[31m==%s %s <<%s>> [%d]====\x1b[0m", __FILE__, __FUNCTION__, "", 0);
  //net_log_.reset(new ShellNetLog("content_shell"));
  InitializeBrowserContexts();

#if defined(USE_AURA)
  new wm::WMState;
#endif
  display::Screen::SetScreenInstance(views::CreateDesktopScreen());
  new views::DesktopTestViewsDelegate();

  new EngineWindow();
  //new EngineWindow
  //device::GeolocationProvider::SetGeolocationDelegate(new ShellGeolocationDelegate(browser_context()));
  //Shell::Initialize();
  //net::NetModule::SetResourceProvider(PlatformResourceProvider);
  //ShellDevToolsManagerDelegate::StartHttpHandler(browser_context_.get());
  InitializeMessageLoopContext();

  if (parameters_.ui_task) {
    parameters_.ui_task->Run();
    delete parameters_.ui_task;
    run_message_loop_ = false;
  }
}

bool XblinkEngineMainParts::MainMessageLoopRun(int* result_code) {
  printf("\n\x1b[31m==%s %s <<%s>> [%d]====\x1b[0m", __FILE__, __FUNCTION__, "", 0);
  return !run_message_loop_;
}

void XblinkEngineMainParts::PostMainMessageLoopRun() {
  //ShellDevToolsManagerDelegate::StopHttpHandler();
  browser_context_.reset();
  printf("\n\x1b[31m==%s %s <<%s>> [%d]====\x1b[0m", __FILE__, __FUNCTION__, "", 0);
}

void XblinkEngineMainParts::PostDestroyThreads() {
  printf("\n\x1b[31m==%s %s <<%s>> [%d]====\x1b[0m", __FILE__, __FUNCTION__, "", 0);
#if defined(OS_LINUX)
  device::BluetoothAdapterFactory::Shutdown();
  bluez::DBusBluezManagerWrapperLinux::Shutdown();
#endif
}

void XblinkEngineMainParts::InitializeBrowserContexts() {
  printf("\n\x1b[31m==%s %s <<%s>> [%d]====\x1b[0m", __FILE__, __FUNCTION__, "", 0);
  browser_context_.reset(new XblinkEngineContext(false, NULL/*net_log_.get()*/));
}

void XblinkEngineMainParts::InitializeMessageLoopContext() {
  printf("\n\x1b[31m==%s %s <<%s>> [%d]====\x1b[0m", __FILE__, __FUNCTION__, "", 0);
}

}
