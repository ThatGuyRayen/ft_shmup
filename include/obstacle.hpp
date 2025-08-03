#pragma once
#include "game_entity.hpp"
#include <ncurses.h>

class Obstacle : public GameEntity {
    int x, y;
public:
    Obstacle(int x, int y) : x(x), y(y) {}
    void update() override {}
    void draw(WINDOW* win) override {
        if (!win) return;
        int max_y, max_x;
        getmaxyx(win, max_y, max_x);
        if (y >= 0 && y < max_y && x >= 0 && x < max_x)
            mvwaddch(win, y, x, '#');
    }
    int getX() const override { return x; }
    int getY() const override { return y; }
};
