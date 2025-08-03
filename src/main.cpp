
#include "entity_manager.hpp"
#include "game.hpp"
#include "player.hpp"
#include "projectile.hpp"
#include "enemy.hpp"
#include "obstacle.hpp"
#include <ncurses.h>
#include <locale.h>
#include <cstdlib>
#include <chrono>
#include <thread>

int main()
{
    setlocale(LC_ALL, "");
    Game game;
    EntityManager entityManager;
    bool running = true;
    int ch;
    int score = 0;
    int timeElapsed = 0;
    int enemySpawnTimer = 0;
    int enemySpawnInterval = 1200; // ms

    srand(time(nullptr));

    game.init();
    int maxX = getmaxx(game.getGameWin());
    int maxY = getmaxy(game.getGameWin());


    Player player(maxX, maxY);
    player.setEntityManager(&entityManager);

    // Add obstacles
    int numObstacles = 8;
    for (int i = 0; i < numObstacles; ++i) {
        int ox = rand() % (maxX - 4) + 2;
        int oy = rand() % (maxY - 10) + 4;
        entityManager.add(new Obstacle(ox, oy));
    }

    // Input setup on game window
    nodelay(game.getGameWin(), TRUE);
    keypad(game.getGameWin(), TRUE);

    auto lastFrame = std::chrono::steady_clock::now();
    auto startTime = lastFrame;
    while (running)
    {
        auto now = std::chrono::steady_clock::now();
        int frameDelayMs = 50;
        int elapsedMs = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastFrame).count();
        if (elapsedMs < frameDelayMs) {
            std::this_thread::sleep_for(std::chrono::milliseconds(frameDelayMs - elapsedMs));
            now = std::chrono::steady_clock::now();
        }
        lastFrame = now;

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

        // Enemy spawn timer
        enemySpawnTimer += frameDelayMs;
        if (enemySpawnTimer >= enemySpawnInterval)
        {
            int spawnX = rand() % (maxX - 2) + 1;
            Enemy* newEnemy = new Enemy(spawnX, 1, maxY);
            newEnemy->setEntityManager(&entityManager);
            entityManager.add(newEnemy);
            enemySpawnTimer = 0;
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
            std::this_thread::sleep_for(std::chrono::milliseconds(1500));
            break;
        }

        // Draw
        werase(game.getGameWin());
        box(game.getGameWin(), 0, 0);
        player.draw(game.getGameWin());
        entityManager.drawAll(game.getGameWin());
        wrefresh(game.getGameWin());

        // UI
        auto nowTime = std::chrono::steady_clock::now();
        timeElapsed = std::chrono::duration_cast<std::chrono::seconds>(nowTime - startTime).count();
        game.drawUI(score, timeElapsed, player.getLives());
    }

    game.shutdown();
    return 0;
}
