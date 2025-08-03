
#pragma once

#include "game_entity.hpp"
#include "projectile.hpp"
#include <ncurses.h>
#include <vector>

using namespace	std;

class EntityManager
{
  private:
	vector<GameEntity *> entities;

  public:
	~EntityManager();

	void add(GameEntity *entity);
	void remove(GameEntity *entity);

	void updateAll();
	void drawAll(WINDOW *win);

	// Helper to clean up projectiles or any entities flagged for removal (optional)
};
