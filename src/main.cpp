#include "entity_manager.hpp"
#include "game.hpp"
#include "player.hpp"
#include "projectile.hpp"
#include <ncurses.h>

int	main(void)
{
	Game			game;
	int				maxX;
	int				maxY;
	EntityManager	entityManager;
	bool			running;
		int ch;

	game.init();
	maxX = getmaxx(game.getGameWin());
	maxY = getmaxy(game.getGameWin());
	Player player(maxX, maxY);
	player.setEntityManager(&entityManager);
	// Make getch non-blocking
	nodelay(game.getGameWin(), TRUE);
	keypad(game.getGameWin(), TRUE); // Enable arrow keys
	running = true;
	while (running)
	{
		while ((ch = wgetch(game.getGameWin())) != ERR)
		{
			if (ch == 'q')
			{
				running = false;
			}
			else
			{
				player.handleInput(ch);
			}
		}
		// Update game state
		player.update();
		entityManager.updateAll();
		// Clear window
		werase(game.getGameWin());
		// Draw border
		box(game.getGameWin(), 0, 0);
		// Draw player and entities
		player.draw(game.getGameWin());
		entityManager.drawAll(game.getGameWin());
		// Refresh to show changes
		wrefresh(game.getGameWin());
		// Control frame rate (~20 FPS)
		napms(50);
	}
	game.shutdown();
	return (0);
}
