#include "projectile.hpp"

Projectile::Projectile(int startX, int startY)
{
	x = startX;
	y = startY;
	symbol = '*'; // vertical bullet
}

void Projectile::update()
{
	y--; // move up by 1 cell every frame
}

void Projectile::draw(WINDOW *win)
{
	mvwaddch(win, y, x, symbol);
}

bool Projectile::isOffScreen() const
{
	return (y < 1); // off top of window
}
