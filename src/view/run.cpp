#include <secure-store.h>

#include <iostream>

namespace SecureStore::View
{
    void Application::run()
    {
        // run application
        TermSize size;
        this->termSize(&size);
        std::cout << "Cols: " << size.cols << "; rows: " << size.rows << std::endl;
    }
}
