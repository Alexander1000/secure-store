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
        int xLbOpenDirectoryWidth = this->lbOpenDirectory->GetSize().GetWidth();
        this->txOpenDirectory = new wxTextCtrl(panel, F_NEW_FILE_TX_OPEN_DIRECTORY, wxEmptyString);
        this->txOpenDirectory->SetSize(wxSize(400, 20));
        this->btnOpenDirectory = new wxButton(panel, F_NEW_FILE_BTN_OPEN_DIRECTORY, _T("select"));

        this->lbFileName = new wxStaticText(panel, F_NEW_FILE_LB_FILE_NAME, _T("File name:"));
        int xLbFileNameWidth = this->lbFileName->GetSize().GetWidth();
        this->txFileName = new wxTextCtrl(panel, F_NEW_FILE_TX_FILE_NAME, wxEmptyString);
        this->txFileName->SetSize(wxSize(400, 20));

        this->lbPassword = new wxStaticText(panel, F_NEW_FILE_LB_PASSWORD, _T("Password:"));
        int xLbPasswordWidth = this->lbPassword->GetSize().GetWidth();
        this->txPassword = new wxTextCtrl(panel, F_NEW_FILE_TX_PASSWORD, wxEmptyString);
        this->txPassword->SetSize(wxSize(400, 20));

        this->btnCreateFile = new wxButton(panel, F_NEW_FILE_BTN_CREATE, _T("Create"));

        int xLabelMaxWidth = xLbFileNameWidth;
        if (xLbOpenDirectoryWidth > xLabelMaxWidth) {
            xLabelMaxWidth = xLbOpenDirectoryWidth;
        }
        if (xLbPasswordWidth > xLabelMaxWidth) {
            xLabelMaxWidth = xLbPasswordWidth;
        }

        int xMargin = 7, yMargin = 7;
        int yOffset = yMargin << 1;

        // open directory

        this->lbOpenDirectory->SetPosition(wxPoint(
            xMargin + xLabelMaxWidth - xLbOpenDirectoryWidth,
            yOffset
        ));

        this->txOpenDirectory->SetPosition(wxPoint(
            this->lbOpenDirectory->GetPosition().x + this->lbOpenDirectory->GetSize().GetWidth() + xMargin,
            yOffset
        ));

        this->btnOpenDirectory->SetPosition(wxPoint(
            this->txOpenDirectory->GetPosition().x + this->txOpenDirectory->GetSize().GetWidth() + xMargin,
            yOffset
        ));

        // file name

        yOffset += 25;

        this->lbFileName->SetPosition(wxPoint(
            xMargin + xLabelMaxWidth - xLbFileNameWidth,
            yOffset
        ));

        this->txFileName->SetPosition(wxPoint(
            this->lbFileName->GetPosition().x + this->lbFileName->GetSize().GetWidth() + xMargin,
            yOffset
        ));

        // password

        yOffset += 25;

        this->lbPassword->SetPosition(wxPoint(
            xMargin + xLabelMaxWidth - xLbPasswordWidth,
            yOffset
        ));

        this->txPassword->SetPosition(wxPoint(
            this->lbPassword->GetPosition().x + this->lbPassword->GetSize().GetWidth() + xMargin,
            yOffset
        ));

        // create button

        yOffset += 25;

        this->btnCreateFile->SetPosition(wxPoint(xMargin, yOffset));

        return panel;
    }
}
