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
        this->fileName = nullptr;
        this->title = nullptr;

        SecureStore::Config config(this->argc, this->argv);
        std::string title = "Secure store";
        // const char* fileName = nullptr;

        if (config.getFileName() != nullptr) {
            title += ": ";
            title += config.getFileName()->c_str();
            this->fileName = (char*) config.getFileName()->c_str();
        }

        this->title = (char*) malloc(title.size() + 1);
        memset(this->title, 0, title.size() + 1);
        memcpy(this->title, title.c_str(), title.size());

        this->mainFrame = nullptr;

        this->mainFrame = new MainFrame(_(this->title), wxDefaultPosition, wxSize(600, 200), fileName, this);
        this->mainFrame->Show(true);
        this->SetTopWindow(this->mainFrame);

        this->showFrame = new ShowFrame(nullptr, wxID_ANY, _(title), wxDefaultPosition, wxSize(600, 200), nullptr);

        return true;
    }
}
