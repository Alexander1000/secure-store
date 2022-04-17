#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#	include <wx/wx.h>
#endif
#include <secure-store.h>
#include <memory>
#include <wx/panel.h>

namespace SecureStore::Application
{
    wxPanel *MainFrame::getPanelOpenFile(wxWindow *parent)
    {
        auto panel = new wxPanel(parent);

        int xMargin = 7;
        int yMargin = 7;

        int yOffset = yMargin * 3;

        this->lbFileBrowse = new wxStaticText(panel, F_AUTH_LB_FILE_BROWSE, _T("File:"), wxPoint(xMargin, yOffset));
        this->txFilePath = new wxTextCtrl(panel, F_AUTH_TX_FILE_PATH, wxEmptyString, wxPoint(xMargin + this->lbFileBrowse->GetSize().GetWidth() + xMargin, yOffset));
        this->txFilePath->SetSize(wxSize(400, 20));
        this->txFilePath->Disable();
        int xLabelFileBrowseWidth = this->lbFileBrowse->GetSize().GetWidth();
        this->btnFileBrowse = new wxButton(
            panel,
            F_AUTH_BTN_FILE_BROWSE,
            _T("Browse"),
            wxPoint(this->txFilePath->GetPosition().x + this->txFilePath->GetSize().GetWidth() + xMargin, yOffset)
        );

        yOffset += 30;
        this->lbPasswordEnter = new wxStaticText(panel, F_AUTH_LB_PASSWORD, _T("Password:"), wxPoint(xMargin, yOffset));
        int xLabelPasswordEnterWidth = this->lbPasswordEnter->GetSize().GetWidth();
        this->textPasswordCtrl = new wxTextCtrl(
            panel,
            TEXT_PASSWORD_Entry,
            _T(""),
            wxPoint(xMargin + this->lbPasswordEnter->GetSize().GetWidth() + xMargin, yOffset),
            wxSize(400, 20),
            wxTE_PASSWORD,
            wxDefaultValidator
        );
        this->btnPasswordEnter = new wxButton(
            panel,
            BUTTON_PASSWORD_ENTER,
            _T("Enter"),
            wxPoint(this->textPasswordCtrl->GetPosition().x + this->textPasswordCtrl->GetSize().GetWidth() + xMargin, yOffset),
            wxDefaultSize,
            0
        );

        int xLabelBlockWidth;
        if (xLabelFileBrowseWidth > xLabelPasswordEnterWidth) {
            xLabelBlockWidth = xLabelFileBrowseWidth;
        } else {
            xLabelBlockWidth = xLabelPasswordEnterWidth;
        }
        // make margin
        xLabelBlockWidth += xMargin << 1;

        // align elements
        this->txFilePath->SetPosition(wxPoint(xLabelBlockWidth, this->txFilePath->GetPosition().y));
        this->btnFileBrowse->SetPosition(wxPoint(this->txFilePath->GetPosition().x + this->txFilePath->GetSize().GetWidth() + xMargin, this->txFilePath->GetPosition().y));
        this->textPasswordCtrl->SetPosition(wxPoint(xLabelBlockWidth, this->textPasswordCtrl->GetPosition().y));
        this->btnPasswordEnter->SetPosition(wxPoint(this->textPasswordCtrl->GetPosition().x + this->textPasswordCtrl->GetSize().GetWidth() + xMargin, this->textPasswordCtrl->GetPosition().y));

        this->lbPasswordResult = new wxStaticText(panel, STATIC_TEXT_PASSWORD_RESULT, wxEmptyString);
        this->lbPasswordResult->Hide();

        return panel;
    }
}
