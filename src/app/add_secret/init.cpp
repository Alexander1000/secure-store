#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#	include <wx/wx.h>
#endif
#include <secure-store.h>

namespace SecureStore::Application
{
    BEGIN_EVENT_TABLE ( AddSecretFrame, wxFrame )
        // EVT_WINDOW_MODAL_DIALOG_CLOSED(FRAME_ADD_SECRET, AddSecretFrame::OnCloseWindow)
    END_EVENT_TABLE()

    AddSecretFrame::AddSecretFrame(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &pos, const wxSize &size)
            : wxFrame(parent, id, title, pos, size)
    {
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
