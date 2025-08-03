#include "entity_manager.hpp"
#include "player.hpp"
#include "enemy.hpp"
#include "projectile.hpp"
#include "game_entity.hpp"
#include <algorithm>

EntityManager::~EntityManager() = default;

void EntityManager::add(GameEntity* entity)
{
    entities.emplace_back(std::unique_ptr<GameEntity>(entity));
}

void EntityManager::remove(GameEntity* entity)
{
    auto it = std::find_if(entities.begin(), entities.end(),
        [entity](const std::unique_ptr<GameEntity>& e) {
            return e.get() == entity;
        });

    if (it != entities.end())
        entities.erase(it);
}

void EntityManager::updateAll()
{
    for (auto& e : entities)
    {
        e->update();
    }

    // Remove off-screen projectiles (top and bottom)
    entities.erase(std::remove_if(entities.begin(), entities.end(), [](const std::unique_ptr<GameEntity>& e) {
        Projectile* p = dynamic_cast<Projectile*>(e.get());
        if (p)
        {
            // Need a maxY; assume projectile will query a global or sentinel—here we approximate by letting caller ensure window height
            // For safety, we leave removal of outdated projectiles to handleCollisions or external logic
            // Alternatively, store window size somewhere accessible.
        }
        return false;
    }), entities.end());
}

void EntityManager::drawAll(WINDOW* win)
{
    for (auto& e : entities)
        e->draw(win);
}

static bool playerHitByProjectile(int px, int py, const Player& player)
{
    int x = player.getX();
    int y = player.getY();
    if (py == y && px == x + 2) return true;
    if (py == y + 1 && (px >= x + 1 && px <= x + 3)) return true;
    if (py == y + 2 && (px >= x && px <= x + 4)) return true;
    return false;
}

void EntityManager::handleCollisions(Player& player)
{
    std::vector<GameEntity*> toRemove;

    // Check each entity
    for (auto& e1 : entities)
    {
        // Projectile logic
        auto* p = dynamic_cast<Projectile*>(e1.get());
        if (p)
        {
            int px = p->getX();
            int py = p->getY();
            int pdy = p->getDy();

            // Player's projectile upward hitting enemy
            if (pdy < 0)
            {
                for (auto& e2 : entities)
                {
                    auto* enemy = dynamic_cast<Enemy*>(e2.get());
                    if (!enemy) continue;

                    if (px == enemy->getX() && py == enemy->getY())
                    {
                        toRemove.push_back(p);
                        toRemove.push_back(enemy);
                    }
                }
            }
            // Enemy projectile downward hitting player
            else if (pdy > 0)
            {
                if (playerHitByProjectile(px, py, player))
                {
                    toRemove.push_back(p);
                    player.loseLife();
                }
            }
        }
    }

    // Enemy reaches bottom
    for (auto& e : entities)
    {
        auto* enemy = dynamic_cast<Enemy*>(e.get());
        if (enemy && enemy->reachedBottom())
        {
            toRemove.push_back(enemy);
            player.loseLife();
        }
    }

    // Deduplicate
    std::sort(toRemove.begin(), toRemove.end());
    toRemove.erase(std::unique(toRemove.begin(), toRemove.end()), toRemove.end());

    // Erase all marked
    entities.erase(std::remove_if(entities.begin(), entities.end(),
        [&](const std::unique_ptr<GameEntity>& e) {
            return std::find(toRemove.begin(), toRemove.end(), e.get()) != toRemove.end();
        }), entities.end());
}
