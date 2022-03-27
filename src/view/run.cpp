#include <secure-store.h>

#include <iostream>
#include <ncurses.h>

namespace SecureStore::View
{
    int Application::run()
    {
        initscr();                   // Переход в curses-режим

        TermSize size;
        this->termSize(&size);

        Point p1, p2;
        p1.x = 0;
        p1.y = 0;

        p2.x = size.cols - 1;
        p2.y = size.rows - 1;

        draw_rectangle(&p1, &p2);

        curs_set(0); // hide cursor

        int cols = 1;
        for (auto & dbRecord : *this->db->getRecords()) {
            mvaddstr(cols, 1, dbRecord->getRecord()->getName()->c_str());
            cols++;
        }

        refresh();                   // Вывод приветствия на настоящий экран
        getch();                     // Ожидание нажатия какой-либо клавиши пользователем
        endwin();                    // Выход из curses-режима. Обязательная команда.
        std::cout << "Cols: " << size.cols << "; rows: " << size.rows << std::endl;
        return 0;
    }
}
