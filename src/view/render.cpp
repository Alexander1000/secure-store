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

        unsigned short breakLineX = (p2.x - p1.x) >> 1;
        p1.x = breakLineX;
        p1.y = 1;
        p2.x = breakLineX;
        p2.y = size.rows - 2;
        draw_line(&p1, &p2);

        SecureStore::Storage::Record* selectedRecord = nullptr;

        int rows = 1;
        for (auto & dbRecord : *this->db->getRecords()) {
            if (this->currentRow + 1 == rows) {
                mvaddstr(rows, 1, "-> ");
                selectedRecord = dbRecord->getRecord();
            }
            mvaddstr(rows, 4, dbRecord->getRecord()->getName()->c_str());
            rows++;
        }

        if (selectedRecord != nullptr) {
            mvprintw(1, breakLineX + 1, "ID: %d", selectedRecord->getId());
            mvprintw(2, breakLineX + 1, "Name: %s", selectedRecord->getName()->c_str());
            if (selectedRecord->getComment() != nullptr) {
                mvprintw(3, breakLineX + 1, "Comment: %s", selectedRecord->getComment()->c_str());
            }
        }

        refresh();                   // Вывод приветствия на настоящий экран
    }
}
