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
        if (value.empty()) {
            this->lbPasswordResult->SetLabel("Empty password");
            this->lbPasswordResult->Show();
            return;
        }

        int code = this->storage->open(new std::string(this->fileName), new std::string(value.c_str().AsChar()));

        if (code > 0) {
            this->lbPasswordResult->SetLabel("Error");
            this->lbPasswordResult->Show();
        } else {
            this->notebook->Hide();
            this->lbPasswordResult->Hide();
            this->renderStorageRecords();
        }
    }
}
