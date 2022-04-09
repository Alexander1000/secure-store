#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#	include <wx/wx.h>
#endif
#include <secure-store.h>

namespace SecureStore::Application
{
    void MainFrame::OnSaveSecretClick(wxCommandEvent &event)
    {
        auto secret = this->getSelectedSecret();
        if (secret == nullptr) {
            return;
        }
    }
}
