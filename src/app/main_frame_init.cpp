#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#	include <wx/wx.h>
#endif
#include <secure-store.h>

namespace SecureStore::Application
{
    MainFrame::MainFrame(const wxString &title, const wxPoint &pos, const wxSize &size)
        : wxFrame((wxFrame *) NULL, -1, title, pos, size)
    {
        this->btnPasswordEnter = new wxButton(this, BUTTON_PASSWORD_ENTER, _T("Enter"), wxPoint(110, 5), wxDefaultSize, 0);

        this->textPasswordCtrl = new wxTextCtrl(this, TEXT_PASSWORD_Entry, _T(""), wxPoint(5, 5), wxSize(100, 20), wxTE_PASSWORD, wxDefaultValidator);
    }

    BEGIN_EVENT_TABLE ( MainFrame, wxFrame )
        EVT_BUTTON ( BUTTON_PASSWORD_ENTER, MainFrame::OnPasswordEnter )
    END_EVENT_TABLE()

    void MainFrame::OnPasswordEnter( wxCommandEvent& event )
    {
        Close(TRUE);
    }
}
