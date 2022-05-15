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

        const char* sExt = ".xdb";
        const char dirSep = '/';

        int nPath = sOpenDirectory.size() + sizeof(dirSep) + sFileName.size() + strlen(sExt) + 1; // add end-slash and .xdb extension (if not set)
        INIT_CHAR_STRING(sPath, nPath)
        memcpy(sPath, sOpenDirectory.c_str().AsChar(), sOpenDirectory.size());
        int offset = sOpenDirectory.size();
        if (sPath[sOpenDirectory.size() - 1] != dirSep) {
            sPath[sOpenDirectory.size()] = dirSep;
            offset++;
        }
        memcpy(sPath + offset, sFileName.c_str().AsChar(), sFileName.size());
        const char* sName = sFileName.c_str().AsChar();
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

        INIT_CHAR_STRING(sPasswordCopy, sPassword.length() + 1);
        memcpy(sPasswordCopy, sPassword.c_str().AsChar(), sPassword.length());

        this->storage = new SecureStore::Storage::DB;
        this->storage->createEmpty();
        this->storage->save(sPath, sPasswordCopy);

        this->setFileName(sPath);

        // clean up
        this->txOpenDirectory->SetValue(wxEmptyString);
        this->txFileName->SetValue(wxEmptyString);
        this->txPassword->SetValue(wxEmptyString);

        this->switchToShowFrame();
    }
}
