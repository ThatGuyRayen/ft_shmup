
#include "entity_manager.hpp"
#include "player.hpp"
#include "enemy.hpp"
#include "projectile.hpp"
#include <algorithm>

EntityManager::~EntityManager()
{
    for (auto e : entities)
        delete e;
    entities.clear();
}

void EntityManager::add(GameEntity* entity)
{
    entities.push_back(entity);
}

void EntityManager::remove(GameEntity* entity)
{
    auto it = std::find(entities.begin(), entities.end(), entity);
    if (it != entities.end())
    {
        delete *it;
        entities.erase(it);
    }
}

void EntityManager::updateAll()
{
    for (auto e : entities)
    {
        e->update();

        // Make enemies shoot if ready
        Enemy* enemy = dynamic_cast<Enemy*>(e);
        if (enemy && enemy->readyToShoot())
        {
	    Projectile* shot = enemy->shoot();
	    if (shot)
		    add(shot);
            add(enemy->shoot());
        }
    }

    // Remove off-screen projectiles
    entities.erase(std::remove_if(entities.begin(), entities.end(), [](GameEntity* e) {
        Projectile* p = dynamic_cast<Projectile*>(e);
        if (p && p->isOffScreen())
        {
            delete p;
            return true;
        }
        return false;
    }), entities.end());
}

void EntityManager::drawAll(WINDOW* win)
{
    for (auto e : entities)
        e->draw(win);
}

void EntityManager::handleCollisions(Player& player)
{
    std::vector<GameEntity*> toRemove;

    for (auto e1 : entities)
    {
        Projectile* p = dynamic_cast<Projectile*>(e1);
        if (!p)
            continue;

        int px = p->getX();
        int py = p->getY();
        int pdy = p->getDy();

        // Player projectile (dy < 0) hits enemy
        if (pdy < 0)
        {
            for (auto e2 : entities)
            {
                Enemy* enemy = dynamic_cast<Enemy*>(e2);
                if (!enemy)
                    continue;

                if (px == enemy->getX() && py == enemy->getY())
                {
                    toRemove.push_back(p);
                    toRemove.push_back(enemy);
                }
            }
        }
        // Enemy projectile (dy > 0) hits player
        else if (pdy > 0)
        {
            if (px == player.getX() && py == player.getY())
            {
                toRemove.push_back(p);
                // TODO: Handle player damage or lives
            }
        }
    }

    for (auto e : toRemove)
        remove(e);
}

