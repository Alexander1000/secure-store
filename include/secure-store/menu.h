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

        void addElement(const char*);

    private:
        std::list<std::string>* elements;
    };
}

#endif
