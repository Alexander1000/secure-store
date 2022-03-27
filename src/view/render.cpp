#include <secure-store.h>
#include <ncurses.h>

namespace SecureStore::View
{
    void Application::render()
    {
        TermSize size;
        this->termSize(&size);

        Point p1, p2;
        p1.x = 0;
        p1.y = 0;

        p2.x = size.cols - 1;
        p2.y = size.rows - 1;

        draw_rectangle(&p1, &p2);

        int rows = 1;
        for (auto & dbRecord : *this->db->getRecords()) {
            mvaddstr(rows, 1, dbRecord->getRecord()->getName()->c_str());
            rows++;
        }

        refresh();                   // Вывод приветствия на настоящий экран
    }
}
