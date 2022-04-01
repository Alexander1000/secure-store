#include <secure-store.h>

#include <unistd.h>
#include <pwd.h>

#include <iostream>
#include <sys/stat.h>

#include <memory.h>

#include <fstream>

namespace SecureStore
{
    Config::Config(int argc, char **argv)
    {
        this->fileName = nullptr;
        this->console = false;

        for (int i = 1; i < argc; i++) {
            std::string paramName(argv[i]);

            if ((paramName == "-f" || paramName == "--file") && i + 1 < argc) {
                this->fileName = new std::string(argv[i+1]);
                i++;
                continue;
            }

            if (paramName == "--console") {
                this->console = true;
                continue;
            }
        }

        if (argc == 1) {
            this->initialize();
        }
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

        nLen += 7; // nLen + "/config"
        char* configFile = new char[nLen];
        memset(configFile, 0, nLen * sizeof(char));
        sprintf(configFile, "%s/config", str);

        struct stat configInfo;

        if (stat(configFile, &configInfo) != 0) {
            std::fstream fs;
            fs.open(configFile, std::ios_base::out);
            fs.close();
        } else if (configInfo.st_mode & S_IFDIR) {
            printf("%s is a directory\n", configFile);
            return;
        } else {
            printf("%s is no directory\n", configFile);
        }

        printf("%s file exists, begin configure it\n", configFile);

        this->loadConfig(configFile);
    }

    const char* Config::getHomeDir()
    {
        struct passwd *pw = getpwuid(getuid());
        const char *homedir = pw->pw_dir;
        return homedir;
    }

    std::string* Config::getFileName()
    {
        return this->fileName;
    }

    bool Config::isConsole()
    {
        return this->console;
    }
}
