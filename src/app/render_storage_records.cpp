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
        this->treeRecords = new wxTreeListCtrl(this, TREE_DB_RECORDS);
    }
}
