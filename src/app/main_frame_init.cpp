#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#	include <wx/wx.h>
#endif
#include <secure-store.h>

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
    }

    BEGIN_EVENT_TABLE ( MainFrame, wxFrame )
        EVT_BUTTON ( BUTTON_PASSWORD_ENTER, MainFrame::OnPasswordEnter )
    END_EVENT_TABLE()

    void MainFrame::OnPasswordEnter( wxCommandEvent& event )
    {
        auto value = this->textPasswordCtrl->GetValue();
        int code = this->storage->open(new std::string(this->fileName), new std::string(value.c_str().AsChar()));

        if (code > 0) {
            this->lbPasswordResult->SetLabel("Error");
            this->lbPasswordResult->Show();
            this->lbPasswordResult->SetPosition(wxPoint(5, 25));
            this->lbPasswordResult->SetFont(wxFont(wxFontInfo().Bold(true)));
        } else {
            this->lbPasswordResult->Hide();
            this->textPasswordCtrl->Hide();
            this->btnPasswordEnter->Hide();

            this->renderStorageRecords();
        }
    }
}
