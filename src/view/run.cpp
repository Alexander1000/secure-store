#include <secure-store.h>

#include <iostream>
#include <ncurses.h>

namespace SecureStore::View
{
    void Application::run()
    {
        initscr();                   // Переход в curses-режим
        printw("Hello world!\n");  // Отображение приветствия в буфер
        refresh();                   // Вывод приветствия на настоящий экран
        getch();                     // Ожидание нажатия какой-либо клавиши пользователем
        endwin();                    // Выход из curses-режима. Обязательная команда.
        TermSize size;
        this->termSize(&size);
        std::cout << "Cols: " << size.cols << "; rows: " << size.rows << std::endl;
    }
}
