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
        auto szTxOpenDirectory = new wxSize(400, 20);
        this->txOpenDirectory->SetSize(*szTxOpenDirectory);
        this->btnOpenDirectory = new wxButton(panel, F_NEW_FILE_BTN_OPEN_DIRECTORY, _T("select"));

        this->lbFileName = new wxStaticText(panel, F_NEW_FILE_LB_FILE_NAME, _T("File name:"));
        int xLbFileNameWidth = this->lbFileName->GetSize().GetWidth();
        this->txFileName = new wxTextCtrl(panel, F_NEW_FILE_TX_FILE_NAME, wxEmptyString);
        auto szTxFileName = new wxSize(400, 20);
        this->txFileName->SetSize(*szTxFileName);

        this->lbNewLogin = new wxStaticText(panel, F_NEW_FILE_LB_LOGIN, _T("Login:"));
        int xLbLoginWidth = this->lbNewLogin->GetSize().GetWidth();
        this->txNewLogin = new wxTextCtrl(panel, F_NEW_FILE_TX_LOGIN, wxEmptyString);
        this->txNewLogin->SetSize(wxSize(400, 20));

        this->lbPassword = new wxStaticText(panel, F_NEW_FILE_LB_PASSWORD, _T("Password:"));
        int xLbPasswordWidth = this->lbPassword->GetSize().GetWidth();
        this->txPassword = new wxTextCtrl(panel, F_NEW_FILE_TX_PASSWORD, wxEmptyString);
        auto szTxPassword = new wxSize(400, 20);
        this->txPassword->SetSize(*szTxPassword);

        this->btnCreateFile = new wxButton(panel, F_NEW_FILE_BTN_CREATE, _T("Create"));
        this->lbCreateNewFileError = new wxStaticText(panel, F_NEW_FILE_LB_ERROR, wxEmptyString);
        this->lbCreateNewFileError->Hide();

        int xLabelMaxWidth = xLbFileNameWidth;
        if (xLbOpenDirectoryWidth > xLabelMaxWidth) {
            xLabelMaxWidth = xLbOpenDirectoryWidth;
        }
        if (xLbLoginWidth > xLabelMaxWidth) {
            xLabelMaxWidth = xLbLoginWidth;
        }
        if (xLbPasswordWidth > xLabelMaxWidth) {
            xLabelMaxWidth = xLbPasswordWidth;
        }

        int xMargin = 7, yMargin = 7;
        int yOffset = yMargin << 1;

        // open directory

        auto posLbOpenDirectory = new wxPoint(
            xMargin + xLabelMaxWidth - xLbOpenDirectoryWidth,
            yOffset
        );
        this->lbOpenDirectory->SetPosition(*posLbOpenDirectory);

        auto posTxOpenDirectory = new wxPoint(
            posLbOpenDirectory->x + this->lbOpenDirectory->GetSize().GetWidth() + xMargin,
            yOffset
        );
        this->txOpenDirectory->SetPosition(*posTxOpenDirectory);

        auto posBtnOpenDirectory = new wxPoint(
            posTxOpenDirectory->x + this->txOpenDirectory->GetSize().GetWidth() + xMargin,
            yOffset
        );
        this->btnOpenDirectory->SetPosition(*posBtnOpenDirectory);

        // file name

        yOffset += 25;

        auto posLbFileName = new wxPoint(
            xMargin + xLabelMaxWidth - xLbFileNameWidth,
            yOffset
        );
        this->lbFileName->SetPosition(*posLbFileName);

        auto posTxFileName = new wxPoint(
            posLbFileName->x + this->lbFileName->GetSize().GetWidth() + xMargin,
            yOffset
        );
        this->txFileName->SetPosition(*posTxFileName);

        // login

        yOffset += 25;

        this->lbNewLogin->SetPosition(wxPoint(
            xMargin + xLabelMaxWidth - xLbLoginWidth,
            yOffset
        ));

        this->txNewLogin->SetPosition(wxPoint(
            this->lbNewLogin->GetPosition().x + this->lbNewLogin->GetSize().GetWidth() + xMargin,
            yOffset
        ));

        // password

        yOffset += 25;

        auto posLbPassword = new wxPoint(
            xMargin + xLabelMaxWidth - xLbPasswordWidth,
            yOffset
        );
        this->lbPassword->SetPosition(*posLbPassword);

        auto posTxPassword = new wxPoint(
            posLbPassword->x + this->lbPassword->GetSize().GetWidth() + xMargin,
            yOffset
        );
        this->txPassword->SetPosition(*posTxPassword);

        // create button

        yOffset += 25;

        auto posBtnCreateFile = new wxPoint(xMargin, yOffset);
        this->btnCreateFile->SetPosition(*posBtnCreateFile);

        auto posLbCreateNewFileError = new wxPoint(
            posBtnCreateFile->x + this->btnCreateFile->GetSize().GetWidth() + xMargin,
            yOffset
        );
        this->lbCreateNewFileError->SetPosition(*posLbCreateNewFileError);

        return panel;
    }
}
