#pragma once

#include <ncurses.h>

class Player;
class GameEntity;

class Game {
protected:
    WINDOW* gameWin = nullptr;
    WINDOW* uiWin = nullptr;
public:
    Game();
    ~Game();

    void init();
    void drawGame(GameEntity& entity);
    void drawUI(int score, int timeElapsed, int lives);
    void shutdown();

    WINDOW* getGameWin() const { return gameWin; }
};
