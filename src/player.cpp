#include "player.hpp"
#include <chrono>

Player::Player(int start_x, int start_y, int lives)
    : x(start_x), y(start_y), lives(lives), max_x(78), max_y(20),
      last_shot(std::chrono::steady_clock::now()), shot_cooldown_ms(300) {}

void Player::move_up() {
    if (y > 1) y--;
}

void Player::move_down() {
    if (y < max_y) y++;
}

void Player::move_left() {
    if (x > 1) x--;
}

void Player::move_right() {
    if (x < max_x) x++;
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
