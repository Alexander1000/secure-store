#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#	include <wx/wx.h>
#endif
#include <secure-store.h>
#include <string>

namespace SecureStore::Application
{
    void MainFrame::OnClickSelectDirectory(wxCommandEvent &event)
    {
        auto browseDirectory = new wxDirDialog;
        browseDirectory->ShowModal();
        auto path = browseDirectory->GetPath();
        if (path.empty()) {
            this->txOpenDirectory->SetValue(wxEmptyString);
        } else {
            this->txOpenDirectory->SetValue(path);
        }
        delete browseDirectory;
    }
}
