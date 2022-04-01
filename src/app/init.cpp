#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#	include <wx/wx.h>
#endif
#include <secure-store.h>

IMPLEMENT_APP_NO_MAIN(MainApp) // A macro that tells wxWidgets to create an instance of our application

bool MainApp::OnInit()
{
    // Create an instance of our frame, or window
    MainFrame *MainWin = new MainFrame(_("Secure store"), wxDefaultPosition, wxSize(300, 200));
    MainWin->Show(true); // show the window
    SetTopWindow(MainWin); // and finally, set it as the main window
    return true;
}

MainFrame::MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
        : wxFrame((wxFrame *) NULL, -1, title, pos, size)
{
    // normally we would initialize objects such as buttons and textboxes here
}
