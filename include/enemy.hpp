
#pragma once

#include <ncurses.h>
#include "game_entity.hpp"
#include "projectile.hpp"

class Enemy : public GameEntity {
private:
    int shootCooldown;
    int shootTimer;
    int maxX;
    int maxY;
public:
    Enemy(int maxX, int maxY, int startX, int startY);

    void update() override;
    void draw(WINDOW* win) override;

    Projectile* shoot();

    bool readyToShoot() const;
};

