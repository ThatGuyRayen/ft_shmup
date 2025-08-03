#pragma once
#include "game_entity.hpp"
#include <ncurses.h>

class Projectile : public GameEntity
{
  public:
	Projectile(int x, int y);
	void update() override;
	void draw(WINDOW *win) override;

	bool isOffScreen() const;
};
