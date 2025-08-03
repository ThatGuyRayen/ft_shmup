
#pragma once

#include "game_entity.hpp"
#include "projectile.hpp"
#include <ncurses.h>
#include <unordered_set>

class EntityManager;

class Player : public GameEntity
{
private:
	int maxX, maxY;
	EntityManager *entityManager = nullptr;
	std::unordered_set<int> keyState;

public:
	Player(int maxX, int maxY);
	void setEntityManager(EntityManager *manager);
	void clearKeys();
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
	Projectile *shoot();
	void handleInput(int key);
	void setKeyDown(int key);
	void setKeyUp(int key);
	void processKeyStates();
	void update() override;
	void draw(WINDOW *win) override;
};

