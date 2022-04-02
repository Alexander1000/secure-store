#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#	include <wx/wx.h>
#endif
#include <secure-store.h>

namespace SecureStore::Application {

    IMPLEMENT_APP_NO_MAIN(MainApp) // A macro that tells wxWidgets to create an instance of our application

    bool MainApp::OnInit() {
        // Create an instance of our frame, or window
        MainFrame *MainWin = new MainFrame(_("Secure store"), wxDefaultPosition, wxSize(300, 200));
        MainWin->Show(true); // show the window
        SetTopWindow(MainWin); // and finally, set it as the main window
        return true;
    }

    MainFrame::MainFrame(const wxString &title, const wxPoint &pos, const wxSize &size)
            : wxFrame((wxFrame *) NULL, -1, title, pos, size) {
        // normally we would initialize objects such as buttons and textboxes here
        this->helloWorld = new wxButton(this, BUTTON_Hello, _T("Hello World"),
            // shows a button on this window
          wxDefaultPosition, wxDefaultSize, 0); // with the text "hello World"

        wxPoint textPosition(100, 0);
        this->textCtrl = new wxTextCtrl(this, TEXT_Entry, _T(""), textPosition, wxDefaultSize, 0, wxDefaultValidator);
    }

    BEGIN_EVENT_TABLE ( MainFrame, wxFrame )
        EVT_BUTTON ( BUTTON_Hello, MainFrame::OnExit ) // Tell the OS to run MainFrame::OnExit when
    END_EVENT_TABLE() // The button is pressed

    void MainFrame::OnExit( wxCommandEvent& event )
    {
        Close(TRUE); // Tells the OS to quit running this process
    }
}
