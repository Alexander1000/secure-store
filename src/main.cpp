#include <iostream>
#include <unistd.h>
#include <pwd.h>

int main() {
    struct passwd *pw = getpwuid(getuid());

    const char *homedir = pw->pw_dir;

    std::cout << "Home dir: " << homedir << std::endl;

    return 0;
}
