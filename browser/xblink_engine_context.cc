
#include "xblink_engine_context.h"

#include <utility>
#include "base/bind.h"
#include "base/command_line.h"
#include "base/environment.h"
#include "base/files/file_util.h"
#include "base/logging.h"
#include "base/path_service.h"
#include "base/threading/thread.h"
#include "build/build_config.h"
#include "content/public/browser/browser_thread.h"
#include "content/public/browser/storage_partition.h"
#include "content/public/common/content_switches.h"
#include "content/public/browser/background_sync_controller.h"
#include "content/public/browser/background_sync_parameters.h"

#include "components/keyed_service/content/browser_context_dependency_manager.h"
#include "content/shell/browser/shell_download_manager_delegate.h"
#include "content/shell/browser/shell_permission_manager.h"
#include "content/shell/common/shell_switches.h"

#if defined(OS_WIN)
#include "base/base_paths_win.h"
#elif defined(OS_LINUX)
#include "base/nix/xdg_util.h"
#elif defined(OS_MACOSX)
#include "base/base_paths_mac.h"
#endif

namespace XB {
  // Contains URLRequestContextGetter required for resource loading.
XblinkEngineContext::XbResourceContext::XbResourceContext() :
  getter_(NULL) {
}
XblinkEngineContext::XbResourceContext::~XbResourceContext() {
}

  // ResourceContext implementation:
net::HostResolver* XblinkEngineContext::XbResourceContext::GetHostResolver() {
  CHECK(getter_);
  return getter_->host_resolver();
}
net::URLRequestContext* XblinkEngineContext::XbResourceContext::GetRequestContext() {
  return getter_->GetURLRequestContext();
}


XblinkEngineContext::XblinkEngineContext(bool off_the_record, net::NetLog* net_log)
  : resource_context_(new XbResourceContext()),
    off_the_record_(off_the_record),
    net_log_(net_log) {

  InitWhileIOAllowed();
  BrowserContextDependencyManager::GetInstance()->
      CreateBrowserContextServices(this);
}

XblinkEngineContext::~XblinkEngineContext() {
  BrowserContextDependencyManager::GetInstance()->
      DestroyBrowserContextServices(this);
  // Need to destruct the ResourceContext before posting tasks which may delete
  // the URLRequestContext because ResourceContext's destructor will remove any
  // outstanding request while URLRequestContext's destructor ensures that there
  // are no more outstanding requests.
  if (resource_context_) {
    content::BrowserThread::DeleteSoon(content::BrowserThread::IO, FROM_HERE, resource_context_.release());
  }
  ShutdownStoragePartitions();
}

base::FilePath XblinkEngineContext::GetPath() const {
  return path_;
}

// BrowserContext implementation.
std::unique_ptr<content::ZoomLevelDelegate>
  XblinkEngineContext::CreateZoomLevelDelegate(const base::FilePath& partition_path) {
  return std::unique_ptr<content::ZoomLevelDelegate>();
}

bool XblinkEngineContext::IsOffTheRecord() const {
  return off_the_record_;
}

content::DownloadManagerDelegate* XblinkEngineContext::GetDownloadManagerDelegate() {
  if (!download_manager_delegate_.get()) {
    download_manager_delegate_.reset(new content::ShellDownloadManagerDelegate());
    download_manager_delegate_->SetDownloadManager(content::BrowserContext::GetDownloadManager(this));
  }

  return download_manager_delegate_.get();
}
content::ResourceContext* XblinkEngineContext::GetResourceContext() {
  return resource_context_.get();
}
content::BrowserPluginGuestManager* XblinkEngineContext::GetGuestManager() {
  return NULL;
}

storage::SpecialStoragePolicy* XblinkEngineContext::GetSpecialStoragePolicy() {
  return NULL;
}
content::PushMessagingService* XblinkEngineContext::GetPushMessagingService() {
  return NULL;
}
content::SSLHostStateDelegate* XblinkEngineContext::GetSSLHostStateDelegate() {
  return NULL;
}
content::PermissionManager* XblinkEngineContext::GetPermissionManager() {
  if (!permission_manager_.get())
    permission_manager_.reset(new content::ShellPermissionManager());
  return permission_manager_.get();
}
content::BackgroundSyncController* XblinkEngineContext::GetBackgroundSyncController()  {
  return nullptr;
}
net::URLRequestContextGetter* XblinkEngineContext::CreateRequestContext(content::ProtocolHandlerMap* protocol_handlers,
  content::URLRequestInterceptorScopedVector request_interceptors)  {

  DCHECK(!url_request_getter_.get());
  url_request_getter_ = CreateURLRequestContextGetter(protocol_handlers, std::move(request_interceptors));
  resource_context_->set_url_request_context_getter(url_request_getter_.get());

  return url_request_getter_.get();
}

net::URLRequestContextGetter* XblinkEngineContext::CreateRequestContextForStoragePartition(
    const base::FilePath& partition_path,
    bool in_memory,
    content::ProtocolHandlerMap* protocol_handlers,
    content::URLRequestInterceptorScopedVector request_interceptors)  {
  return nullptr;
}

net::URLRequestContextGetter* XblinkEngineContext::CreateMediaRequestContext() {
  DCHECK(url_request_getter_.get());
  return url_request_getter_.get();
}

net::URLRequestContextGetter* XblinkEngineContext::CreateMediaRequestContextForStoragePartition(
    const base::FilePath& partition_path, bool in_memory) {
  return nullptr;
}

content::ShellURLRequestContextGetter* XblinkEngineContext::CreateURLRequestContextGetter(
    content::ProtocolHandlerMap* protocol_handlers,
    content::URLRequestInterceptorScopedVector request_interceptors) {

  return new content::ShellURLRequestContextGetter(true, GetPath(),
                content::BrowserThread::GetTaskRunnerForThread(content::BrowserThread::IO),
                content::BrowserThread::GetTaskRunnerForThread(content::BrowserThread::FILE),
                protocol_handlers, std::move(request_interceptors), net_log_);
}

// Performs initialization of the ShellBrowserContext while IO is still
// allowed on the current thread.
void XblinkEngineContext::InitWhileIOAllowed() {
  //base::CommandLine* cmd_line = base::CommandLine::ForCurrentProcess();

#if defined(OS_LINUX)
  std::unique_ptr<base::Environment> env(base::Environment::Create());
  base::FilePath config_dir(base::nix::GetXDGDirectory(env.get(),
                            base::nix::kXdgConfigHomeEnvVar,
                            base::nix::kDotConfigDir));

  path_ = config_dir.Append("Xblink");
#elif defined(OS_MACOSX)
  CHECK(PathService::Get(base::DIR_APP_DATA, &path_));
  path_ = path_.Append("Xblink");
#elif defined(OS_ANDROID)
  CHECK(PathService::Get(base::DIR_ANDROID_APP_DATA, &path_));
  path_ = path_.Append(FILE_PATH_LITERAL("Xblink"));
#else
  NOTIMPLEMENTED();
#endif

  if (!base::PathExists(path_))
    base::CreateDirectory(path_);

  BrowserContext::Initialize(this, path_);
}


}
