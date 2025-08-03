#pragma once
#include <ncurses.h>

class GameEntity
{
  protected:
	int x;
	int y;
	char symbol;

  public:
	GameEntity(int x = 0, int y = 0, char symbol = ' ') : x(x), y(y),
		symbol(symbol)
	{
	}
    int getX() const { return x; }
    int getY() const { return y; }

	virtual void update() = 0;
	virtual void draw(WINDOW *win) = 0;

	virtual ~GameEntity();
};
