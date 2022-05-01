#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#	include <wx/wx.h>
#endif
#include <secure-store.h>
#include <memory.h>
#include <wx/notebook.h>
#include <wx/panel.h>

namespace SecureStore::Application
{
    void MainFrame::setFileName(const char* fileName)
    {
        if (this->fileName != nullptr) {
            free((void*) this->fileName);
        }

        this->fileName = (const char*) malloc(strlen(fileName) + 1);
        memset((void*) this->fileName, 0, strlen(fileName) + 1);
        memcpy((void*) this->fileName, fileName, strlen(fileName));
    }
}
