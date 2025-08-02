#include "enemy.hpp"
#include <chrono>
#include <random>

Enemy::Enemy(int x, int y, char sym)
    : x(x), y(y), symbol(sym), alive(true),
      last_shot(std::chrono::steady_clock::now()), shot_cooldown_ms(2000),
      move_counter(0), move_interval(30) {}

void Enemy::update_position() {
    move_counter++;
    if (move_counter >= move_interval) {
        move_counter = 0;
        move_left();
    }
}

void Enemy::move_left() {
    x--;
}

void Enemy::move_right() {
    x++;
}

bool Enemy::can_shoot() const {
    auto now = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - last_shot);
    return elapsed.count() >= shot_cooldown_ms;
}

void Enemy::shoot() {
    if (can_shoot()) {
        last_shot = std::chrono::steady_clock::now();
    }
}

void Enemy::take_damage() {
    alive = false;
}

void Enemy::update() {
    update_position();
}
