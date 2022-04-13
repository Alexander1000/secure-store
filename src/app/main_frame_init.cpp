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

        int xMargin = 7;
        int yMargin = 7;

        int yOffset = 0;

        this->lbFileBrowse = new wxStaticText(this, F_AUTH_LB_FILE_BROWSE, _T("File:"), wxPoint(xMargin, yMargin));
        this->txFilePath = new wxTextCtrl(this, F_AUTH_TX_FILE_PATH, wxEmptyString, wxPoint(xMargin + this->lbFileBrowse->GetSize().GetWidth() + xMargin, yMargin));

        yOffset = yMargin + 30;
        this->lbPasswordEnter = new wxStaticText(this, F_AUTH_LB_PASSWORD, _T("Password:"), wxPoint(xMargin, yOffset));
        this->textPasswordCtrl = new wxTextCtrl(
            this,
            TEXT_PASSWORD_Entry,
            _T(""),
            wxPoint(xMargin + this->lbPasswordEnter->GetSize().GetWidth() + xMargin, yOffset),
            wxSize(100, 20),
            wxTE_PASSWORD,
            wxDefaultValidator
        );
        this->btnPasswordEnter = new wxButton(
            this,
            BUTTON_PASSWORD_ENTER,
            _T("Enter"),
            wxPoint(this->textPasswordCtrl->GetPosition().x + this->textPasswordCtrl->GetSize().GetWidth() + xMargin, yOffset),
            wxDefaultSize,
            0
        );

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
