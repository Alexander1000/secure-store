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

        // name
        auto wxStrName = this->grid->GetCellValue(1, 1);
        if (wxStrName != secret->getName()) {
            secret->setName(new std::string(wxStrName.c_str().AsChar()));
        }
    }
}
