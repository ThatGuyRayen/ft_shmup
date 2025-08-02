#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <chrono>
#include <vector>
#include <utility>

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
    void move_up(const std::vector<std::pair<int, int>>& obstacles);
    void move_down(const std::vector<std::pair<int, int>>& obstacles);
    void move_left(const std::vector<std::pair<int, int>>& obstacles);
    void move_right(const std::vector<std::pair<int, int>>& obstacles);
    void set_bounds(int max_x, int max_y);
    bool can_move_to(int new_x, int new_y, const std::vector<std::pair<int, int>>& obstacles) const;
    
    // Combat
    bool can_shoot() const;
    void shoot();
    void take_damage();
    
    // Obstacle collision
    int check_obstacle_collision(int new_x, int new_y, const std::vector<std::pair<int, int>>& obstacles) const;
    bool move_with_obstacle_collision(int new_x, int new_y, const std::vector<std::pair<int, int>>& obstacles);
};

#endif
