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
        this->treeRecords->UnselectAll();
        this->treeRecords->DeleteAllItems();
        wxTreeListItem root = this->treeRecords->GetRootItem();

        for (auto & dbRecord : *this->storage->getRecords()) {
            auto secret = dbRecord->getRecord();

            wxString name(secret->getName()->c_str());
            this->treeRecords->AppendItem(root, name);

            this->listSecrets->Append(name);
        }

        this->grid->ClearGrid();
    }
}
