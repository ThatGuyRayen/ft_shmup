#pragma once

#include "game_entity.hpp"
#include "projectile.hpp"
#include <ncurses.h>

class	EntityManager;

class Player : public GameEntity
{
  private:
	int maxX, maxY; // boundaries to keep player inside
	EntityManager *entityManager = nullptr;

  public:
	Player(int maxX, int maxY);
	void setEntityManager(EntityManager *manager);
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
	Projectile *shoot();
	void handleInput(int key);
	void update() override;
	void draw(WINDOW *win) override;
};
