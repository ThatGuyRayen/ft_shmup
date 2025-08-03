#pragma once

#include "game_entity.hpp"
#include <ncurses.h>

class EntityManager; // forward
class Projectile;

class Enemy : public GameEntity {
    int x, y;
    int maxY;
    int shootCooldown;
    int shootTimer;
    int moveTimer;
    EntityManager* entityManager;
public:
    Enemy(int startX, int startY, int maxY);
    void setEntityManager(EntityManager* manager);

    Projectile* shoot();
    void resetShootTimer();
    bool readyToShoot() const;

    void update() override;
    void draw(WINDOW* win) override;

    int getX() const override { return x; }
    int getY() const override { return y; }

    bool reachedBottom() const { return y >= maxY - 2; } // near bottom border
};
