#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#	include <wx/wx.h>
#endif
#include <secure-store.h>

namespace SecureStore::Application
{
    void MainFrame::switchToShowFrame()
    {
        this->getApp()->mainFrame->Hide();
        auto showFrame = (ShowFrame*) this->getApp()->showFrame;
        showFrame->storage = this->storage;
        showFrame->renderStorageRecords();
        this->getApp()->showFrame->Show(true);
    }
}
