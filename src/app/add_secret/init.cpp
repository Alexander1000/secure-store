#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#	include <wx/wx.h>
#endif
#include <secure-store.h>
#include <memory>

namespace SecureStore::Application
{
    AddSecretFrame::AddSecretFrame(const wxString &title, const wxPoint &pos, const wxSize &size)
            : wxFrame((wxFrame *) NULL, -1, title, pos, size)
    {
        // initialize frame controls
    }
}
