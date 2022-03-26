#include <secure-store.h>

#include <sys/ioctl.h> //ioctl() and TIOCGWINSZ
#include <unistd.h> // for STDOUT_FILENO

namespace SecureStore::View
{
    void Application::termSize(TermSize* termSize)
    {
        struct winsize size;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
        termSize->rows = size.ws_row;
        termSize->cols = size.ws_col;
    }
}
