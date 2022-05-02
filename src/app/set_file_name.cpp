#include <secure-store.h>
#include <memory.h>

namespace SecureStore::Application
{
    void MainFrame::setFileName(const char* fileName)
    {
        if (this->_fileName != nullptr) {
            free((void*) this->_fileName);
        }

        this->_fileName = (const char*) malloc(strlen(fileName) + 1);
        memset((void*) this->_fileName, 0, strlen(fileName) + 1);
        memcpy((void*) this->_fileName, fileName, strlen(fileName));
    }
}
