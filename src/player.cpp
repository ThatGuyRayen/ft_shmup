#include "player.hpp"
#include <chrono>

Player::Player(int start_x, int start_y, int lives)
    : x(start_x), y(start_y), lives(lives), max_x(78), max_y(20),
      last_shot(std::chrono::steady_clock::now()), shot_cooldown_ms(300) {}

void Player::move_up(const std::vector<std::pair<int, int>>& obstacles) {
    if (y > 1) {
        move_with_obstacle_collision(x, y - 1, obstacles);
    }
}

void Player::move_down(const std::vector<std::pair<int, int>>& obstacles) {
    if (y < max_y) {
        move_with_obstacle_collision(x, y + 1, obstacles);
    }
}

void Player::move_left(const std::vector<std::pair<int, int>>& obstacles) {
    if (x > 1) {
        move_with_obstacle_collision(x - 1, y, obstacles);
    }
}

void Player::move_right(const std::vector<std::pair<int, int>>& obstacles) {
    if (x < max_x) {
        move_with_obstacle_collision(x + 1, y, obstacles);
    }
}

bool Player::can_move_to(int new_x, int new_y, const std::vector<std::pair<int, int>>& obstacles) const {
    // Check bounds
    if (new_x < 1 || new_x > max_x || new_y < 1 || new_y > max_y) {
        return false;
    }
    
    // Check obstacles
    for (const auto& obstacle : obstacles) {
        if (obstacle.first == new_x && obstacle.second == new_y) {
            return false;
        }
    }
    
    return true;
}

void Player::set_bounds(int max_x, int max_y) {
    this->max_x = max_x;
    this->max_y = max_y;
}

bool Player::can_shoot() const {
    auto now = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - last_shot);
    return elapsed.count() >= shot_cooldown_ms;
}

void Player::shoot() {
    if (can_shoot()) {
        last_shot = std::chrono::steady_clock::now();
    }
}

void Player::take_damage() {
    if (lives > 0) {
        lives--;
    }
}

int Player::check_obstacle_collision(int new_x, int new_y, const std::vector<std::pair<int, int>>& obstacles) const {
    for (size_t i = 0; i < obstacles.size(); i++) {
        if (obstacles[i].first == new_x && obstacles[i].second == new_y) {
            return static_cast<int>(i);
        }
    }
    return -1; // No collision
}

bool Player::move_with_obstacle_collision(int new_x, int new_y, const std::vector<std::pair<int, int>>& obstacles) {
    int collision_index = check_obstacle_collision(new_x, new_y, obstacles);
    if (collision_index >= 0) {
        // Collision with obstacle - take damage
        take_damage();
        return true; // Indicates collision occurred
    } else {
        // No collision, move normally
        x = new_x;
        y = new_y;
        return false; // No collision
    }
}
