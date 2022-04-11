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

        int maxItemId = 0;

        for (auto & it : *this->storage->getRecords()) {
            int currentId = it->getRecord()->getId();
            if (currentId > maxItemId) {
                maxItemId = currentId;
            }
        }

        record->setId(maxItemId + 1);

        auto wxName = this->txName->GetValue();
        record->setName(new std::string(wxName.c_str().AsChar()));

        auto wxUser = this->txUser->GetValue();
        if (!wxUser.empty()) {
            record->setUser(new std::string(wxName.c_str().AsChar()));
        }

        auto wxPassword = this->txPassword->GetValue();
        if (!wxPassword.empty()) {
            record->setPassword(new std::string(wxPassword.c_str().AsChar()));
        }

        auto wxComment = this->txComment->GetValue();
        if (!wxComment.empty()) {
            record->setComment(new std::string(wxComment.c_str().AsChar()));
        }

        // todo: get current unix time

        this->storage->addRecord(record);

        this->storage->save();
    }
}
