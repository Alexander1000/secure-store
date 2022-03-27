#include <secure-store.h>

#include <iostream>
#include <ncurses.h>

namespace SecureStore::View
{
    int Application::run()
    {
        initscr();                   // Переход в curses-режим
        curs_set(0); // hide cursor
        this->render();

        getch();                     // Ожидание нажатия какой-либо клавиши пользователем

        endwin();                    // Выход из curses-режима. Обязательная команда.
        return 0;
    }
}
