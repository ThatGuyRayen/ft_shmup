
#include "entity_manager.hpp"
#include <algorithm>

EntityManager::~EntityManager()
{
		delete e;

	for (auto e : entities)
	entities.clear();
}

void EntityManager::add(GameEntity *entity)
{
	entities.push_back(entity);
}

void EntityManager::remove(GameEntity *entity)
{
	auto	it;
		delete *it;

	it = find(entities.begin(), entities.end(), entity);
	if (it != entities.end())
	{
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
