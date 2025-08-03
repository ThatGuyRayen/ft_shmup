#pragma once

#include <ncurses.h>

class GameEntity {
public:
    virtual ~GameEntity();
    virtual void update() = 0;
    virtual void draw(WINDOW* win) = 0;

    virtual int getX() const = 0;
    virtual int getY() const = 0;
};
