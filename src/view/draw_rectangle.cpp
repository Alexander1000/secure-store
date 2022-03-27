#include <secure-store.h>
#include <ncurses.h>

namespace SecureStore::View
{
    void draw_rectangle(Point* p1, Point* p2)
    {
        for (unsigned short i = p1->x; i <= p2->x; i++) {
            mvaddch(p1->y, i, '-');
            mvaddch(p2->y, i, '-');
        }

        for (unsigned short i = p1->y; i <= p2->y; i++) {
            mvaddch(i, p1->x, '|');
            mvaddch(i, p2->x, '|');
        }
    }
}
