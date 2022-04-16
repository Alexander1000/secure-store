#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#	include <wx/wx.h>
#endif
#include <secure-store.h>
#include <string>

namespace SecureStore::Application
{
    void MainFrame::OnFileBrowseClick(wxCommandEvent &event)
    {
        auto browseFile = new wxFileDialog;
        browseFile->ShowModal();
        auto sFileName = browseFile->GetFilename();
        this->txFilePath->SetValue(browseFile->GetDirectory() + "/" + sFileName);
        std::string *fName = nullptr;
        fName = new std::string(this->txFilePath->GetValue().utf8_string().c_str());
        this->fileName = fName->c_str();
    }
}
