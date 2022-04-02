#ifndef H_SECURE_STORE_APP
#define H_SECURE_STORE_APP

#include <wx/wx.h>

namespace SecureStore::Application {
    enum
    {
        BUTTON_Hello = wxID_HIGHEST + 1, // declares an id which will be used to call our button
        TEXT_PASSWORD_Entry
    };

    class MainApp : public wxApp // MainApp is the class for our application
    {
        // MainApp just acts as a container for the window, or frame in MainFrame
    public:
        virtual bool OnInit();
    };

    class MainFrame : public wxFrame // MainFrame is the class for our window,
    {
        // It contains the window and all objects in it
    public:
        MainFrame(const wxString &title, const wxPoint &pos, const wxSize &size);
        wxButton* helloWorld;
        wxTextCtrl* textPasswordCtrl;
        void OnExit( wxCommandEvent& event );

        DECLARE_EVENT_TABLE()
    };

    DECLARE_APP(MainApp)
}

#endif
