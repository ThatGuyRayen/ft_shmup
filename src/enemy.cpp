#include "enemy.hpp"
#include "entity_manager.hpp"
#include "projectile.hpp"
#include <cstdlib> // rand
#include <ncurses.h>

Enemy::Enemy(int startX, int startY, int maxY)
    : x(startX), y(startY),
      maxY(maxY),
      shootCooldown(30), shootTimer(0),
      entityManager(nullptr)
{
}

void Enemy::setEntityManager(EntityManager* manager)
{
    entityManager = manager;
}

Projectile* Enemy::shoot()
{
    return new Projectile(x, y + 1, 0, 1); // downwards
}

void Enemy::resetShootTimer() {
    shootTimer = 0;
}

bool Enemy::readyToShoot() const
{
    return shootTimer >= shootCooldown;
}

void Enemy::update()
{
    // Straight downward movement
    if (y < maxY - 2)
        y++;

    shootTimer++;

    // Defensive: don't shoot if about to go off screen
    if (entityManager && readyToShoot() && (rand() % 100) < 20) // more frequent for responsiveness
    {
        // Only shoot if projectile will be in bounds
        if (y + 1 < maxY - 1 && y + 1 >= 0) {
            Projectile* p = shoot();
            if (p)
            {
                entityManager->add(p);
                resetShootTimer();
            }
        }
    }
}

void Enemy::draw(WINDOW* win)
{
    if (!win) return;
    int max_y, max_x;
    getmaxyx(win, max_y, max_x);
    if (y >= 0 && y < max_y && x >= 0 && x < max_x)
    {
        mvwaddch(win, y, x, 'Y');
    }
}
