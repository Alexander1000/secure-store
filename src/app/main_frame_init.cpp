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
    MainFrame::MainFrame(const wxString &title, const wxPoint &pos, const wxSize &size, const char* fileName, MainApp* app)
        : wxFrame((wxFrame *) NULL, -1, title, pos, size)
    {
        this->app = app;
        this->fileName = fileName;

        this->storage = new SecureStore::Storage::DB;

        int xMargin = 7;
        int yMargin = 7;

        this->notebook = new wxNotebook(this, wxID_ANY);
        this->notebook->AddPage(this->getPanelOpenFile(this->notebook), "Open");
        this->notebook->AddPage(this->getPanelNewFile(this->notebook), "New");
        this->notebook->SetSize(wxSize(this->GetSize().GetWidth() - xMargin * 2, this->GetSize().GetHeight() - yMargin * 2));

        if (fileName != nullptr) {
            this->txFilePath->SetValue(wxString(fileName));
        }
    }
}
