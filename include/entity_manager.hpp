
// entity_manager.hpp
#pragma once
#include <vector>
#include "game_entity.hpp"
#include <ncurses.h>

class EntityManager {
private:
    std::vector<GameEntity*> entities;

public:
    ~EntityManager();

    void add(GameEntity* entity);
    void remove(GameEntity* entity);
    void updateAll();
    void drawAll(WINDOW* win);

    // Add this getter:
    const std::vector<GameEntity*>& getEntities() const {
        return entities;
    }
};

