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
        // main window form controls
        TREE_DB_RECORDS,
        DB_GRID,
        BUTTON_ADD_SECRET,
        BUTTON_SAVE_SECRET,
        // add secret form controls
        FRAME_ADD_SECRET,
        F_AS_BTN_SAVE,
        F_AS_BTN_CANCEL,
        F_AS_TX_NAME,
        F_AS_TX_USER,
        F_AS_TX_PASSWORD,
        F_AS_TX_COMMENT,
        F_AS_LB_NAME,
        F_AS_LB_USER,
        F_AS_LB_PASSWORD,
        F_AS_LB_COMMENT,
        F_AS_LB_TITLE_TEXT,
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

        void reloadContent();

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

        wxFrame* addSecretFrame;

        void renderStorageRecords();

        SecureStore::Storage::Record* getSelectedSecret();

        DECLARE_EVENT_TABLE()
    };

    DECLARE_APP(MainApp)
}

#endif
