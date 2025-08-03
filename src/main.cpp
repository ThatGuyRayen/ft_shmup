
#include <ncurses.h>
#include "game.hpp"
#include "player.hpp"
#include "entity_manager.hpp"
#include "projectile.hpp"

int main() {
    Game game;
    game.init();

    int maxX = getmaxx(game.getGameWin());
    int maxY = getmaxy(game.getGameWin());

    Player player(maxX, maxY);
    EntityManager entityManager;

    // Make getch non-blocking
    nodelay(game.getGameWin(), TRUE);
    keypad(game.getGameWin(), TRUE); // Enable arrow keys

    bool running = true;

    while (running) {
        int ch = wgetch(game.getGameWin());

        if (ch != ERR) { // Key pressed
            player.handleInput(ch);

            if (ch == ' ') {
                entityManager.add(player.shoot());
            } else if (ch == 'q') {
                running = false;
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

    return 0;
}

