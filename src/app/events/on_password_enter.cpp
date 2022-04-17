#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#	include <wx/wx.h>
#endif
#include <secure-store.h>

namespace SecureStore::Application
{
    void MainFrame::OnPasswordEnter( wxCommandEvent& event )
    {
        auto value = this->textPasswordCtrl->GetValue();
        int code = this->storage->open(new std::string(this->fileName), new std::string(value.c_str().AsChar()));

        if (code > 0) {
            this->lbPasswordResult->SetLabel("Error");
            this->lbPasswordResult->Show();
            this->lbPasswordResult->SetPosition(wxPoint(5, 25));
            this->lbPasswordResult->SetFont(wxFont(wxFontInfo().Bold(true)));
        } else {
            this->notebook->Hide();

            this->renderStorageRecords();
        }
    }
}
