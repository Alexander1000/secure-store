#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#	include <wx/wx.h>
#endif
#include <secure-store.h>

namespace SecureStore::Application
{
    BEGIN_EVENT_TABLE(MainFrame, wxFrame)
        EVT_BUTTON(BUTTON_PASSWORD_ENTER, MainFrame::OnPasswordEnter)
        EVT_BUTTON(F_AUTH_BTN_FILE_BROWSE, MainFrame::OnFileBrowseClick)
    END_EVENT_TABLE()
}
