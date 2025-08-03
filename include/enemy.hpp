
#pragma once

#include <ncurses.h>
#include "game_entity.hpp"
#include "projectile.hpp"
#include "entity_manager.hpp"

class Enemy : public GameEntity {
private:
    int maxX, maxY;
    int shootCooldown;
    int shootTimer;
    EntityManager* entityManager;

public:
    Enemy(int startX, int startY, int maxX, int maxY);

    void setEntityManager(EntityManager* manager);

    Projectile* shoot();

    void update() override;
    void draw(WINDOW* win) override;
	void resetShootTimer();
    bool readyToShoot() const; // optional helper
};

