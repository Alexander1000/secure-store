#include <secure-store.h>
#include <iostream>
#include <io-buffer.h>

namespace SecureStore
{
    void StdoutLogger::allocateMemory(const char* varName, int length)
    {
        std::cout << "[debug] allocate memory \"" << varName << "\" (size: " << length << " bytes)" << std::endl;
    }

    void StdoutLogger::freeMemory(const char *varName)
    {
        std::cout << "[debug] free memory \"" << varName << "\"" << std::endl;
    }

    FileLogger::FileLogger(const char *fileName)
    {
        this->fileWriter = new IOBuffer::IOFileWriter(fileName);
    }

    void FileLogger::allocateMemory(const char *varName, int length)
    {
        char* result = (char*) malloc(1024);
        memset(result, 0, 1024);
        sprintf(result, "[debug] allocate memory \"%s\" (size: %d)\n", varName, length);
        this->fileWriter->write(result, strlen(result));
        free(result);
    }

    void FileLogger::freeMemory(const char *varName)
    {
        char* result = (char*) malloc(1024);
        memset(result, 0, 1024);
        sprintf(result, "[debug] free memory \"%s\"\n", varName);
        this->fileWriter->write(result, strlen(result));
        free(result);
    }
}
