#ifndef GAME_HPP
#define GAME_HPP

#include <ncurses.h>
#include <vector>
#include <chrono>
#include "player.hpp"
#include "enemy.hpp"
#include <string>

// Simple game entity structure
struct Entity {
    int x, y;
    char symbol;
    bool alive;
    
    Entity(int x, int y, char sym) : x(x), y(y), symbol(sym), alive(true) {}
    virtual ~Entity() = default;
};

// Bullet structure
struct Bullet {
    int x, y;
    int direction; // 1 = down, -1 = up
    char symbol;
    bool active;
    
    Bullet(int x, int y, int dir) : x(x), y(y), direction(dir), 
                                   symbol(dir > 0 ? 'v' : '|'), active(true) {}
};

class Game {
private:
    WINDOW* game_win;
    int screen_width;
    int screen_height;
    int scroll_x;
    
    // Game entities
    Player player;
    std::vector<Enemy> enemies;
    std::vector<Bullet> bullets;
    std::vector<std::pair<int, int>> scenery;
    std::vector<bool> scenery_alive;
    
    // Game state
    int score;
    bool game_running;
    std::chrono::steady_clock::time_point start_time;
    std::chrono::steady_clock::time_point last_frame;
    int frame_count;
    
	void display_message_style(std::string message, int style);
    void init_ncurses();
    void cleanup_ncurses();
    void handle_input();
    void update_game();
    void render();
    void spawn_enemy();
    void update_bullets();
    void check_collisions();
    void draw_ui();
    void draw_scenery();
    void render_game_over();
	bool is_terminal_too_small(int new_width, int new_height);
    void update_window_size();
    std::vector<std::pair<int, int>> get_active_obstacles() const;
    void check_obstacle_collision();
    void handle_player_obstacle_collision(int collision_index);
    
public:
    Game();
    ~Game();
    void run();
};

#endif
