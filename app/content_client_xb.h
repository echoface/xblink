#ifndef CONTENT_CLIENT_XBLINK_H
#define CONTENT_CLIENT_XBLINK_H

#include <string>
#include <vector>

#include "base/compiler_specific.h"
#include "content/public/common/content_client.h"
#include "content/public/common/origin_trial_policy.h"
//#include "content/shell/common/shell_origin_trial_policy.h"

namespace XB {

class XBContentClient : public content::ContentClient {
public:
  XBContentClient();
  ~XBContentClient() override;

  std::string GetUserAgent() const override;
  base::string16 GetLocalizedString(int message_id) const override;
  base::StringPiece GetDataResource(int resource_id, ui::ScaleFactor scale_factor) const override;
  base::RefCountedMemory* GetDataResourceBytes(int resource_id) const override;
  gfx::Image& GetNativeImageNamed(int resource_id) const override;

  bool IsSupplementarySiteIsolationModeEnabled() override;
  content::OriginTrialPolicy* GetOriginTrialPolicy() override;

private:
  //content::OriginTrialPolicy origin_trial_policy_;
};

} //end of namespace
#endif
