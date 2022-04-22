#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#	include <wx/wx.h>
#endif
#include <secure-store.h>

namespace SecureStore::Application
{
    void ShowFrame::OnChoiceSecret(wxTreeListEvent &event)
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

        SecureStore::Storage::Record* secret = this->getSelectedSecret();

        if (secret == nullptr) {
            this->btnRemoveSecret->Hide();
            return;
        }

        this->btnRemoveSecret->Show();

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
        char* strCreateTime = (char*) malloc(16 * sizeof(char));
        memset(strCreateTime, 0, sizeof(char) * 16);
        sprintf(strCreateTime, "%llu", secret->getCreateTime());
        this->grid->SetCellValue(5, 1, wxString(strCreateTime));
    }
}
