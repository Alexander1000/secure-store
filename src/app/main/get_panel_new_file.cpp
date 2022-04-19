#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#	include <wx/wx.h>
#endif
#include <secure-store.h>
#include <memory>
#include <wx/panel.h>

namespace SecureStore::Application
{
    wxPanel *MainFrame::getPanelNewFile(wxWindow *parent)
    {
        auto panel = new wxPanel(parent);

        this->lbOpenDirectory = new wxStaticText(panel, F_NEW_FILE_LB_OPEN_DIRECTORY, _T("Directory:"));
        this->txOpenDirectory = new wxTextCtrl(panel, F_NEW_FILE_TX_OPEN_DIRECTORY, wxEmptyString);
        this->btnOpenDirectory = new wxButton(panel, F_NEW_FILE_BTN_OPEN_DIRECTORY, _T("select"));

        return panel;
    }
}
