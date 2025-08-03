
#include "enemy.hpp"
#include <cstdlib> // for rand()

Enemy::Enemy(int startX, int startY, int maxX, int maxY)
	: maxX(maxX), maxY(maxY), shootCooldown(30), shootTimer(0), entityManager(nullptr)
{
	x = startX;
	y = startY;
	symbol = '^'; // optional, emoji used in draw()
}

void Enemy::setEntityManager(EntityManager* manager)
{
	entityManager = manager;
}

Projectile* Enemy::shoot()
{
	return new Projectile(x, y + 1, 0, 1); // shooting downward
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
	shootTimer++;

	// Random movement: left/right/down
	int r = rand() % 100;
	if (r < 3 && x > 1)
		x--;
	else if (r < 6 && x < maxX - 2)
		x++;
	else if (r < 9 && y < maxY - 2)
		y++;

	// Shooting logic
	if (entityManager && readyToShoot() && (rand() % 100) < 5)
	{
		Projectile* p = shoot();
		if (p)
		{
			entityManager->add(p);
			resetShootTimer();
		}
	}
}

void Enemy::draw(WINDOW* win)
{
	// Draw emoji rocket 🚀
	mvwaddwstr(win, y, x, L"🚀");
}

