#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#	include <wx/wx.h>
#endif
#include <secure-store.h>

namespace SecureStore::Application
{
    BEGIN_EVENT_TABLE(AddSecretFrame, wxFrame)
        EVT_BUTTON(F_AS_BTN_CANCEL, AddSecretFrame::OnClickCancelButton)
        EVT_BUTTON(F_AS_BTN_SAVE, AddSecretFrame::OnClickSaveButton)
    END_EVENT_TABLE()

    AddSecretFrame::AddSecretFrame(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &pos, const wxSize &size, SecureStore::Storage::DB* storage)
            : wxFrame(parent, id, title, pos, size)
    {
        this->storage = storage;

        this->GetParent()->Disable();
        this->GetParent()->SetTransparent(wxByte(220));
        this->Bind(wxEVT_CLOSE_WINDOW, [&](wxCloseEvent& event)
        {
            this->GetParent()->SetTransparent(wxByte(255));
            this->GetParent()->Enable();
            event.Skip();
        });

        this->initialize();
    }
}
