#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#	include <wx/wx.h>
#endif
#include <secure-store.h>
#include <string>

namespace SecureStore::Application
{
    void MainFrame::OnClickCreateFile(wxCommandEvent &event)
    {
        auto sOpenDirectory = this->txOpenDirectory->GetValue();
        auto sFileName = this->txFileName->GetValue();
        int nPath = sOpenDirectory.size() + sFileName.size() + 2;
        INIT_CHAR_STRING(sPath, nPath)
        memcpy(sPath, sOpenDirectory.c_str().AsChar(), sOpenDirectory.size());
        int offset = sOpenDirectory.size();
        if (sPath[sOpenDirectory.size() - 1] != '/') {
            sPath[sOpenDirectory.size()] = '/';
            offset++;
        }
        memcpy(sPath + offset, sFileName.c_str().AsChar(), sFileName.size());

        auto sPassword = this->txPassword->GetValue();

        this->storage = new SecureStore::Storage::DB;
        this->storage->createEmpty();
        this->storage->save(new std::string(sPath), new std::string(sPassword.c_str().AsChar()));

        // clean up
        this->txOpenDirectory->SetValue(wxEmptyString);
        this->txFileName->SetValue(wxEmptyString);
        this->txPassword->SetValue(wxEmptyString);
    }
}
