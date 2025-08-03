#pragma once
#include <ncurses.h>
#include "game_entity.hpp"

class Projectile : public GameEntity {
	public:
		Projectile(int x, int y);
		void	update() override;
		void	draw(WINDOW* win) override;

		bool isOffScreen() const;
};
