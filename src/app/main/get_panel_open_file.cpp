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

        auto posLbFileBrowse = new wxPoint(xMargin, yOffset);
        this->lbFileBrowse = new wxStaticText(panel, F_AUTH_LB_FILE_BROWSE, _T("File:"), *posLbFileBrowse);
        auto posTxFilePath = new wxPoint(xMargin + this->lbFileBrowse->GetSize().GetWidth() + xMargin, yOffset);
        this->txFilePath = new wxTextCtrl(panel, F_AUTH_TX_FILE_PATH, wxEmptyString, *posTxFilePath);
        auto szTxFilePath = new wxSize(400, 20);
        this->txFilePath->SetSize(*szTxFilePath);
        this->txFilePath->Disable();
        int xLabelFileBrowseWidth = this->lbFileBrowse->GetSize().GetWidth();
        auto posBtnFileBrowse = new wxPoint(posLbFileBrowse->x + this->txFilePath->GetSize().GetWidth() + xMargin, yOffset);
        this->btnFileBrowse = new wxButton(
            panel,
            F_AUTH_BTN_FILE_BROWSE,
            _T("Browse"),
            *posBtnFileBrowse
        );

        yOffset += 30;
        auto posLbLogin = new wxPoint(xMargin, yOffset);
        this->lbLogin = new wxStaticText(panel, F_AUTH_LB_LOGIN, _T("Login:"), *posLbLogin);
        int xLabelLoginWidth = this->lbLogin->GetSize().GetWidth();
        auto posTxLogin = new wxPoint(xMargin + this->lbLogin->GetSize().GetWidth() + xMargin, yOffset);
        auto szTxLogin = new wxSize(400, 20);
        this->txLogin = new wxTextCtrl(
            panel,
            F_AUTH_TX_LOGIN,
            wxEmptyString,
            *posTxLogin,
            *szTxLogin
        );

        yOffset += 30;
        auto posLbPasswordEnter = new wxPoint(xMargin, yOffset);
        this->lbPasswordEnter = new wxStaticText(panel, F_AUTH_LB_PASSWORD, _T("Password:"), *posLbPasswordEnter);
        int xLabelPasswordEnterWidth = this->lbPasswordEnter->GetSize().GetWidth();
        auto posTextPasswordCtrl = new wxPoint(xMargin + this->lbPasswordEnter->GetSize().GetWidth() + xMargin, yOffset);
        auto szTextPasswordCtrl = new wxSize(400, 20);
        this->textPasswordCtrl = new wxTextCtrl(
            panel,
            TEXT_PASSWORD_Entry,
            _T(""),
            *posTextPasswordCtrl,
            *szTextPasswordCtrl,
            wxTE_PASSWORD,
            wxDefaultValidator
        );
        auto posBtnPasswordEnter = new wxPoint(posTextPasswordCtrl->x + this->textPasswordCtrl->GetSize().GetWidth() + xMargin, yOffset);
        this->btnPasswordEnter = new wxButton(
            panel,
            BUTTON_PASSWORD_ENTER,
            _T("Enter"),
            *posBtnPasswordEnter,
            wxDefaultSize,
            0
        );

        int xLabelBlockWidth = xLabelFileBrowseWidth;
        if (xLabelLoginWidth > xLabelBlockWidth) {
            xLabelBlockWidth = xLabelLoginWidth;
        }
        if (xLabelPasswordEnterWidth > xLabelBlockWidth) {
            xLabelBlockWidth = xLabelPasswordEnterWidth;
        }
        // make margin
        xLabelBlockWidth += xMargin << 1;

        // align elements
        posTxFilePath->x = xLabelBlockWidth;
        this->txFilePath->SetPosition(*posTxFilePath);
        posBtnFileBrowse->x = posTxFilePath->x + this->txFilePath->GetSize().GetWidth() + xMargin;
        this->btnFileBrowse->SetPosition(*posBtnFileBrowse);
        posTxLogin->x = xLabelBlockWidth;
        this->txLogin->SetPosition(*posTxLogin);
        posTextPasswordCtrl->x = xLabelBlockWidth;
        this->textPasswordCtrl->SetPosition(*posTextPasswordCtrl);
        posBtnPasswordEnter->x = posTextPasswordCtrl->x + this->textPasswordCtrl->GetSize().GetWidth() + xMargin;
        this->btnPasswordEnter->SetPosition(*posBtnPasswordEnter);

        this->lbPasswordResult = new wxStaticText(panel, STATIC_TEXT_PASSWORD_RESULT, wxEmptyString);
        auto posLbPasswordResult = new wxPoint(this->textPasswordCtrl->GetPosition().x, this->textPasswordCtrl->GetPosition().y + 20);
        this->lbPasswordResult->SetPosition(*posLbPasswordResult);
        auto fontInfo = new wxFontInfo;
        fontInfo->Bold(true);
        auto font = new wxFont(*fontInfo);
        font->SetPointSize(12);
        this->lbPasswordResult->SetFont(*font);
        this->lbPasswordResult->Hide();

        return panel;
    }
}
