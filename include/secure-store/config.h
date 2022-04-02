#ifndef H_SECURE_STORE_CONFIG
#define H_SECURE_STORE_CONFIG

#include <string>
#include <wx/wx.h>

namespace SecureStore
{
    class Config
    {
    public:
        Config(int argc, char** argv);
        Config(int argc, wxArrayString* wxArrayString);
        std::string* getFileName();
        bool isConsole();
    private:
        std::string* fileName;
        bool console;

        void initialize();
        void loadConfig(const char*);
        const char* getHomeDir();
    };
}

#endif
