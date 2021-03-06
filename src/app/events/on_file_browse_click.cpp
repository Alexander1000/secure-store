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
        auto browseFile = new wxFileDialog(this, _("Open XDB file"), "", "", "XDB files (*.xdb)|*.xdb", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
        browseFile->ShowModal();
        auto sFileName = browseFile->GetFilename();
        this->txFilePath->SetValue(browseFile->GetDirectory() + "/" + sFileName);
        this->setFileName(this->txFilePath->GetValue().c_str().AsChar());
    }
}
