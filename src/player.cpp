#include "player.hpp"

Player::Player() {
    x = COLS / 2;        // Start roughly center horizontally
    y = LINES - 2;       // Near bottom of the terminal
    symbol = '^';        // Representation of the player's ship
}

void Player::moveLeft() {
    if (x > 0)
        x--;
}

void Player::moveRight() {
    if (x < COLS - 1)
        x++;
}

void	Player::moveUp(){
	if (y > 0)
		y--;
}

void	Player::moveDown(){
	if (y < LINES - 1)
		y++;
}

void Player::shoot() {
    // TODO: Later spawn a projectile entity here
}

void Player::update() {
    // For now, nothing to update here
}

void Player::draw() {
    mvaddch(y, x, symbol);
}
