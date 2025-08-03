
#include "enemy.hpp"

// Constructor initializes boundaries and timers, positions the enemy

Enemy::Enemy(int maxX, int maxY, int startX, int startY)
    : shootCooldown(30), shootTimer(0), maxX(maxX), maxY(maxY)
{
    x = startX;
    y = startY;
}


// Shoot projectile downwards from enemy position
Projectile* Enemy::shoot() {
    return new Projectile(x, y + 1, 0, 1);
}

// Returns whether enemy can shoot now
bool Enemy::readyToShoot() const {
    return shootTimer >= shootCooldown;
}

// Update enemy timers and possibly position (optional boundary checks added)
void Enemy::update() {
    shootTimer++;
    if (shootTimer >= shootCooldown) {
        shootTimer = 0;
        // actual shooting triggered outside
    }

    // Optional: keep enemy within bounds
    if (x < 0) x = 0;
    if (x > maxX) x = maxX;
    if (y < 0) y = 0;
    if (y > maxY) y = maxY;

    // TODO: add enemy movement logic here if needed
}

// Draw enemy as rocket emoji on window at position (y, x)
void Enemy::draw(WINDOW* win) {
    mvwaddwstr(win, y, x, L"🚀");
}

