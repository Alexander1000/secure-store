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

        this->lbName = new wxStaticText(this, F_AS_LB_NAME, _T("Name"));

        this->btnSave = new wxButton(this, F_AS_BTN_SAVE, _T("Save"));
        this->btnCancel = new wxButton(this, F_AS_BTN_CANCEL, _T("Cancel"));
    }
}
