#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#	include <wx/wx.h>
#endif
#include <secure-store.h>

namespace SecureStore::Application
{
    BEGIN_EVENT_TABLE ( MainFrame, wxFrame )
        EVT_BUTTON(BUTTON_PASSWORD_ENTER, MainFrame::OnPasswordEnter)
        EVT_TREELIST_SELECTION_CHANGED(TREE_DB_RECORDS, MainFrame::OnChoiceSecret)
        EVT_BUTTON(BUTTON_SAVE_SECRET, MainFrame::OnSaveSecretClick)
        EVT_BUTTON(BUTTON_ADD_SECRET, MainFrame::OnAddSecretClick)
    END_EVENT_TABLE()
}
