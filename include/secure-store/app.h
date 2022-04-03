#ifndef H_SECURE_STORE_APP
#define H_SECURE_STORE_APP

#include <secure-store/storage.h>
#include <wx/wx.h>

namespace SecureStore::Application {
    enum
    {
        BUTTON_PASSWORD_ENTER = wxID_HIGHEST + 1, // declares an id which will be used to call our button
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
        MainFrame(const wxString &title, const wxPoint &pos, const wxSize &size, const char* fileName);
        void OnPasswordEnter( wxCommandEvent& event );

    private:
        wxButton* btnPasswordEnter;
        wxTextCtrl* textPasswordCtrl;

        const char* fileName;

        SecureStore::Storage::DB* storage;

        DECLARE_EVENT_TABLE()
    };

    DECLARE_APP(MainApp)
}

#endif
