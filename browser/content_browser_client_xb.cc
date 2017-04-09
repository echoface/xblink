#include "content_browser_client_xb.h"
#include "content/public/browser/browser_main_parts.h"
#include "storage/common/quota/quota_types.h"


namespace XB {

ContentBrowserClientXb::ContentBrowserClientXb() {
}

ContentBrowserClientXb::~ContentBrowserClientXb() {

};

content::BrowserMainParts* ContentBrowserClientXb::CreateBrowserMainParts(const content::MainFunctionParams& parameters) {
  return new content::BrowserMainParts();
}

bool ContentBrowserClientXb::IsHandledURL(const GURL& url) {
  return true;
}

content::QuotaPermissionContext* ContentBrowserClientXb::CreateQuotaPermissionContext() {
  return NULL;//content::QuotaPermissionContext();
}

void ContentBrowserClientXb::GetQuotaSettings(content::BrowserContext* context,
                                              content::StoragePartition* partition,
                                              const storage::OptionalQuotaSettingsCallback& callback) {
  callback.Run(storage::GetHardCodedSettings(100 * 1024 * 1024));
}

void ContentBrowserClientXb::SelectClientCertificate(content::WebContents* web_contents,
                                                     net::SSLCertRequestInfo* cert_request_info,
                                                     std::unique_ptr<content::ClientCertificateDelegate> delegate) {
}

content::BrowserContext* ContentBrowserClientXb::browser_context() {
  return NULL;//browser_main_parts_->browser_context();
}


}//end of namespace
