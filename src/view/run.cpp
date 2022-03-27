#include <secure-store.h>

#include <iostream>
#include <ncurses.h>

namespace SecureStore::View
{
    int Application::run()
    {
        initscr();                   // Переход в curses-режим
        curs_set(0); // hide cursor
        keypad(stdscr, true);

        while (true) {
            clear();
            this->render();

            bool stop = false;

            switch (getch()) {
                case KEY_UP:
                    break;
                case KEY_DOWN:
                    break;
                default:
                    stop = true;
                    break;
            }

            if (stop) {
                break;
            }
        }

        getch();                     // Ожидание нажатия какой-либо клавиши пользователем

        endwin();                    // Выход из curses-режима. Обязательная команда.
        return 0;
    }
}
