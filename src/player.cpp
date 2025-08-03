#include "entity_manager.hpp"
#include "player.hpp"

// Initialize player near bottom center, store boundaries
Player::Player(int maxX, int maxY)
{
	this->maxX = maxX;
	this->maxY = maxY;
	x = maxX / 2;
	y = maxY - 4; // near bottom but inside border
	symbol = '^';
}

void Player::moveLeft()
{
	if (x > 1) // 1 for border offset
		x--;
}

void Player::moveRight()
{
	if (x < maxX - 6) // 5 wide ship + 1 border
		x++;
}

void Player::moveUp()
{
	if (y > 1)
		y--;
}

void Player::moveDown()
{
	if (y < maxY - 4) // 3 high ship + 1 border
		y++;
}

Projectile *Player::shoot()
{
	return (new Projectile(x + 2, y - 1));
}

void Player::update()
{
	// Update player state here if needed
}

void Player::draw(WINDOW *win)
{
	// Draw a simple 3x5 ship shape relative to (x, y)
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

void Player::handleInput(int key)
{
	switch (key)
	{
	case KEY_LEFT:
	case 'a':
		moveLeft();
		break ;
	case KEY_RIGHT:
	case 'd':
		moveRight();
		break ;
	case KEY_UP:
	case 'w':
		moveUp();
		break ;
	case KEY_DOWN:
	case 's':
		moveDown();
		break ;
	case ' ':
		if (entityManager)
		{
			entityManager->add(shoot());
		}
		break ;
	default:
		break ;
	}
}
