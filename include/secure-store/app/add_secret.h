#ifndef H_SECURE_STORE_APP_ADD_SECRET
#define H_SECURE_STORE_APP_ADD_SECRET

#include <wx/wx.h>
#include <secure-store/storage.h>

namespace SecureStore::Application
{
    class AddSecretFrame : public wxFrame
    {
    public:
        AddSecretFrame(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &pos, const wxSize &size, SecureStore::Storage::DB* storage);

        void OnClickSaveButton(wxCommandEvent &event);
        void OnClickCancelButton(wxCommandEvent &event);

    private:
        SecureStore::Storage::DB* storage;

        wxButton* btnSave;
        wxButton* btnCancel;

        wxTextCtrl* txName;
        wxTextCtrl* txUser;
        wxTextCtrl* txPassword;
        wxTextCtrl* txComment;

        wxStaticText* lbName;
        wxStaticText* lbUser;
        wxStaticText* lbPassword;
        wxStaticText* lbComment;

        wxStaticText* lbTitleText;

        void initialize();

        DECLARE_EVENT_TABLE()
    };
}

#endif
