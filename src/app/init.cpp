#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#	include <wx/wx.h>
#endif
#include <secure-store.h>

namespace SecureStore::Application {

    IMPLEMENT_APP_NO_MAIN(MainApp)

    bool MainApp::OnInit()
    {
        SecureStore::Config config(this->argc, this->argv);
        std::string title = "Secure store";
        const char* fileName = nullptr;

        if (config.getFileName() != nullptr) {
            title += ": ";
            title += config.getFileName()->c_str();
            fileName = config.getFileName()->c_str();
        }

        this->mainFrame = new MainFrame(_(title), wxDefaultPosition, wxSize(600, 200), fileName, this);
        this->mainFrame->Show(true);
        this->SetTopWindow(this->mainFrame);

        this->showFrame = new ShowFrame(nullptr, wxID_ANY, _(title), wxDefaultPosition, wxSize(600, 200), nullptr);

        return true;
    }
}
