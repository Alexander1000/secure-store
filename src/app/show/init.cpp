#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#	include <wx/wx.h>
#endif
#include <secure-store.h>

namespace SecureStore::Application
{
    BEGIN_EVENT_TABLE(ShowFrame, wxFrame)
        EVT_TREELIST_SELECTION_CHANGED(TREE_DB_RECORDS, ShowFrame::OnChoiceSecret)
        EVT_BUTTON(BUTTON_SAVE_SECRET, ShowFrame::OnSaveSecretClick)
        EVT_BUTTON(BUTTON_ADD_SECRET, ShowFrame::OnAddSecretClick)
    END_EVENT_TABLE()

    ShowFrame::ShowFrame(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &pos, const wxSize &size, SecureStore::Storage::DB* storage)
            : wxFrame(parent, id, title, pos, size)
    {
        this->storage = storage;
        this->treeRecords = nullptr;
        this->grid = nullptr;
        this->btnSaveSecret = nullptr;
        this->btnAddSecret = nullptr;
        this->btnRemoveSecret = nullptr;

        this->addSecretFrame = nullptr;

        this->selectedSecretIndex = -1;
    }
}
