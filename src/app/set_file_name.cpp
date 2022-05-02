#include <secure-store.h>
#include <memory.h>

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
