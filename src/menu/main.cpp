#include <secure-store.h>

#include <string>
#include <list>

namespace SecureStore
{
    Menu::Menu()
    {
        this->elements = new std::list<std::string>;
    }

    void Menu::addElement(const char *pElement)
    {
        this->elements->push_back(pElement);
    }
}
