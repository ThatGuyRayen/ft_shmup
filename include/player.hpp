#pragma once
#include "game.hpp"
#include "game_entity.hpp"

using namespace std;

class Player : public GameEntity {
public:
    Player();
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    void shoot();

    void update() override;
    void draw() override;
};
