#ifndef CONTENT_BROWSER_CLIENT_XB_H
#define CONTENT_BROWSER_CLIENT_XB_H

#include <memory>
#include <string>

#include "base/compiler_specific.h"
#include "base/files/file_path.h"
#include "build/build_config.h"
#include "content/public/browser/content_browser_client.h"
#include "content/public/browser/quota_permission_context.h"

//#include "content/shell/browser/shell_resource_dispatcher_host_delegate.h"
//#include "content/shell/browser/shell_speech_recognition_manager_delegate.h"

namespace XB {

class ContentBrowserClientXb : public content::ContentBrowserClient {
public:
  ContentBrowserClientXb();
  ~ContentBrowserClientXb() override;

  // ContentBrowserClient overrides.
  content::BrowserMainParts* CreateBrowserMainParts(const content::MainFunctionParams& parameters) override;

  bool IsHandledURL(const GURL& url) override;
//  void RegisterInProcessServices(StaticServiceMap* services) override;
//  void RegisterOutOfProcessServices(OutOfProcessServiceMap* services) override;
//  std::unique_ptr<base::Value> GetServiceManifestOverlay(base::StringPiece name) override;

//void AppendExtraCommandLineSwitches(base::CommandLine* command_line,int child_process_id) override;
//  void ResourceDispatcherHostCreated() override;
//  std::string GetDefaultDownloadName() override;
// WebContentsViewDelegate* GetWebContentsViewDelegate(WebContents* web_contents) override;
  content::QuotaPermissionContext* CreateQuotaPermissionContext() override;
  void GetQuotaSettings(content::BrowserContext* context,
                        content::StoragePartition* partition,
                        const storage::OptionalQuotaSettingsCallback& callback) override;
  void SelectClientCertificate(content::WebContents* web_contents,
                               net::SSLCertRequestInfo* cert_request_info,
                               std::unique_ptr<content::ClientCertificateDelegate> delegate) override;
//  SpeechRecognitionManagerDelegate* CreateSpeechRecognitionManagerDelegate() override;
//  net::NetLog* GetNetLog() override;
//  bool ShouldSwapProcessesForRedirect(BrowserContext* browser_context,
//                                      const GURL& current_url,
//                                      const GURL& new_url) override;
//  DevToolsManagerDelegate* GetDevToolsManagerDelegate() override;

//  void OpenURL(BrowserContext* browser_context,
//               const OpenURLParams& params,
//               const base::Callback<void(WebContents*)>& callback) override;

  content::BrowserContext* browser_context();
  content::BrowserMainParts* browser_main_parts() {
    return browser_main_parts_;
  }

private:
  base::Closure select_client_certificate_callback_;

  content::BrowserMainParts* browser_main_parts_;
};

} //end namespace XB
#endif
