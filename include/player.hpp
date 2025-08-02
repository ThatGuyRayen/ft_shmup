#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <chrono>

class Player {
private:
    int x, y;
    int lives;
    int max_x, max_y;
    std::chrono::steady_clock::time_point last_shot;
    int shot_cooldown_ms;
    
public:
    Player(int start_x, int start_y, int lives = 3);
    
    // Getters
    int get_x() const { return x; }
    int get_y() const { return y; }
    int get_lives() const { return lives; }
    char get_symbol() const { return 'A'; }
    bool is_alive() const { return lives > 0; }
    
    // Movement
    void move_up();
    void move_down();
    void move_left();
    void move_right();
    void set_bounds(int max_x, int max_y);
    
    // Combat
    bool can_shoot() const;
    void shoot();
    void take_damage();
};

#endif
