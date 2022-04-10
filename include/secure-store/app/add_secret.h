#ifndef H_SECURE_STORE_APP_ADD_SECRET
#define H_SECURE_STORE_APP_ADD_SECRET

#include <wx/wx.h>

namespace SecureStore::Application
{
    class AddSecretFrame : public wxFrame
    {
    public:
        AddSecretFrame(const wxString &title, const wxPoint &pos, const wxSize &size);
    };
}

#endif
