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

        this->selectedSecretIndex = -1;
    }

    BEGIN_EVENT_TABLE ( MainFrame, wxFrame )
        EVT_BUTTON ( BUTTON_PASSWORD_ENTER, MainFrame::OnPasswordEnter )
        EVT_TREELIST_SELECTION_CHANGED(TREE_DB_RECORDS, MainFrame::OnChoiceSecret)
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

    void MainFrame::OnChoiceSecret(wxTreeListEvent &event)
    {
        int index = 0;
        auto treeItem = this->treeRecords->GetFirstItem();
        do {
            if (treeItem.IsOk()) {
                if (this->treeRecords->IsSelected(treeItem)) {
                    break;
                }
            }

            index++;
            treeItem = this->treeRecords->GetNextItem(treeItem);
        } while (treeItem.IsOk());

        this->selectedSecretIndex = index;

        SecureStore::Storage::Record* secret = nullptr;

        index = 0;
        for (auto & it : *this->storage->getRecords()) {
            auto record = it->getRecord();
            if (index == this->selectedSecretIndex) {
                secret = record;
                break;
            }
            index++;
        }

        if (secret == nullptr) {
            return;
        }

        this->grid->SetCellValue(0, 0, "ID");
        char* strId = (char*) malloc(10);
        memset(strId, 0, 10 * sizeof(char));
        sprintf(strId, "%d", secret->getId());
        this->grid->SetCellValue(0, 1, wxString(strId));
        free(strId);
        this->grid->SetCellValue(1, 0, "Name");
        this->grid->SetCellValue(1, 1, wxString(*secret->getName()));
        this->grid->SetCellValue(2, 0, "User");
        if (secret->getUser() != nullptr) {
            this->grid->SetCellValue(2, 1, wxString(*secret->getUser()));
        }
        this->grid->SetCellValue(3, 0, "Password");
        if (secret->getPassword() != nullptr) {
            this->grid->SetCellValue(3, 1, wxString(*secret->getPassword()));
        }
        this->grid->SetCellValue(4, 0, "Comment");
        if (secret->getComment() != nullptr) {
            this->grid->SetCellValue(4, 1, wxString(*secret->getComment()));
        }
        this->grid->SetCellValue(5, 0, "Create Time");
    }
}
