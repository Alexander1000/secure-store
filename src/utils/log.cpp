#include <secure-store.h>
#include <iostream>

namespace SecureStore
{
    void StdoutLogger::allocateMemory(const char* varName, int length)
    {
        std::cout << "[debug] allocate memory \"" << varName << "\" (size: " << length << " bytes)" << std::endl;
    }
}
