#include <iostream>
#include <ncurses.h>
#include "game.hpp"
#include "player.hpp"


using namespace std;

int	main(){
	Game game;
	game.init();

    int maxX = getmaxx(game.getGameWin());
    int maxY = getmaxy(game.getGameWin());
	Player player(maxX, maxY);
	bool running = true;
	int	score = 0;
	int	timeElapsed = 0;

    while (running) {
        werase(game.getGameWin());       // Clear game window for fresh frame

        game.handleInput(&player, running); // Process input
        player.update();                 // Update player state (if needed)
        player.draw(game.getGameWin()); // Draw player in game window

        box(game.getGameWin(), 0, 0);   // Draw border around game window
        wrefresh(game.getGameWin());    // Refresh game window

        game.drawUI(score, timeElapsed); // Update and display UI (score/time)

        napms(50);                      // Frame delay (~20 FPS)
        timeElapsed++;
    }


	game.shutdown();
	return (0);
}
