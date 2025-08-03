
// projectile.hpp
#pragma once
#include "game_entity.hpp"

class Projectile : public GameEntity {
private:
    int dx, dy;

public:
    Projectile(int x, int y, int dx, int dy);

    int getDx() const { return dx; }
    int getDy() const { return dy; }

    bool isOffScreen() const;
    void update() override;
    void draw(WINDOW* win) override;
};

