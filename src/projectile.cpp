#include "projectile.hpp"
#include <ncurses.h>

Projectile::Projectile(int startX, int startY, int deltaX, int deltaY)
    : x(startX), y(startY), dx(deltaX), dy(deltaY), symbol('|')
{
}

void Projectile::update() {
    x += dx;
    y += dy;
}

void Projectile::draw(WINDOW* win)
{
    int max_y, max_x;
    getmaxyx(win, max_y, max_x);
    if (y >= 0 && y < max_y && x >= 0 && x < max_x)
        mvwaddch(win, y, x, symbol);
}

bool Projectile::isOffScreen(int maxY) const
{
    return (y < 1) || (y >= maxY - 1); // off top or bottom
}
