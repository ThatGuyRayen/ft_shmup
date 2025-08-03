
// projectile.hpp
#pragma once
#include "game_entity.hpp"


class Projectile : public GameEntity {
protected:
    int x, y;
    int dx, dy;
    chtype symbol;
public:
    Projectile(int startX, int startY, int deltaX, int deltaY);
    void update() override;
    void draw(WINDOW* win) override;

    bool isOffScreen(int maxY) const; // now takes bottom bound as parameter

    int getX() const override { return x; }
    int getY() const override { return y; }
    int getDy() const { return dy; }
};
