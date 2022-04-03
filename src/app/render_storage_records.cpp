#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#	include <wx/wx.h>
#endif
#include <secure-store.h>
#include <wx/treelist.h>

namespace SecureStore::Application
{
    void MainFrame::renderStorageRecords()
    {
        this->treeRecords = new wxTreeListCtrl(this, TREE_DB_RECORDS, wxDefaultPosition, wxSize(300, 200));

        this->treeRecords->AppendColumn("Name",
           wxCOL_WIDTH_AUTOSIZE,
           wxALIGN_LEFT,
           wxCOL_RESIZABLE);

        wxTreeListItem root = this->treeRecords->GetRootItem();

        for (auto & dbRecord : *this->storage->getRecords()) {
            auto secret = dbRecord->getRecord();

            wxString name(secret->getName()->c_str());
            wxTreeListItem item = this->treeRecords->AppendItem(root, name);
        }
    }
}
