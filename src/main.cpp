
#include "entity_manager.hpp"
#include "game.hpp"
#include "player.hpp"
#include "projectile.hpp"
#include <ncurses.h>
#include <locale.h>
#include "enemy.hpp"
#include <ctime>
#include <cstdlib>

int main(void)
{
    setlocale(LC_ALL, "");
    Game game;
    int maxX = 0, maxY = 0;
    EntityManager entityManager;
    bool running = true;
    int ch;

    // Seed random for enemy behavior and spawning
    srand(time(NULL));

    game.init();
    maxX = getmaxx(game.getGameWin());
    maxY = getmaxy(game.getGameWin());

    Player player(maxX, maxY);
    player.setEntityManager(&entityManager);

    // Initial enemy spawn example (optional)
    Enemy* enemy = new Enemy(maxX / 2, 2, maxX, maxY);
    enemy->setEntityManager(&entityManager);
    entityManager.add(enemy);

    // Set up input mode
    nodelay(game.getGameWin(), TRUE);
    keypad(game.getGameWin(), TRUE); // Enable arrow keys

    while (running)
    {
        // 1. Clear previous key states for player (to detect current keys only)
        player.clearKeys();

        // 2. Read all current key presses available this frame
        while ((ch = wgetch(game.getGameWin())) != ERR)
        {
            if (ch == 'q')
            {
                running = false;
            }
            else
            {
                player.setKeyDown(ch); // track keys currently pressed
            }
        }

        // 3. Possibly spawn new enemies randomly at top
        if ((rand() % 50) == 0) // Adjust spawn rate here
        {
            int spawnX = rand() % (maxX - 2) + 1;
            Enemy* newEnemy = new Enemy(spawnX, 1, maxX, maxY);
            newEnemy->setEntityManager(&entityManager);
            entityManager.add(newEnemy);
        }

        // 4. Update game state
        player.update();
        entityManager.updateAll();
	entityManager.handleCollisions(player);
        // 5. Clear window
        werase(game.getGameWin());

        // 6. Draw border
        box(game.getGameWin(), 0, 0);

        // 7. Draw all entities
        player.draw(game.getGameWin());
        entityManager.drawAll(game.getGameWin());

        // 8. Refresh window
        wrefresh(game.getGameWin());

        // 9. Control frame rate (~20 FPS)
        napms(50);
    }

    game.shutdown();
    return 0;
}

