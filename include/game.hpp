#pragma once

#include "player.hpp"
#include <iostream>
#include <ncurses.h>
#include <string>
#include <vector>

class			Player;
class			GameEntity;

using namespace	std;

class Game
{
  private:
	WINDOW *gameWin;
	WINDOW *uiWin;

  public:
	Game();
	~Game();
	WINDOW *getGameWin() const
	{
		return (gameWin);
	}
	WINDOW *getUIWin() const
	{
		return (uiWin);
	}
	void init();
	void handleInput(Player *player, bool &running);
	void shutdown();

	void drawGame(GameEntity &entity);
	void drawUI(int score, int timeElapsed);
};
