#ifndef H_SECURE_STORE_CONFIG
#define H_SECURE_STORE_CONFIG

namespace SecureStore
{
    class Config
    {
    public:
        Config();
    private:
        void initialize();
        void loadConfig(const char*);
        const char* getHomeDir();
    };
}

#endif
