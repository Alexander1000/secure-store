#include <iostream>
#include <unistd.h>
#include <pwd.h>

#include <sys/types.h>
#include <sys/stat.h>

#include <memory.h>

int main() {
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
