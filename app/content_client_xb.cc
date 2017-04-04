#include "content_client_xb.h"

#include "base/command_line.h"
#include "base/strings/string_piece.h"
#include "base/strings/utf_string_conversions.h"
#include "blink/public/resources/grit/blink_image_resources.h"
#include "build/build_config.h"
#include "content/app/resources/grit/content_resources.h"
#include "content/app/strings/grit/content_strings.h"
#include "content/public/common/content_switches.h"
#include "content/public/common/user_agent.h"
#include "ui/base/l10n/l10n_util.h"
#include "ui/base/resource/resource_bundle.h"

//#include "content/shell/common/shell_switches.h"
//#include "content/shell/grit/shell_resources.h"
namespace XB {

XBContentClient::XBContentClient() {}

XBContentClient::~XBContentClient() {}

std::string XBContentClient::GetUserAgent() const {
  return "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/57.0.2987.133 Safari/537.36";
}

base::string16 XBContentClient::GetLocalizedString(int message_id) const {
  return l10n_util::GetStringUTF16(message_id);
}

base::StringPiece XBContentClient::GetDataResource(int resource_id, ui::ScaleFactor scale_factor) const {
  return ResourceBundle::GetSharedInstance().GetRawDataResourceForScale(resource_id, scale_factor);
}

base::RefCountedMemory* XBContentClient::GetDataResourceBytes(int resource_id) const {
  return ResourceBundle::GetSharedInstance().LoadDataResourceBytes(resource_id);
}

gfx::Image& XBContentClient::GetNativeImageNamed(int resource_id) const {
  return ResourceBundle::GetSharedInstance().GetNativeImageNamed(resource_id);
}

bool XBContentClient::IsSupplementarySiteIsolationModeEnabled() {
  return false;
}

content::OriginTrialPolicy* XBContentClient::GetOriginTrialPolicy() {
  return NULL;//&origin_trial_policy_;
}

}//end of namespace
