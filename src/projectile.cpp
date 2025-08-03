#include "projectile.hpp"

Projectile::Projectile(int startX, int startY, int deltaX, int deltaY)
{
    x = startX;
    y = startY;
    dx = deltaX;
    dy = deltaY;
    symbol = '|';  // or whatever symbol you prefer
}

void Projectile::update() {
    x += dx;
    y += dy;
}

void Projectile::draw(WINDOW *win)
{
	mvwaddch(win, y, x, symbol);
}

bool Projectile::isOffScreen() const
{
	return (y < 1); // off top of window
}
