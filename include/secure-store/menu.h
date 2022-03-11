#ifndef H_SECURE_STORE_MENU
#define H_SECURE_STORE_MENU

#include <string>
#include <list>

namespace SecureStore
{
    class Menu
    {
    public:
        Menu();

    private:
        std::list<std::string>* elements;
    };
}

#endif
