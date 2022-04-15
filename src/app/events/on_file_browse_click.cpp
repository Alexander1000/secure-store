#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#	include <wx/wx.h>
#endif
#include <secure-store.h>

namespace SecureStore::Application
{
    void MainFrame::OnFileBrowseClick(wxCommandEvent &event)
    {
        auto browseFile = new wxFileDialog;
        browseFile->ShowModal();
        auto sFileName = browseFile->GetFilename();
        this->txFilePath->SetValue(sFileName);
    }
}
