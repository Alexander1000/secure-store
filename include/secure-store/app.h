#ifndef H_SECURE_STORE_APP
#define H_SECURE_STORE_APP

#include <secure-store/storage.h>
#include <wx/wx.h>
#include <wx/treelist.h>
#include <wx/grid.h>

namespace SecureStore::Application
{
    enum
    {
        BUTTON_PASSWORD_ENTER = wxID_HIGHEST + 1, // declares an id which will be used to call our button
        TEXT_PASSWORD_Entry,
        STATIC_TEXT_PASSWORD_RESULT,
        TREE_DB_RECORDS,
        DB_GRID,
        BUTTON_ADD_SECRET,
        BUTTON_SAVE_SECRET,
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
        void OnChoiceSecret(wxTreeListEvent& event);
        void OnSaveSecretClick(wxCommandEvent& event);
        void OnAddSecretClick(wxCommandEvent& event);

    private:
        // auth page
        wxButton* btnPasswordEnter;
        wxTextCtrl* textPasswordCtrl;
        wxStaticText* lbPasswordResult;

        // db page:
        wxTreeListCtrl* treeRecords;
        wxGrid* grid;
        wxButton* btnSaveSecret;
        wxButton* btnAddSecret;

        const char* fileName;

        SecureStore::Storage::DB* storage;

        int selectedSecretIndex;

        void renderStorageRecords();

        SecureStore::Storage::Record* getSelectedSecret();

        DECLARE_EVENT_TABLE()
    };

    DECLARE_APP(MainApp)
}

#endif
