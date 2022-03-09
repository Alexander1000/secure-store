#include <secure-store.h>

#include <unistd.h>
#include <pwd.h>

#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>

#include <memory.h>

namespace SecureStore
{
    Config::Config()
    {
        this->initialize();
    }

    void Config::initialize()
    {
        const char* homedir = this->getHomeDir();
        int nLen = std::strlen(homedir) + 5; // homeDir + "/.sec"
        char* str = new char[nLen];
        memset(str, 0, nLen * sizeof(char));
        sprintf(str, "%s/.sec", homedir);

        struct stat info;

        if (stat(str, &info) != 0) {
            mkdir(str, 0777);
        } else if (info.st_mode & S_IFDIR) {
            printf("%s is a directory\n", str);
        } else {
            printf("%s is no directory\n", str);
            return;
        }
    }

    const char* Config::getHomeDir()
    {
        struct passwd *pw = getpwuid(getuid());
        const char *homedir = pw->pw_dir;
        return homedir;
    }
}
