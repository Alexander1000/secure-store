#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#	include <wx/wx.h>
#endif
#include <secure-store.h>

namespace SecureStore::Application
{
    void AddSecretFrame::initialize()
    {
        this->lbTitleText = new wxStaticText(this, F_AS_LB_TITLE_TEXT, _T("Input data for save in db:"));
        wxPoint wxPosTitleText((this->GetSize().x - this->lbTitleText->GetSize().x) >> 1, 5);
        this->lbTitleText->SetPosition(wxPosTitleText);
        this->lbTitleText->SetFont(wxFont(wxFontInfo().Bold()));

        // render parameters

        int yOffset = 30;
        int yInterval = 25;
        int nRow = 0;
        int xTextOffset = 120;

        // name

        this->lbName = new wxStaticText(this, F_AS_LB_NAME, _T("Name:"));
        this->lbName->SetPosition(wxPoint(5, yOffset + yInterval * nRow));

        this->txName = new wxTextCtrl(this, F_AS_TX_NAME, wxEmptyString);
        this->txName->SetPosition(wxPoint(xTextOffset, yOffset + yInterval * nRow));

        // user

        nRow++;

        this->lbUser = new wxStaticText(this, F_AS_LB_USER, _T("User:"));
        this->lbUser->SetPosition(wxPoint(5, yOffset + yInterval * nRow));

        this->txUser = new wxTextCtrl(this, F_AS_TX_USER, wxEmptyString);
        this->txUser->SetPosition(wxPoint(xTextOffset, yOffset + yInterval * nRow));

        // password

        nRow++;

        this->lbPassword = new wxStaticText(this, F_AS_LB_PASSWORD, _T("Password:"));
        this->lbPassword->SetPosition(wxPoint(5, yOffset + yInterval * nRow));

        this->txPassword = new wxTextCtrl(this, F_AS_TX_PASSWORD, wxEmptyString);
        this->txPassword->SetPosition(wxPoint(xTextOffset, yOffset + yInterval * nRow));

        // comment

        nRow++;

        this->lbComment = new wxStaticText(this, F_AS_LB_COMMENT, _T("Comment:"));
        this->lbComment->SetPosition(wxPoint(5, yOffset + yInterval * nRow));

        this->txComment = new wxTextCtrl(this, F_AS_TX_COMMENT, wxEmptyString);
        this->txComment->SetPosition(wxPoint(xTextOffset, yOffset + yInterval * nRow));

        // buttons

        this->btnSave = new wxButton(this, F_AS_BTN_SAVE, _T("Save"), wxPoint(5, this->GetSize().y - 60));
        this->btnCancel = new wxButton(this, F_AS_BTN_CANCEL, _T("Cancel"), wxPoint(5 + this->btnSave->GetSize().x, this->GetSize().y - 60));
    }
}
