#include "game.hpp"
#include "player.hpp"

Game::Game(){}
Game::~Game(){}

void	Game::init(){
    initscr();              // Start ncurses
    cbreak();               // Disable line buffering
    noecho();               // Don't echo typed chars
    keypad(stdscr, TRUE);   // Enable arrow keys
    curs_set(0);            // Hide cursor
    nodelay(stdscr, TRUE);  // Non-blocking getch()
    timeout(0);
}


void Game::handleInput(Player* player, bool& running) {
    int ch = getch();
    switch (ch) {
        case KEY_LEFT:
        case 'a':
        case 'A':
            player->moveLeft();
            break;
        case KEY_RIGHT:
        case 'd':
        case 'D':
            player->moveRight();
            break;
        case KEY_UP:
        case 'w':
        case 'W':
            player->moveUp();
            break;
        case KEY_DOWN:
        case 's':
        case 'S':
            player->moveDown();
            break;
        case ' ':
            player->shoot();
            break;
        case 'q':
        case 27:
            running = false;
            break;
        default:
            break;
    }
}

void Game::shutdown() {
    endwin();
}
