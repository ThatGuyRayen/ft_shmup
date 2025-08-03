
#include "entity_manager.hpp"
#include <algorithm>

EntityManager::~EntityManager()
{
    // Delete all entities to avoid memory leaks
    for (auto e : entities)
        delete e;

    // Clear the vector after deleting pointers
    entities.clear();
}

void EntityManager::add(GameEntity *entity)
{
    entities.push_back(entity);
}

void EntityManager::remove(GameEntity *entity)
{
    // Find the entity in the vector
    auto it = std::find(entities.begin(), entities.end(), entity);

    if (it != entities.end())
    {
        // Delete the entity object to free memory
        delete *it;

        // Remove pointer from vector
        entities.erase(it);
    }
}

void EntityManager::updateAll()
{
    for (auto e : entities)
        e->update();
}

void EntityManager::drawAll(WINDOW *win)
{
    for (auto e : entities)
        e->draw(win);
}

