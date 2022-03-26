#include <secure-store.h>

#include <iostream>
#include <unistd.h>
#include <pwd.h>

#include <sys/types.h>
#include <sys/stat.h>

#include <memory.h>

int main(int argc, char** argv) {
    SecureStore::Config config(argc, argv);

    if (config.getFileName() != nullptr) {
        struct stat info;
        int code = stat(config.getFileName()->c_str(), &info);

        if (code != 0) {
            std::cout << "Cannot access: " << config.getFileName()->c_str() << std::endl;
            return 1;
        }

        if (info.st_mode & S_IFDIR) {
            std::cout << config.getFileName()->c_str() << " is not file" << std::endl;
            return 1;
        }

        std::cout << "Open file: " << config.getFileName()->c_str() << std::endl;
        std::cout << "Enter password: ";

        char pw[32] = {0};
        char *p = pw;
        FILE *fp = stdin;
        ssize_t nchr = 0;
        nchr = SecureStore::getpasswd(&p, 32, '*', fp);
        std::cout << std::endl;
        if (nchr == 0) {
            std::cout << "Empty password" << std::endl;
            return 1;
        }

        // open db
        std::string key = p;
        SecureStore::Storage::DB db;
        code = db.open(config.getFileName(), &key);

        if (code != 0) {
            std::cout << "Failed to open: " << config.getFileName()->c_str() << std::endl;
            return 1;
        }

        SecureStore::View::Application app(&db);
        app.run();

        return 0;
    }

    struct passwd *pw = getpwuid(getuid());

    const char *homedir = pw->pw_dir;

    std::cout << "Home dir: " << homedir << std::endl;

    int nLen = std::strlen(homedir) + 5; // homeDir + "/.sec"
    char* str = new char[nLen];
    memset(str, 0, nLen * sizeof(char));
    sprintf(str, "%s/.sec", homedir);

    struct stat info;

    if( stat( str, &info ) != 0 )
        printf( "cannot access %s\n", str );
    else if( info.st_mode & S_IFDIR )
        printf( "%s is a directory\n", str );
    else
        printf( "%s is no directory\n", str );

    return 0;
}
