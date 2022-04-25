#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#	include <wx/wx.h>
#endif
#include <secure-store.h>

namespace SecureStore::Application
{
    void ShowFrame::reloadContent()
    {
        this->selectedSecretIndex = -1;
        this->listSecrets->Clear();

        for (auto & dbRecord : *this->storage->getRecords()) {
            auto secret = dbRecord->getRecord();
            wxString name(secret->getName()->c_str());
            this->listSecrets->Append(name);
        }

        this->grid->ClearGrid();
    }
}
