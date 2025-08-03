#include "entity_manager.hpp"
#include "game.hpp"
#include "player.hpp"
#include "projectile.hpp"
#include "enemy.hpp"
#include <ncurses.h>
#include <locale.h>
#include <ctime>
#include <cstdlib>

int main()
{
    setlocale(LC_ALL, "");
    Game game;
    EntityManager entityManager;
    bool running = true;
    int ch;
    int score = 0;
    int timeElapsed = 0;

    srand(time(nullptr));

    game.init();
    int maxX = getmaxx(game.getGameWin());
    int maxY = getmaxy(game.getGameWin());

    Player player(maxX, maxY);
    player.setEntityManager(&entityManager);

    // Initial enemy spawn at top
    Enemy* enemy = new Enemy(rand() % (maxX - 2) + 1, 1, maxY);
    enemy->setEntityManager(&entityManager);
    entityManager.add(enemy);

    // Input setup on game window
    nodelay(game.getGameWin(), TRUE);
    keypad(game.getGameWin(), TRUE);

    const int frameDelayMs = 50; // ~20 FPS
    while (running)
    {
        // Input: clear old state
        player.clearKeys();
        while ((ch = wgetch(game.getGameWin())) != ERR)
        {
            if (ch == 'q' || ch == 27)
            {
                running = false;
            }
            else
            {
                player.setKeyDown(ch);
            }
        }

        // Randomly spawn new enemy at top row
        if ((rand() % 50) == 0)
        {
            int spawnX = rand() % (maxX - 2) + 1;
            Enemy* newEnemy = new Enemy(spawnX, 1, maxY);
            newEnemy->setEntityManager(&entityManager);
            entityManager.add(newEnemy);
        }

        // Update
        player.update();
        entityManager.updateAll();
        entityManager.handleCollisions(player);

        // Check player death
        if (player.isDead())
        {
            werase(game.getGameWin());
            box(game.getGameWin(), 0, 0);
            mvwprintw(game.getGameWin(), maxY / 2, maxX / 2 - 5, "GAME OVER");
            wrefresh(game.getGameWin());
            napms(1500);
            break;
        }

        // Draw
        werase(game.getGameWin());
        box(game.getGameWin(), 0, 0);
        player.draw(game.getGameWin());
        entityManager.drawAll(game.getGameWin());
        wrefresh(game.getGameWin());

        // UI
        game.drawUI(score, timeElapsed, player.getLives());

        // Frame control
        napms(frameDelayMs);
        timeElapsed += frameDelayMs / 1000;
    }

    game.shutdown();
    return 0;
}
