#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#	include <wx/wx.h>
#endif
#include <secure-store.h>

namespace SecureStore::Application
{
    void ShowFrame::OnClickRemoveSecret(wxCommandEvent &event)
    {
        if (this->selectedSecretIndex < 0
            || this->storage == nullptr
            || this->storage->getRecords() == nullptr
            || this->storage->getRecords()->empty()
            || this->selectedSecretIndex >= this->storage->getRecords()->size()) {
            return;
        }

        int index = 0;

        for (auto & it : *this->storage->getRecords()) {
            auto record = it->getRecord();

            if (index == this->selectedSecretIndex) {
                this->storage->getRecords()->remove(it);
                break;
            }

            index++;
        }

        this->storage->save();
        this->reloadContent();
    }
}
