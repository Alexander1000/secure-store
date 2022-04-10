#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#	include <wx/wx.h>
#endif
#include <secure-store.h>

namespace SecureStore::Application
{
    void AddSecretFrame::initialize()
    {
        this->btnSave = new wxButton(this, F_AS_BTN_SAVE, _T("Save"));
        this->btnCancel = new wxButton(this, F_AS_BTN_CANCEL, _T("Cancel"));
    }
}
