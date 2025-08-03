
// entity_manager.hpp
#pragma once

#include <vector>
#include <memory>
#include <ncurses.h>

class GameEntity;
class Player;

class EntityManager {
    std::vector<std::unique_ptr<GameEntity>> entities;
public:
    ~EntityManager();

    void add(GameEntity* entity);
    void remove(GameEntity* entity); // safe removal by pointer

    void updateAll();
    void drawAll(WINDOW* win);
    void handleCollisions(Player& player);
};
