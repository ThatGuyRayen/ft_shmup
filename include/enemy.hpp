#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <chrono>

class Enemy {
private:
    int x, y;
    char symbol;
    bool alive;
    std::chrono::steady_clock::time_point last_shot;
    int shot_cooldown_ms;
    int move_counter;
    int move_interval;
    
public:
    Enemy(int x, int y, char sym = 'E');
    
    // Getters
    int get_x() const { return x; }
    int get_y() const { return y; }
    char get_symbol() const { return symbol; }
    bool is_alive() const { return alive; }
    
    // Movement
    void update_position();
    void move_left();
    void move_right();
    
    // Combat
    bool can_shoot() const;
    void shoot();
    void take_damage();
    
    // AI
    void update();
};

#endif
