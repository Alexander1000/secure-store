#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#	include <wx/wx.h>
#endif
#include <secure-store.h>

namespace SecureStore::Application
{
    void MainFrame::reloadContent()
    {
        this->treeRecords->UnselectAll();
        this->treeRecords->ClearColumns();
        wxTreeListItem root = this->treeRecords->GetRootItem();

        for (auto & dbRecord : *this->storage->getRecords()) {
            auto secret = dbRecord->getRecord();

            wxString name(secret->getName()->c_str());
            this->treeRecords->AppendItem(root, name);
        }

        this->grid->ClearGrid();
    }
}
