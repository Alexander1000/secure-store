#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#	include <wx/wx.h>
#endif
#include <secure-store.h>

namespace SecureStore::Application
{
    void MainFrame::OnAddSecretClick(wxCommandEvent &event)
    {
        this->addSecretFrame = new AddSecretFrame(this, FRAME_ADD_SECRET, _T("Add secret"), wxDefaultPosition, wxSize(400, 200));
        this->addSecretFrame->CenterOnParent();
        this->addSecretFrame->Show(true);
    }
}
