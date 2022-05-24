#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#	include <wx/wx.h>
#endif
#include <secure-store.h>

namespace SecureStore::Application
{
    wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
        EVT_BUTTON(BUTTON_PASSWORD_ENTER, MainFrame::OnPasswordEnter)
        EVT_BUTTON(F_AUTH_BTN_FILE_BROWSE, MainFrame::OnFileBrowseClick)
        EVT_BUTTON(F_NEW_FILE_BTN_OPEN_DIRECTORY, MainFrame::OnClickSelectDirectory)
        EVT_BUTTON(F_NEW_FILE_BTN_CREATE, MainFrame::OnClickCreateFile)
    wxEND_EVENT_TABLE()
}
