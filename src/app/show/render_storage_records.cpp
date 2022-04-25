#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#	include <wx/wx.h>
#endif
#include <secure-store.h>
#include <wx/grid.h>

namespace SecureStore::Application
{
    void ShowFrame::renderStorageRecords()
    {
        int xMargin = 7;
        int yMargin = 7;

        this->SetSize(800, 600);

        this->listSecrets = new wxListBox(this, F_SHOW_LIST_SECRETS);
        this->listSecrets->SetPosition(wxPoint(xMargin, yMargin));
        this->listSecrets->SetSize(wxSize(300, 200));

        for (auto & dbRecord : *this->storage->getRecords()) {
            auto secret = dbRecord->getRecord();
            wxString name(secret->getName()->c_str());
            this->listSecrets->Append(name);
        }

        this->grid = new wxGrid(this, DB_GRID);
        this->grid->SetPosition(wxPoint(xMargin + this->listSecrets->GetSize().GetWidth() + xMargin, yMargin));
        this->grid->SetSize(wxSize(500 - xMargin * 3, 200));
        this->grid->CreateGrid(10, 2);
        this->grid->HideColLabels();
        this->grid->HideRowLabels();
        this->grid->SetColSize(0, 150 - xMargin);
        this->grid->SetColSize(1, 350 - xMargin * 2);

        this->btnAddSecret = new wxButton(this, BUTTON_ADD_SECRET, _T("Add"), wxPoint(600, 200), wxSize(100, 20));
        this->btnSaveSecret = new wxButton(this, BUTTON_SAVE_SECRET, _T("Save"), wxPoint(700, 200), wxSize(100, 20));
        this->btnRemoveSecret = new wxButton(this, F_SHOW_BTN_REMOVE_SECRET, _T("Remove"));
        this->btnRemoveSecret->SetPosition(wxPoint(
            this->grid->GetPosition().x,
            this->grid->GetPosition().y + this->grid->GetSize().GetHeight() + yMargin
        ));
        this->btnRemoveSecret->Hide();
    }
}
