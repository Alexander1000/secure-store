#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#	include <wx/wx.h>
#endif
#include <secure-store.h>

namespace SecureStore::Application
{
    MainFrame::MainFrame(const wxString &title, const wxPoint &pos, const wxSize &size)
            : wxFrame((wxFrame *) NULL, -1, title, pos, size) {

        this->helloWorld = new wxButton(this, BUTTON_Hello, _T("Hello World"),wxDefaultPosition, wxDefaultSize, 0);

        wxPoint textPosition(100, 0);
        this->textCtrl = new wxTextCtrl(this, TEXT_Entry, _T(""), textPosition, wxDefaultSize, 0, wxDefaultValidator);
    }

    BEGIN_EVENT_TABLE ( MainFrame, wxFrame )
        EVT_BUTTON ( BUTTON_Hello, MainFrame::OnExit ) // Tell the OS to run MainFrame::OnExit when
    END_EVENT_TABLE()

    void MainFrame::OnExit( wxCommandEvent& event )
    {
        Close(TRUE);
    }
}
