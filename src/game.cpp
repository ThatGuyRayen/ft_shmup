#include "game.hpp"
#include "player.hpp"
#include "game_entity.hpp"
#include <ncurses.h>

Game::Game() {}
Game::~Game() {}

void Game::init()
{
    int wHeight;
    int gameHeight;
    int gameWidth;

    initscr();             // Start ncurses
    cbreak();              // Disable line buffering
    noecho();              // Don't echo typed chars
    keypad(stdscr, TRUE);  // Enable arrow keys
    curs_set(0);           // Hide cursor
    nodelay(stdscr, TRUE); // Non-blocking getch()
    timeout(0);
    wHeight = 3;
    gameHeight = LINES - wHeight - 2;
    gameWidth = COLS - 2;
    gameWin = newwin(gameHeight, gameWidth, 1, 1);
    uiWin = newwin(wHeight, COLS, LINES - wHeight, 0);
    box(stdscr, 0, 0);
    refresh();
    box(gameWin, 0, 0);
    wrefresh(gameWin);
    werase(uiWin);
    wrefresh(uiWin);
}

void Game::drawGame(GameEntity& entity)
{
    werase(gameWin);
    entity.draw(gameWin);
    box(gameWin, 0, 0);
    wrefresh(gameWin);
}

void Game::drawUI(int score, int timeElapsed, int lives)
{
    werase(uiWin);
    mvwprintw(uiWin, 1, 2, "Score: %d", score);
    mvwprintw(uiWin, 1, COLS / 2 - 10, "Time: %d s", timeElapsed);
    mvwprintw(uiWin, 1, COLS - 15, "Lives: %d", lives);
    wrefresh(uiWin);
}

void Game::shutdown()
{
    if (gameWin)
        delwin(gameWin);
    if (uiWin)
        delwin(uiWin);
    endwin();
}

