#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#	include <wx/wx.h>
#endif
#include <secure-store.h>

namespace SecureStore::Application
{
    void AddSecretFrame::initialize()
    {
        this->lbTitleText = new wxStaticText(this, F_AS_LB_TITLE_TEXT, _T("Input data for save in db"));
        wxPoint wxPosTitleText((this->GetSize().x - this->lbTitleText->GetSize().x) >> 1, 0);
        this->lbTitleText->SetPosition(wxPosTitleText);

        this->lbName = new wxStaticText(this, F_AS_LB_NAME, _T("Name"));
        this->lbName->SetPosition(wxPoint(5, 20));

        this->btnSave = new wxButton(this, F_AS_BTN_SAVE, _T("Save"), wxPoint(5, this->GetSize().y - 60));
        this->btnCancel = new wxButton(this, F_AS_BTN_CANCEL, _T("Cancel"), wxPoint(5 + this->btnSave->GetSize().x, this->GetSize().y - 60));
    }
}
