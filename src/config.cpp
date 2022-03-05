#include <secure-store.h>

#include <unistd.h>
#include <pwd.h>

namespace SecureStore
{
    Config::Config()
    {
        this->initialize();
    }

    void Config::initialize()
    {
    }

    const char* Config::getHomeDir()
    {
        struct passwd *pw = getpwuid(getuid());
        const char *homedir = pw->pw_dir;
        return homedir;
    }
}
