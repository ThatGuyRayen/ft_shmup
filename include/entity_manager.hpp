
// entity_manager.hpp
#pragma once
#include <vector>
#include <memory>    
#include "player.hpp"
#include <ncurses.h>

class EntityManager {
private:
	std::vector<std::unique_ptr<GameEntity>> entities;

public:
    ~EntityManager();

    void add(GameEntity* entity);
    void remove(GameEntity* entity);
    void updateAll();
    void drawAll(WINDOW* win);
    void handleCollisions(Player &player);
    // Add this getter:
    const std::vector<std::unique_ptr<GameEntity>>& getEntities() const {
        return entities;
    }
};

