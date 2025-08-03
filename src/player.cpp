
#include "entity_manager.hpp"
#include "player.hpp"

Player::Player(int maxX, int maxY)
{
	this->maxX = maxX;
	this->maxY = maxY;
	x = maxX / 2;
	y = maxY - 4;
	symbol = '^';
}

void Player::clearKeys()
{
	keyState.clear();
}

void Player::moveLeft()
{
	if (x > 1)
		x--;
}

void Player::moveRight()
{
	if (x < maxX - 6)
		x++;
}

void Player::moveUp()
{
	if (y > 1)
		y--;
}

void Player::moveDown()
{
	if (y < maxY - 4)
		y++;
}

Projectile *Player::shoot()
{
	return new Projectile(x + 2, y - 1, 0, -1);
}

void Player::update()
{
	processKeyStates();
}

void Player::draw(WINDOW *win)
{
	mvwaddch(win, y, x + 2, '^');
	mvwaddch(win, y + 1, x + 1, '/');
	mvwaddch(win, y + 1, x + 2, '|');
	mvwaddch(win, y + 1, x + 3, '\\');
	mvwaddch(win, y + 2, x, '<');
	mvwaddch(win, y + 2, x + 1, '=');
	mvwaddch(win, y + 2, x + 2, '=');
	mvwaddch(win, y + 2, x + 3, '=');
	mvwaddch(win, y + 2, x + 4, '>');
}

void Player::setEntityManager(EntityManager *manager)
{
	entityManager = manager;
}

void Player::setKeyDown(int key)
{
	keyState.insert(key);

	if (key == ' ' && entityManager)
		entityManager->add(shoot());
}

void Player::setKeyUp(int key)
{
	keyState.erase(key);
}

void Player::processKeyStates()
{
	if (keyState.count(KEY_LEFT) || keyState.count('a'))
		moveLeft();
	if (keyState.count(KEY_RIGHT) || keyState.count('d'))
		moveRight();
	if (keyState.count(KEY_UP) || keyState.count('w'))
		moveUp();
	if (keyState.count(KEY_DOWN) || keyState.count('s'))
		moveDown();
}

void Player::handleInput(int key)
{
	switch (key)
	{
	case KEY_LEFT:
	case 'a':
		moveLeft();
		break;
	case KEY_RIGHT:
	case 'd':
		moveRight();
		break;
	case KEY_UP:
	case 'w':
		moveUp();
		break;
	case KEY_DOWN:
	case 's':
		moveDown();
		break;
	case ' ':
		if (entityManager)
			entityManager->add(shoot());
		break;
	default:
		break;
	}
}

