
#pragma once

#include <ncurses.h>
#include "game_entity.hpp"


class Player : public GameEntity {
private:
    int maxX, maxY;  // boundaries to keep player inside

public:
    Player(int maxX, int maxY);

    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    void shoot();

    void update() override;
    void draw(WINDOW* win) override;
};

