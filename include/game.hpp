#pragma once

#include <string>
#include <vector>
#include <iostream>
#include "player.hpp"
#include <ncurses.h>

class Player;


using namespace std;

class Game {
public:
    Game();
    ~Game();

    void init();
    void handleInput(Player* player, bool& running);
    void shutdown();
};
