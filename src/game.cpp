#include "game.hpp"
#include "player.hpp"
#include "enemy.hpp"
#include <iostream>
#include <random>
#include <thread>
#include <chrono>
#include <algorithm>

Game::Game() 
    : game_win(nullptr), screen_width(80), screen_height(22), scroll_x(0),
      player(10, 20, 3), score(0), game_running(true), frame_count(0) {
    
    start_time = std::chrono::steady_clock::now();
    last_frame = start_time;
    
    // Initialize scenery (simple obstacles)
    for (int i = 0; i < 10; i++) {
        scenery.push_back({20 + i * 15, 10});
        scenery.push_back({25 + i * 15, 15});
    }
}

Game::~Game() {
    cleanup_ncurses();
}

void Game::init_ncurses() {
    initscr();
    noecho();
    curs_set(0);
    cbreak();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    
    // Create game window
    game_win = newwin(screen_height, screen_width, 0, 0);
    box(game_win, 0, 0);
    wrefresh(game_win);
}

void Game::cleanup_ncurses() {
    if (game_win) {
        delwin(game_win);
    }
    endwin();
}

void Game::run() {
    init_ncurses();
    bool game_over = false;
    
    while (game_running) {
        auto frame_start = std::chrono::steady_clock::now();
        
        handle_input();
        
        if (!game_over) {
            // Check for window resize
            if (frame_count % 30 == 0) { // Check every 30 frames
                update_window_size();
            }
            
            update_game();
            render();
            
            // Check if player died
            if (!player.is_alive()) {
                game_over = true;
            }
        } else {
            // Game over screen
            render_game_over();
        }
        
        // Frame rate control
        auto frame_end = std::chrono::steady_clock::now();
        auto frame_duration = std::chrono::duration_cast<std::chrono::milliseconds>(frame_end - frame_start);
        int target_frame_time = 50; // 20 FPS
        
        if (frame_duration.count() < target_frame_time) {
            std::this_thread::sleep_for(std::chrono::milliseconds(target_frame_time - frame_duration.count()));
        }
        
        frame_count++;
        last_frame = frame_start;
    }
}

void Game::handle_input() {
    int ch = getch();
    switch (ch) {
        case 'w':
        case KEY_UP:
            player.move_up();
            break;
        case 's':
        case KEY_DOWN:
            player.move_down();
            break;
        case 'a':
        case KEY_LEFT:
            player.move_left();
            break;
        case 'd':
        case KEY_RIGHT:
            player.move_right();
            break;
        case ' ':
            if (player.can_shoot()) {
                bullets.push_back(Bullet(player.get_x() + scroll_x, player.get_y() - 1, -1));
                player.shoot();
            }
            break;
        case 'q':
        case 27: // ESC key
            game_running = false;
            break;
    }
}

void Game::update_game() {
    // Update enemies
    for (auto& enemy : enemies) {
        if (enemy.is_alive()) {
            enemy.update();
            
            // Enemy shooting
            if (enemy.can_shoot()) {
                bullets.push_back(Bullet(enemy.get_x(), enemy.get_y() + 1, 1));
                enemy.shoot();
            }
        }
    }
    
    // Update bullets
    update_bullets();
    
    // Spawn enemies
    if (frame_count % 100 == 0) {
        spawn_enemy();
    }
    
    // Scroll world
    if (frame_count % 30 == 0) {
        scroll_x++;
    }
    
    // Check collisions
    check_collisions();
    
    // Remove dead enemies and enemies that are off screen
    enemies.erase(
        std::remove_if(enemies.begin(), enemies.end(),
            [this](const Enemy& enemy) { 
                return !enemy.is_alive() || enemy.get_x() - scroll_x < -5; 
            }),
        enemies.end()
    );
    
    // Remove invalid bullets
    bullets.erase(
        std::remove_if(bullets.begin(), bullets.end(),
            [](const Bullet& bullet) { 
                return !bullet.active || bullet.y < 0 || bullet.y > 25; 
            }),
        bullets.end()
    );
}

