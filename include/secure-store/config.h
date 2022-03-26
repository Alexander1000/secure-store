#ifndef H_SECURE_STORE_CONFIG
#define H_SECURE_STORE_CONFIG

#include <string>

namespace SecureStore
{
    class Config
    {
    public:
        Config(int argc, char** argv);
        std::string* getFileName();
    private:
        std::string* fileName;

        void initialize();
        void loadConfig(const char*);
        const char* getHomeDir();
    };
}

#endif
