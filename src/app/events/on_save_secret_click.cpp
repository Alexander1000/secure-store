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

        bool dirty = false;

        // name
        auto wxStrName = this->grid->GetCellValue(1, 1);
        if (wxStrName != secret->getName()) {
            secret->setName(new std::string(wxStrName.c_str().AsChar()));
            dirty = true;
        }

        // user
        auto wxStrUser = this->grid->GetCellValue(2, 1);
        if (wxStrUser.empty() && secret->getUser() != nullptr) {
            secret->setUser(nullptr);
            dirty = true;
        }
        if (!wxStrUser.empty() && (secret->getUser() == nullptr || wxStrUser != secret->getUser())) {
            secret->setUser(new std::string(wxStrUser.c_str().AsChar()));
            dirty = true;
        }

        // password
        auto wxStrPassword = this->grid->GetCellValue(3, 1);
        if (wxStrPassword.empty() && secret->getPassword() != nullptr) {
            secret->setPassword(nullptr);
            dirty = true;
        }
        if (!wxStrPassword.empty() && (secret->getPassword() == nullptr || wxStrPassword != secret->getPassword())) {
            secret->setPassword(new std::string(wxStrPassword.c_str().AsChar()));
            dirty = true;
        }
    }
}
