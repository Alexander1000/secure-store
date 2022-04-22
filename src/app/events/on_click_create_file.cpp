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
        auto sPassword = this->txPassword->GetValue();

        if (sOpenDirectory.empty() || sFileName.empty() || sPassword.empty()) {
            this->lbCreateNewFileError->SetLabel(_T("All fields is required"));
            this->lbCreateNewFileError->Show();
            return;
        }

        int nPath = sOpenDirectory.size() + sFileName.size() + 7; // add end-slash and .xdb extension (if not set)
        INIT_CHAR_STRING(sPath, nPath)
        memcpy(sPath, sOpenDirectory.c_str().AsChar(), sOpenDirectory.size());
        int offset = sOpenDirectory.size();
        if (sPath[sOpenDirectory.size() - 1] != '/') {
            sPath[sOpenDirectory.size()] = '/';
            offset++;
        }
        memcpy(sPath + offset, sFileName.c_str().AsChar(), sFileName.size());
        const char* sName = sFileName.c_str().AsChar();
        const char* sExt = ".xdb";
        if (sFileName.size() <= strlen(sExt)) {
            // minimal file name
            memcpy(sPath + offset + sFileName.size(), sExt, strlen(sExt));
        }
        // check extension exists
        bool extExists = true;
        for (int i = 0; i < strlen(sExt); i++) {
            if (sExt[i] != sName[strlen(sName) - strlen(sExt) + i]) {
                extExists = false;
                break;
            }
        }

        if (!extExists) {
            memcpy(sPath + offset + sFileName.size(), sExt, strlen(sExt));
        }

        this->storage = new SecureStore::Storage::DB;
        this->storage->createEmpty();
        this->storage->save(new std::string(sPath), new std::string(sPassword.c_str().AsChar()));

        this->fileName = sPath;

        // clean up
        this->txOpenDirectory->SetValue(wxEmptyString);
        this->txFileName->SetValue(wxEmptyString);
        this->txPassword->SetValue(wxEmptyString);

        this->switchToShowFrame();
    }
}
