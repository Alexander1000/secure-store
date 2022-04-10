#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#	include <wx/wx.h>
#endif
#include <secure-store.h>
#include <memory>

namespace SecureStore::Application
{
    MainFrame::MainFrame(const wxString &title, const wxPoint &pos, const wxSize &size, const char* fileName)
        : wxFrame((wxFrame *) NULL, -1, title, pos, size)
    {
        this->fileName = fileName;

        this->storage = new SecureStore::Storage::DB;

        this->btnPasswordEnter = new wxButton(this, BUTTON_PASSWORD_ENTER, _T("Enter"), wxPoint(110, 5), wxDefaultSize, 0);

        this->textPasswordCtrl = new wxTextCtrl(this, TEXT_PASSWORD_Entry, _T(""), wxPoint(5, 5), wxSize(100, 20), wxTE_PASSWORD, wxDefaultValidator);

        this->lbPasswordResult = new wxStaticText(this, STATIC_TEXT_PASSWORD_RESULT, wxEmptyString);
        this->lbPasswordResult->Hide();

        // db records page
        this->treeRecords = nullptr;
        this->grid = nullptr;
        this->btnSaveSecret = nullptr;
        this->btnAddSecret = nullptr;

        // add secret frame
        this->addSecretFrame = nullptr;

        this->selectedSecretIndex = -1;
    }
}
