
#pragma once

#include "game_entity.hpp"
#include "projectile.hpp"
#include <ncurses.h>
#include <set>
#include <unordered_set>


class EntityManager; // forward

class Player : public GameEntity {
    int x, y;
    int maxX, maxY;
    std::set<int> keyState;
    EntityManager* entityManager = nullptr;
    int lives = 3;
public:
    Player(int maxX, int maxY);

    void clearKeys();
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    Projectile* shoot();
    void update() override;
    void draw(WINDOW* win) override;

    void setEntityManager(EntityManager* manager);
    void setKeyDown(int key);
    void setKeyUp(int key);
    void processKeyStates();
    void handleInput(int key);

    int getX() const override { return x; }
    int getY() const override { return y; }

    void loseLife() { if (lives > 0) lives--; }
    bool isDead() const { return lives <= 0; }
    int getLives() const { return lives; }
};
