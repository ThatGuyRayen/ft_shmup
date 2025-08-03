#include "player.hpp"
#include "entity_manager.hpp"
#include "projectile.hpp"
#include <ncurses.h>

Player::Player(int maxX, int maxY)
    : maxX(maxX), maxY(maxY)
{
    x = maxX / 2;
    y = maxY - 4;
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

Projectile* Player::shoot()
{
    return new Projectile(x + 2, y - 1, 0, -1);
}

void Player::update()
{
    processKeyStates();
}

void Player::draw(WINDOW* win)
{
    int max_y, max_x;
    getmaxyx(win, max_y, max_x);
    auto safe_mvwaddch = [&](int yy, int xx, chtype ch) {
        if (yy >= 0 && yy < max_y && xx >= 0 && xx < max_x)
            mvwaddch(win, yy, xx, ch);
    };

    safe_mvwaddch(y, x + 2, '^');
    safe_mvwaddch(y + 1, x + 1, '/');
    safe_mvwaddch(y + 1, x + 2, '|');
    safe_mvwaddch(y + 1, x + 3, '\\');
    safe_mvwaddch(y + 2, x, '<');
    safe_mvwaddch(y + 2, x + 1, '=');
    safe_mvwaddch(y + 2, x + 2, '=');
    safe_mvwaddch(y + 2, x + 3, '=');
    safe_mvwaddch(y + 2, x + 4, '>');
}

void Player::setEntityManager(EntityManager* manager)
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
