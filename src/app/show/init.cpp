#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#	include <wx/wx.h>
#endif
#include <secure-store.h>
#include <wx/listbox.h>

namespace SecureStore::Application
{
    BEGIN_EVENT_TABLE(ShowFrame, wxFrame)
        EVT_BUTTON(BUTTON_SAVE_SECRET, ShowFrame::OnSaveSecretClick)
        EVT_BUTTON(BUTTON_ADD_SECRET, ShowFrame::OnAddSecretClick)
        EVT_BUTTON(F_SHOW_BTN_REMOVE_SECRET, ShowFrame::OnClickRemoveSecret)
        EVT_LISTBOX(F_SHOW_LIST_SECRETS, ShowFrame::OnSelectItem)
    END_EVENT_TABLE()

    ShowFrame::ShowFrame(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &pos, const wxSize &size, SecureStore::Storage::DB* storage)
            : wxFrame(parent, id, title, pos, size)
    {
        this->storage = storage;
        this->grid = nullptr;
        this->btnSaveSecret = nullptr;
        this->btnAddSecret = nullptr;
        this->btnRemoveSecret = nullptr;
        this->listSecrets = nullptr;

        this->addSecretFrame = nullptr;

        this->selectedSecretIndex = -1;
    }
}
