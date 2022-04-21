#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#	include <wx/wx.h>
#endif
#include <secure-store.h>

namespace SecureStore::Application
{
    void MainFrame::switchToShowFrame()
    {
        this->getApp()->getMainFrame()->Hide();
        this->getApp()->getMainFrame()->Close();
        auto showFrame = (ShowFrame*) this->getApp()->getShowFrame();
        showFrame->storage = this->storage;
        showFrame->SetTitle(_(this->fileName));
        showFrame->renderStorageRecords();
        showFrame->Show(true);
    }
}
