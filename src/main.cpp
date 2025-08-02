#include <iostream>
#include <ncurses.h>
#include "game.hpp"
#include "player.hpp"
using namespace std;

int	main(){
	Game game;
	game.init();

	Player player;
	bool running = true;

	while (running){
		clear();
		game.handleInput(&player, running);
		player.update();
		player.draw();

		refresh();

		napms(50);
	}
	game.shutdown();
	return (0);
}
