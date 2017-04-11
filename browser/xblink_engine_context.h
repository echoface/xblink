#ifndef XBLINK_ENGINE_CONTEXT_H
#define XBLINK_ENGINE_CONTEXT_H

#include <memory>

#include "base/compiler_specific.h"
#include "base/files/file_path.h"
#include "base/macros.h"
#include "base/memory/ref_counted.h"
#include "content/public/browser/browser_context.h"
#include "content/public/browser/content_browser_client.h"
#include "content/public/browser/resource_context.h"

#include "net/url_request/url_request_job_factory.h"

//XB TODO: replace by xb self
#include "content/shell/browser/shell_url_request_context_getter.h"

namespace content {
class BackgroundSyncController;
class DownloadManagerDelegate;
class PermissionManager;
class ShellDownloadManagerDelegate;
class ZoomLevelDelegate;
class ShellURLRequestContextGetter;
}

namespace XB {

class XblinkEngineContext : public content::BrowserContext {
public:
  XblinkEngineContext(bool off_the_record, net::NetLog* net_log);
  ~XblinkEngineContext() override;

  // BrowserContext implementation.
  base::FilePath GetPath() const override;
  std::unique_ptr<content::ZoomLevelDelegate> CreateZoomLevelDelegate(
      const base::FilePath& partition_path) override;

  bool IsOffTheRecord() const override;
  content::DownloadManagerDelegate* GetDownloadManagerDelegate() override;
  content::ResourceContext* GetResourceContext() override;
  content::BrowserPluginGuestManager* GetGuestManager() override;

  storage::SpecialStoragePolicy* GetSpecialStoragePolicy() override;
  content::PushMessagingService* GetPushMessagingService() override;
  content::SSLHostStateDelegate* GetSSLHostStateDelegate() override;
  content::PermissionManager* GetPermissionManager() override;
  content::BackgroundSyncController* GetBackgroundSyncController() override;
  net::URLRequestContextGetter* CreateRequestContext(content::ProtocolHandlerMap* protocol_handlers,
                                                     content::URLRequestInterceptorScopedVector request_interceptors) override;
  net::URLRequestContextGetter* CreateRequestContextForStoragePartition(
      const base::FilePath& partition_path,
      bool in_memory,
      content::ProtocolHandlerMap* protocol_handlers,
      content::URLRequestInterceptorScopedVector request_interceptors) override;

  net::URLRequestContextGetter* CreateMediaRequestContext() override;
  net::URLRequestContextGetter* CreateMediaRequestContextForStoragePartition(
      const base::FilePath& partition_path,
      bool in_memory) override;

 protected:
  // Contains URLRequestContextGetter required for resource loading.
  class XbResourceContext : public content::ResourceContext {
   public:
    XbResourceContext();
    ~XbResourceContext() override;

    // ResourceContext implementation:
    net::HostResolver* GetHostResolver() override;
    net::URLRequestContext* GetRequestContext() override;

    void set_url_request_context_getter(content::ShellURLRequestContextGetter* getter) {
      getter_ = getter;
    }

  private:
    content::ShellURLRequestContextGetter* getter_;

    DISALLOW_COPY_AND_ASSIGN(XbResourceContext);
  };

  content::ShellURLRequestContextGetter* url_request_context_getter() {
    return url_request_getter_.get();
  }

  // Used by ShellBrowserContext to initiate and set different types of
  // URLRequestContextGetter.
  virtual content::ShellURLRequestContextGetter* CreateURLRequestContextGetter(
      content::ProtocolHandlerMap* protocol_handlers,
      content::URLRequestInterceptorScopedVector request_interceptors);

  bool ignore_certificate_errors() const { return true; }
  net::NetLog* net_log() const { return net_log_; }

  std::unique_ptr<XbResourceContext> resource_context_;

  std::unique_ptr<content::PermissionManager> permission_manager_;
  std::unique_ptr<content::ShellDownloadManagerDelegate> download_manager_delegate_;
  std::unique_ptr<content::BackgroundSyncController> background_sync_controller_;

 private:
  // Performs initialization of the ShellBrowserContext while IO is still
  // allowed on the current thread.
  void InitWhileIOAllowed();

  bool off_the_record_;
  net::NetLog* net_log_;
  base::FilePath path_;
  scoped_refptr<content::ShellURLRequestContextGetter> url_request_getter_;

  DISALLOW_COPY_AND_ASSIGN(XblinkEngineContext);
};

} //end namespace XB
#endif
