
#include "entity_manager.hpp"
#include "player.hpp"
#include "enemy.hpp"
#include "projectile.hpp"
#include "game_entity.hpp"
#include <algorithm>

// EntityManager::~EntityManager()
// {
//     for (auto& e : entities)
//         delete e.get();
//     entities.clear();
// }

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
    	entities.erase(it); // as it is a unique ptr now - auto delete
}

void EntityManager::updateAll()
{
    for (auto& e : entities)
    {
        e->update();
    }

    // Remove off-screen projectiles
    entities.erase(std::remove_if(entities.begin(), entities.end(), [](const std::unique_ptr<GameEntity>& e) {
        Projectile* p = dynamic_cast<Projectile*>(e.get());
        return p && p->isOffScreen();
    }), entities.end());
}

void EntityManager::drawAll(WINDOW* win)
{
    for (auto& e : entities)
        e->draw(win);
}

void EntityManager::handleCollisions(Player& player)
{
    std::vector<GameEntity*> toRemove;

    for (auto& e1 : entities)
    {
        auto* p = dynamic_cast<Projectile*>(e1.get());
        if (!p)
            continue;

        int px = p->getX();
        int py = p->getY();
        int pdy = p->getDy();

        // player shot upwards - hits enemy (plus score)
        if (pdy < 0)
        {
            for (const auto& e2 : entities)
            {
                auto* enemy = dynamic_cast<Enemy*>(e2.get());
                if (!enemy)
                    continue;

                if (px == enemy->getX() && py == enemy->getY())
                {
                    if (std::find(toRemove.begin(), toRemove.end(), p) == toRemove.end())
                        toRemove.push_back(p);
                    if (std::find(toRemove.begin(), toRemove.end(), enemy) == toRemove.end())
                        toRemove.push_back(enemy);
                }
            }
        }
        // enemy shot downwards = shot the player (minus life)
        else if (pdy > 0)
        {
            if (px == player.getX() && py == player.getY())
            {
                if (std::find(toRemove.begin(), toRemove.end(), p) == toRemove.end())
                    toRemove.push_back(p);
            }
        }
    }

 	// cleaning of all the leftover from the entities as unique pointers
     entities.erase(std::remove_if(entities.begin(), entities.end(),
        [&](const std::unique_ptr<GameEntity>& e) {
            return std::find(toRemove.begin(), toRemove.end(), e.get()) != toRemove.end();
        }), entities.end());
}

