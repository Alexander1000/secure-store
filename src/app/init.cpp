#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#	include <wx/wx.h>
#endif
#include <secure-store.h>
#include <memory>

namespace SecureStore::Application {

    IMPLEMENT_APP_NO_MAIN(MainApp)

    bool MainApp::OnInit()
    {
        this->title = nullptr;

        this->mainFrame = nullptr;
        this->showFrame = nullptr;

        std::string title = "Secure store";

        this->title = (char*) malloc(title.size() + 1);
        memset(this->title, 0, title.size() + 1);
        memcpy(this->title, title.c_str(), title.size());

        auto mainFrame = this->getMainFrame();
        mainFrame->Show(true);
        this->SetTopWindow(mainFrame);

        return true;
    }

    wxFrame* MainApp::getMainFrame()
    {
        if (this->mainFrame != nullptr) {
            return this->mainFrame;
        }

        auto szMainFrame = new wxSize(600, 220);
        this->mainFrame = new MainFrame(_(this->title), wxDefaultPosition, *szMainFrame, this);

        return this->mainFrame;
    }

    wxFrame* MainApp::getShowFrame()
    {
        if (this->showFrame != nullptr) {
            return this->showFrame;
        }

        auto szShowFrame = new wxSize(600, 200);
        this->showFrame = new ShowFrame(nullptr, wxID_ANY, _(this->title), wxDefaultPosition, *szShowFrame, nullptr);

        return this->showFrame;
    }
}
