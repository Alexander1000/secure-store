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

        int xMarginOffset = 7;
        int yOffset = 30;
        int yInterval = 25;
        int nRow = 0;
        int xTextOffset = 120;
        int xTextSize = this->GetSize().GetWidth() - xTextOffset - xMarginOffset;
        int yTextSize = 20;

        // name

        this->lbName = new wxStaticText(this, F_AS_LB_NAME, _T("Name:"));
        int xLbPosition = xTextOffset - this->lbName->GetSize().GetWidth() - xMarginOffset;
        this->lbName->SetPosition(wxPoint(xLbPosition, yOffset + yInterval * nRow));

        this->txName = new wxTextCtrl(this, F_AS_TX_NAME, wxEmptyString);
        this->txName->SetPosition(wxPoint(xTextOffset, yOffset + yInterval * nRow));
        this->txName->SetSize(wxSize(xTextSize, yTextSize));

        // user

        nRow++;

        this->lbUser = new wxStaticText(this, F_AS_LB_USER, _T("User:"));
        xLbPosition = xTextOffset - this->lbUser->GetSize().GetWidth() - xMarginOffset;
        this->lbUser->SetPosition(wxPoint(xLbPosition, yOffset + yInterval * nRow));

        this->txUser = new wxTextCtrl(this, F_AS_TX_USER, wxEmptyString);
        this->txUser->SetPosition(wxPoint(xTextOffset, yOffset + yInterval * nRow));
        this->txUser->SetSize(wxSize(xTextSize, yTextSize));

        // password

        nRow++;

        this->lbPassword = new wxStaticText(this, F_AS_LB_PASSWORD, _T("Password:"));
        xLbPosition = xTextOffset - this->lbPassword->GetSize().GetWidth() - xMarginOffset;
        this->lbPassword->SetPosition(wxPoint(xLbPosition, yOffset + yInterval * nRow));

        this->txPassword = new wxTextCtrl(this, F_AS_TX_PASSWORD, wxEmptyString);
        this->txPassword->SetPosition(wxPoint(xTextOffset, yOffset + yInterval * nRow));
        this->txPassword->SetSize(wxSize(xTextSize, yTextSize));

        // comment

        nRow++;

        this->lbComment = new wxStaticText(this, F_AS_LB_COMMENT, _T("Comment:"));
        xLbPosition = xTextOffset - this->lbComment->GetSize().GetWidth() - xMarginOffset;
        this->lbComment->SetPosition(wxPoint(xLbPosition, yOffset + yInterval * nRow));

        this->txComment = new wxTextCtrl(this, F_AS_TX_COMMENT, wxEmptyString);
        this->txComment->SetPosition(wxPoint(xTextOffset, yOffset + yInterval * nRow));
        this->txComment->SetSize(wxSize(xTextSize, yTextSize));

        // buttons

        this->btnSave = new wxButton(this, F_AS_BTN_SAVE, _T("Save"), wxPoint(5, this->GetSize().y - 60));
        this->btnCancel = new wxButton(this, F_AS_BTN_CANCEL, _T("Cancel"), wxPoint(5 + this->btnSave->GetSize().x, this->GetSize().y - 60));
    }
}
