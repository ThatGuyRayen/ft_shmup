#include "player.hpp"
#include <chrono>

Player::Player(int start_x, int start_y, int lives)
    : x(start_x), y(start_y), lives(lives), 
      last_shot(std::chrono::steady_clock::now()), shot_cooldown_ms(300) {}

void Player::move_up() {
    if (y > 1) y--;
}

void Player::move_down() {
    if (y < 20) y++;
}

void Player::move_left() {
    if (x > 1) x--;
}

void Player::move_right() {
    if (x < 78) x++;
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
