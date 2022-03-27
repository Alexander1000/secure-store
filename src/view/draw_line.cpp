#include <secure-store.h>
#include <ncurses.h>

namespace SecureStore::View
{
    void draw_line(Point* p1, Point* p2)
    {
        if (p1->x != p2->x) {
            for (unsigned short i = p1->x; i <= p2->x; i++) {
                mvaddch(p1->y, i, '-');
            }
        }

        if (p1->y != p2->y) {
            for (unsigned short i = p1->y; i <= p2->y; i++) {
                mvaddch(i, p1->x, '|');
            }
        }
    }
}
