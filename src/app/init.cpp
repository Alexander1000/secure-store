#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#	include <wx/wx.h>
#endif
#include <secure-store.h>

namespace SecureStore::Application {

    IMPLEMENT_APP_NO_MAIN(MainApp) // A macro that tells wxWidgets to create an instance of our application

    bool MainApp::OnInit() {
        SecureStore::Config config(this->argc, this->argv);
        std::string title = "Secure store";

        if (config.getFileName() != nullptr) {
            title += ": ";
            title += config.getFileName()->c_str();
        }

        // Create an instance of our frame, or window
        MainFrame *MainWin = new MainFrame(_(title), wxDefaultPosition, wxSize(300, 200));
        MainWin->Show(true); // show the window
        SetTopWindow(MainWin); // and finally, set it as the main window
        return true;
    }
}
