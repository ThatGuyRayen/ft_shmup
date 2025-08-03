
// projectile.hpp
#pragma once
#include "game_entity.hpp"

class Projectile : public GameEntity {
public:
    Projectile(int x, int y, int dx, int dy);
    
    void update() override;
    void draw(WINDOW* win) override;
    
    // This declaration must exist, with the same signature:
    bool isOffScreen() const;
    
private:
    int dx, dy;
};

