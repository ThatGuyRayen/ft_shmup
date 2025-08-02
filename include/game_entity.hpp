
#pragma once
#include <ncurses.h>

class GameEntity {
protected:
    int x;
    int y;
    char symbol;

public:
    GameEntity(int x = 0, int y = 0, char symbol = ' ')
        : x(x), y(y), symbol(symbol) {}

    virtual void update() = 0;
    virtual void draw(WINDOW *win) = 0;

    virtual ~GameEntity();
};
