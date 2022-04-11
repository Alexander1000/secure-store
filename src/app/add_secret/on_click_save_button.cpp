#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#	include <wx/wx.h>
#endif
#include <secure-store.h>

namespace SecureStore::Application
{
    void AddSecretFrame::OnClickSaveButton(wxCommandEvent &event)
    {
        SecureStore::Storage::Record* record = nullptr;
        record = new SecureStore::Storage::Record;

        auto wxName = this->txName->GetValue();
        record->setName(new std::string(wxName.c_str().AsChar()));

        auto wxUser = this->txUser->GetValue();
        if (!wxUser.empty()) {
            record->setUser(new std::string(wxName.c_str().AsChar()));
        }
    }
}
