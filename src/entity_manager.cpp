
#include "entity_manager.hpp"
#include <algorithm>

EntityManager::~EntityManager() {
    for (auto e : entities)
        delete e;
    entities.clear();
}

void EntityManager::add(GameEntity* entity) {
    entities.push_back(entity);
}

void EntityManager::remove(GameEntity* entity) {
    auto it = find(entities.begin(), entities.end(), entity);
    if (it != entities.end()) {
        delete *it;
        entities.erase(it);
    }
}

void EntityManager::updateAll() {
    for (auto e : entities)
        e->update();
}

void EntityManager::drawAll(WINDOW* win) {
    for (auto e : entities)
        e->draw(win);
}
