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
        DEBUG_MESSAGE("Event: MainFrame::OnPasswordEnter");

        auto passwordValue = this->textPasswordCtrl->GetValue();
        if (passwordValue.empty()) {
            this->lbPasswordResult->SetLabel("Empty password");
            this->lbPasswordResult->Show();
            return;
        }

        auto sPassword = passwordValue.c_str().AsChar();
        INIT_CHAR_STRING(sPasswordCopy, strlen(sPassword) + 1);
        memcpy(sPasswordCopy, sPassword, strlen(sPassword));

        auto userValue = this->txLogin->GetValue();
        if (userValue.empty()) {
            this->lbPasswordResult->SetLabel("Empty login");
            this->lbPasswordResult->Show();
            return;
        }

        auto sUser = userValue.c_str().AsChar();
        INIT_CHAR_STRING(sUserCopy, strlen(sUser) + 1);
        memcpy(sUserCopy, sUser, strlen(sUser));

        INIT_CHAR_STRING(sFileName, strlen(this->_fileName) + 1);
        memcpy(sFileName, this->_fileName, strlen(this->_fileName));

        int code = this->storage->open(sFileName, sUserCopy, sPasswordCopy);

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
