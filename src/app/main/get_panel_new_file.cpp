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

        int xMargin = 7, yMargin = 7;

        int yOffset = yMargin;

        this->lbOpenDirectory = new wxStaticText(panel, F_NEW_FILE_LB_OPEN_DIRECTORY, _T("Directory:"));
        this->lbOpenDirectory->SetPosition(wxPoint(xMargin, yOffset));
        this->txOpenDirectory = new wxTextCtrl(panel, F_NEW_FILE_TX_OPEN_DIRECTORY, wxEmptyString);
        this->txOpenDirectory->SetPosition(wxPoint(xMargin + this->lbOpenDirectory->GetSize().GetWidth() + xMargin, yOffset));
        this->btnOpenDirectory = new wxButton(panel, F_NEW_FILE_BTN_OPEN_DIRECTORY, _T("select"));
        this->btnOpenDirectory->SetPosition(wxPoint(
            this->txOpenDirectory->GetPosition().x + this->txOpenDirectory->GetSize().GetWidth() + xMargin,
            yOffset
        ));

        yOffset += 25;

        this->lbFileName = new wxStaticText(panel, F_NEW_FILE_LB_FILE_NAME, _T("File name:"));
        this->lbFileName->SetPosition(wxPoint(xMargin, yOffset));
        this->txFileName = new wxTextCtrl(panel, F_NEW_FILE_TX_FILE_NAME, wxEmptyString);
        this->txFileName->SetPosition(wxPoint(xMargin + this->lbFileName->GetSize().GetWidth() + xMargin, yOffset));

        yOffset += 25;

        this->lbPassword = new wxStaticText(panel, F_NEW_FILE_LB_PASSWORD, _T("Password:"));
        this->lbPassword->SetPosition(wxPoint(xMargin, yOffset));
        this->txPassword = new wxTextCtrl(panel, F_NEW_FILE_TX_PASSWORD, wxEmptyString);
        this->txPassword->SetPosition(wxPoint(xMargin + this->lbPassword->GetSize().GetWidth() + xMargin, yOffset));

        yOffset += 25;

        this->btnCreateFile = new wxButton(panel, F_NEW_FILE_BTN_CREATE, _T("Create"));
        this->btnCreateFile->SetPosition(wxPoint(xMargin, yOffset));

        return panel;
    }
}
