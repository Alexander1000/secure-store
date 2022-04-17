#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#	include <wx/wx.h>
#endif
#include <secure-store.h>
#include <memory>
#include <wx/notebook.h>
#include <wx/panel.h>

namespace SecureStore::Application
{
    MainFrame::MainFrame(const wxString &title, const wxPoint &pos, const wxSize &size, const char* fileName)
        : wxFrame((wxFrame *) NULL, -1, title, pos, size)
    {
        this->fileName = fileName;

        this->storage = new SecureStore::Storage::DB;

        int xMargin = 7;
        int yMargin = 7;

        this->notebook = new wxNotebook(this, wxID_ANY);
        this->notebook->AddPage(this->getPanelOpenFile(this->notebook), "Open");
        auto pageNewFile = new wxPanel(this->notebook);
        this->notebook->AddPage(pageNewFile, "New");
        this->notebook->SetSize(wxSize(this->GetSize().GetWidth() - xMargin * 2, this->GetSize().GetHeight() - yMargin * 2));

        // db records page
        this->treeRecords = nullptr;
        this->grid = nullptr;
        this->btnSaveSecret = nullptr;
        this->btnAddSecret = nullptr;

        // add secret frame
        this->addSecretFrame = nullptr;

        this->selectedSecretIndex = -1;

        if (fileName != nullptr) {
            this->txFilePath->SetValue(wxString(fileName));
        }
    }
}
