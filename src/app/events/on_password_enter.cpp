#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#	include <wx/wx.h>
#endif
#include <secure-store.h>
#include <memory.h>

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

        auto sPassword = value.c_str().AsChar();
        INIT_CHAR_STRING(sPasswordCopy, strlen(sPassword) + 1);
        memcpy(sPasswordCopy, sPassword, strlen(sPassword));
        int code = this->storage->open(this->_fileName, sPasswordCopy);

        if (code > 0) {
            this->lbPasswordResult->SetLabel("Error");
            this->lbPasswordResult->Show();
        } else {
            this->notebook->Hide();
            this->lbPasswordResult->Hide();
            this->switchToShowFrame();
        }
    }
}