void Game::render() {
    werase(game_win);
    box(game_win, 0, 0);
    
    // Draw player
    mvwaddch(game_win, player.get_y(), player.get_x(), player.get_symbol());
    
    // Draw enemies
    for (const auto& enemy : enemies) {
        if (enemy.is_alive()) {
            int screen_x = enemy.get_x() - scroll_x;
            if (screen_x >= 0 && screen_x < screen_width - 2) {
                mvwaddch(game_win, enemy.get_y(), screen_x + 1, enemy.get_symbol());
            }
        }
    }
    
    // Draw bullets
    for (const auto& bullet : bullets) {
        int screen_x = bullet.x - scroll_x;
        if (screen_x >= 0 && screen_x < screen_width - 2 && bullet.y >= 0 && bullet.y < screen_height - 2) {
            mvwaddch(game_win, bullet.y + 1, screen_x + 1, bullet.symbol);
        }
    }
    
    // Draw scenery
    draw_scenery();
    
    // Draw UI
    draw_ui();
    
    wrefresh(game_win);
}

void Game::spawn_enemy() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> x_dist(scroll_x + screen_width, scroll_x + screen_width + 20);
    static std::uniform_int_distribution<> y_dist(1, 10);
    
    int x = x_dist(gen);
    int y = y_dist(gen);
    
    enemies.push_back(Enemy(x, y, 'E'));
}

void Game::update_bullets() {
    for (auto& bullet : bullets) {
        bullet.y += bullet.direction;
    }
}

void Game::check_collisions() {
    // Player vs Enemy collisions
    for (auto& enemy : enemies) {
        if (enemy.is_alive() && enemy.get_x() - scroll_x == player.get_x() && enemy.get_y() == player.get_y()) {
            player.take_damage();
            score += 10;
        }
    }
    
    // Player bullets vs Enemy collisions
    for (auto& bullet : bullets) {
        if (bullet.direction == -1) { // Player bullet
            for (auto& enemy : enemies) {
                if (enemy.is_alive() && enemy.get_x() == bullet.x && 
                    enemy.get_y() == bullet.y) {
                    enemy.take_damage();
                    bullet.active = false;
                    score += 50;
                    break;
                }
            }
        }
    }
    
    // Enemy bullets vs Player collisions
    for (auto& bullet : bullets) {
        if (bullet.direction == 1 && 
            bullet.x - scroll_x == player.get_x() && 
            bullet.y == player.get_y()) {
            player.take_damage();
            bullet.active = false;
        }
    }
    
    // Bullet vs Scenery collisions
    for (auto& bullet : bullets) {
        for (const auto& obstacle : scenery) {
            if (obstacle.first - scroll_x == bullet.x && obstacle.second == bullet.y) {
                bullet.active = false;
                break;
            }
        }
    }
}

void Game::draw_ui() {
    auto now = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - start_time);
    
    mvwprintw(game_win, 0, 2, "Score: %d", score);
    mvwprintw(game_win, 0, 15, "Lives: %d", player.get_lives());
    mvwprintw(game_win, 0, 25, "Time: %lds", elapsed.count());
    mvwprintw(game_win, 0, 35, "Enemies: %zu", enemies.size());
}

void Game::draw_scenery() {
    for (const auto& obstacle : scenery) {
        int screen_x = obstacle.first - scroll_x;
        if (screen_x >= 0 && screen_x < screen_width - 2) {
            mvwaddch(game_win, obstacle.second + 1, screen_x + 1, '#');
        }
    }
}

void Game::render_game_over() {
    werase(game_win);
    box(game_win, 0, 0);
    
    // Draw game over screen
    mvwprintw(game_win, screen_height/2 - 2, screen_width/2 - 5, "GAME OVER");
    mvwprintw(game_win, screen_height/2, screen_width/2 - 8, "Score: %d", score);
    mvwprintw(game_win, screen_height/2 + 1, screen_width/2 - 10, "Press ESC to exit");
    
    wrefresh(game_win);
}

void Game::update_window_size() {
    int new_height, new_width;
    getmaxyx(stdscr, new_height, new_width);
    
    // Update screen dimensions
    screen_height = new_height;
    screen_width = new_width;
    
    // Update player bounds (leave some space for borders and UI)
    player.set_bounds(screen_width - 2, screen_height - 2);
    
    // Recreate game window with new size
    if (game_win) {
        delwin(game_win);
    }
    game_win = newwin(screen_height, screen_width, 0, 0);
}
