#ifndef H_SECURE_STORE_APP_SHOW
#define H_SECURE_STORE_APP_SHOW

#include <wx/wx.h>
#include <wx/grid.h>
#include <secure-store/storage.h>

namespace SecureStore::Application
{
    class ShowFrame : public wxFrame
    {
    public:
        ShowFrame(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &pos, const wxSize &size, SecureStore::Storage::DB* storage);

        void OnSaveSecretClick(wxCommandEvent& event);
        void OnAddSecretClick(wxCommandEvent& event);
        void OnClickRemoveSecret(wxCommandEvent& event);
        void OnSelectItem(wxCommandEvent& event);

        void reloadContent();

        void renderStorageRecords();

        SecureStore::Storage::DB* storage;

    private:
        wxTreeListCtrl* treeRecords;
        wxGrid* grid;
        wxButton* btnSaveSecret;
        wxButton* btnAddSecret;
        wxButton* btnRemoveSecret;
        wxListBox* listSecrets;

        const char* fileName;

        int selectedSecretIndex;

        wxFrame* addSecretFrame;

        SecureStore::Storage::Record* getSelectedSecret();

        DECLARE_EVENT_TABLE()
    };
}

#endif
