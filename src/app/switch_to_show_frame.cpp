#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#	include <wx/wx.h>
#endif
#include <secure-store.h>
#include <memory.h>

namespace SecureStore::Application
{
    void MainFrame::switchToShowFrame()
    {
        DEBUG_MESSAGE("MainFrame::switchToShowFrame <called>");

        auto showFrame = (ShowFrame*) this->getApp()->getShowFrame();
        showFrame->storage = this->storage;
        INIT_CHAR_STRING(sTitle, 15 + strlen(this->_fileName)); // "Secure store: " // 14
        sprintf(sTitle, "Secure store: %s", this->_fileName);
        showFrame->SetTitle(_(sTitle));
        showFrame->renderStorageRecords();
        showFrame->Show(true);
        this->getApp()->SetTopWindow(showFrame);
        this->getApp()->getMainFrame()->Close();
    }
}
