#pragma once
#ifndef MINIGAME_H
#define MINIGAME_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "player.h"

class MiniGame {
private:
    bool is_on = false;
    bool is_running = false;
    bool left_pressed = false;
    bool right_pressed = false;
    bool prey_active = false;
    bool slow_power_up_active = false;
    bool fast_power_up_active = false;
    bool show_game_over_screen = false;
    bool can_draw = true;
    bool reverse_controls = false;
    sf::RectangleShape player_sprite;
    sf::RectangleShape player_hitbox;
    sf::RectangleShape prey;
    sf::RectangleShape background;
    sf::RectangleShape ui_coin;
    sf::RectangleShape exit_button;
    std::vector<sf::RectangleShape> obstacles;

    sf::Texture player_dog_texture_1, player_dog_texture_2;
    sf::Texture player_cat_texture_1, player_cat_texture_2;
    sf::Texture player_texture_1, player_texture_2;
    sf::Texture prey_texture;
    sf::Texture background_texture;
    sf::Texture obstacle_texture_1, obstacle_texture_2, obstacle_texture_3, obstacle_texture_4, obstacle_texture_5;
    sf::Texture coinTexture;
    sf::Texture slow_power_up_texture, fast_power_up_texture, teleport_power_up_texture, dizzy_power_up_texture, double_power_up_texture;
    sf::Texture game_over_screen_texture;
    sf::Font font;

    float playerSpeed = 3.0f;
    float base_obstacle_speed = 1.0f;
    float base_spawn_interval = 1.0f;
    float total_obstacle_speed = 1.0f;
    float total_spawn_interval = 1.0f;
    float slow_duration = 5.0f;
    float fast_duration = 5.0f;
    float teleport_duration = 8.0f;
    float dizzy_duration = 4.0f;

    int currentLane = 1;
    int score = 0;
    int coins_collected = 0;

    sf::Clock spawnTimer, preyTimer, slow_timer, fast_timer;

    Tamagotchi* pet;
    Player* player;
    sf::RenderWindow* window;

    float lane_switch_time = 0.01f; // Time to complete lane switch
    float lane_transition_progress = 1.0f; // 1.0 means transition complete
    float startX = 0.0f, targetX = 0.0f;
    sf::Clock lane_switch_clock;
    bool is_switching_lanes = false;

    void spawnObstacle(int lane) {
        sf::RectangleShape newObstacle;

        int obstacleType = rand() % 13 + 1;

        if (obstacleType < 9) {
            newObstacle.setTexture(&obstacle_texture_1);
            newObstacle.setSize(sf::Vector2f(8.f, 10.f));
        }
        else if (obstacleType == 10) {
            newObstacle.setTexture(&obstacle_texture_2);
            newObstacle.setSize(sf::Vector2f(8.f, 17.f));
        }
        else if (obstacleType == 11) {
            newObstacle.setTexture(&obstacle_texture_3);
            newObstacle.setSize(sf::Vector2f(8.f, 17.f));
        }
        else if (obstacleType == 12) {
            newObstacle.setTexture(&obstacle_texture_4);
            newObstacle.setSize(sf::Vector2f(8.f, 17.f));
        }
        else if (obstacleType == 13) {
            newObstacle.setTexture(&obstacle_texture_5);
            newObstacle.setSize(sf::Vector2f(8.f, 17.f));
        }
        newObstacle.setPosition({ lane * 21.f + 7.f, -40.f });
        obstacles.push_back(newObstacle);
    }

    void spawnCoin(int lane) {
        sf::RectangleShape newCoin(sf::Vector2f(7.f, 8.f));
        newCoin.setTexture(&coinTexture);
        newCoin.setPosition({ lane * 21.f + 7.f, -72.f });
        obstacles.push_back(newCoin);
    }
    void spawnPowerUp(int lane) {
        sf::RectangleShape new_power_up(sf::Vector2f(7.f, 8.f));
        int powerUpType = rand() % 2;

        if (powerUpType == 0) {
            new_power_up.setTexture(&slow_power_up_texture);
        }
        else {
            new_power_up.setTexture(&fast_power_up_texture);
        }

        new_power_up.setPosition({ lane * 21.f + 7.f, -72.f });
        obstacles.push_back(new_power_up);
    }
    void checkCollisions() {
        bool hitObstacle = false;

        obstacles.erase(std::remove_if(obstacles.begin(), obstacles.end(),
            [&](const sf::RectangleShape& obj) {
                if (obj.getGlobalBounds().findIntersection(player_hitbox.getGlobalBounds())) {
                    if (obj.getTexture() == &obstacle_texture_1 || obj.getTexture() == &obstacle_texture_2 || obj.getTexture() == &obstacle_texture_3 || obj.getTexture() == &obstacle_texture_4 || obj.getTexture() == &obstacle_texture_5) {
                        hitObstacle = true;
                    }
                    else if (obj.getTexture() == &coinTexture) {
                        score += 5;
                        coins_collected++;
                    }
                    else if (obj.getTexture() == &slow_power_up_texture) {
                        slow_power_up_active = true;
                        fast_power_up_active = false;
                        slow_timer.restart();
                    }
                    else if (obj.getTexture() == &fast_power_up_texture) {
                        score += 10;
                        fast_power_up_active = true;
                        slow_power_up_active = false;
                        fast_timer.restart();
                    }
                    return true;
                }
                return false;
            }), obstacles.end());

        if (hitObstacle) {
            stop();
            show_game_over_screen = true;
        }
    }

    void prey_reset() {
        prey.setPosition({ 26.f, 90.f });
    }
    void applySlowPowerUp() {
        if (slow_power_up_active) {
            total_obstacle_speed = 0.6*base_obstacle_speed;
            total_spawn_interval = 1.3*base_spawn_interval;
        }
    }
    void applyFastPowerUp() {
        if (fast_power_up_active) {
            total_obstacle_speed = 1.4f * base_obstacle_speed;
            total_spawn_interval = 0.7f * base_spawn_interval;
        }
    }
    void turnOff() {
        is_on = false;
    }
public:
    MiniGame(Tamagotchi& pet_ref, Player& player_ref, sf::RenderWindow& window_ref) : pet(&pet_ref), player(&player_ref), window(&window_ref), is_running(false), playerSpeed(3.0f), base_obstacle_speed(1.f), score(0), currentLane(1) {
        if (!font.openFromFile("assets/font/font.otf")) {
            std::cerr << "Error loading font!" << std::endl;
        }

        if (!player_dog_texture_1.loadFromFile("minigame/run_dog_1.png") ||
            !player_dog_texture_2.loadFromFile("minigame/run_dog_2.png") ||
            !player_cat_texture_1.loadFromFile("minigame/run_cat_1.png") ||
            !player_cat_texture_2.loadFromFile("minigame/run_cat_2.png") ||
            !background_texture.loadFromFile("backgrounds/minigame.png") ||
            !obstacle_texture_1.loadFromFile("minigame/obstacle_1.png") ||
            !obstacle_texture_2.loadFromFile("minigame/obstacle_2.png") ||
            !obstacle_texture_3.loadFromFile("minigame/obstacle_3.png") ||
            !obstacle_texture_4.loadFromFile("minigame/obstacle_4.png") ||
            !obstacle_texture_5.loadFromFile("minigame/obstacle_5.png") ||
            !coinTexture.loadFromFile("minigame/minigame_coin.png") ||
            !slow_power_up_texture.loadFromFile("minigame/minigame_slow_power_up.png") ||
            !fast_power_up_texture.loadFromFile("minigame/minigame_fast_power_up.png") ||
            !coinTexture.loadFromFile("minigame/minigame_coin.png") ||
            !prey_texture.loadFromFile("minigame/frisbee_1.png") ||
            !game_over_screen_texture.loadFromFile("minigame/game_over_screen.png")) {
            std::cerr << "Error loading textures!" << std::endl;
        }
        player_sprite.setTexture(&player_dog_texture_1);
        player_sprite.setSize(sf::Vector2f(9, 16));
        player_sprite.setPosition({ 28.f, 100.f });

        player_hitbox.setSize(sf::Vector2f(6, 3));
        player_hitbox.setPosition({ player_sprite.getPosition().x + player_sprite.getSize().x * 0.2f, player_sprite.getPosition().y + player_sprite.getSize().y * 0.2f });

        background.setSize(sf::Vector2f(64.f, 248.f));
        background.setTexture(&background_texture);
        background.setPosition({ 0.f, 0.f });
        ui_coin.setSize(sf::Vector2f(7.f, 8.f));
        ui_coin.setTexture(&coinTexture);
        ui_coin.setPosition({ 2, 2 });
        prey.setSize(sf::Vector2f(11.f, 11.f));
        prey.setTexture(&prey_texture);
        prey.setPosition({ 26.f, 90.f });
        exit_button.setPosition({ 26,95 });
        exit_button.setSize({ 12,12 });
    }
    //storing Tamagotchi's reference
    void start() {
        is_on = true;
        is_running = true;
        can_draw = true;
        show_game_over_screen = false;
        reverse_controls = false;
        obstacles.clear();
        score = 0;
        currentLane = 1;
        coins_collected = 0;
        base_obstacle_speed = 1.f;
        base_spawn_interval = 1.f;
        total_obstacle_speed = base_obstacle_speed;
        total_spawn_interval = base_spawn_interval;
        spawnTimer.restart();
        preyTimer.restart();
        prey_active = true;
        prey.setPosition({ 26.f, 90.f });
        if (pet->getType() == "Dog") {
            player_texture_1 = player_dog_texture_1;
            player_texture_2 = player_dog_texture_2;
        }
        else {
            player_texture_1 = player_cat_texture_1;
            player_texture_2 = player_cat_texture_2;
        }
    }

    void stop() {
        is_running = false;
        prey_active = false;
        std::cout << "Game lost! Final Score: " << score << std::endl;
        if (pet && player) {
            player->addCoins(coins_collected);
            pet->setHappiness(pet->getHappiness() + 10 * coins_collected);
            pet->setEnergy(pet->getEnergy() - 4 * coins_collected);

            if (score > player->getMinigameHighscore()) {
                player->setMinigameHighscore(score);
            }
        }
        prey_reset();
        base_obstacle_speed = 0.0f;
        base_spawn_interval = 999.9f;
    }
    void quit() {
        is_running = false;
        prey_reset();
    }

    bool isGameRunning() const { return is_running; }
    bool isGameOn() const { return is_on; }

    void update(float deltaTime) {
        total_obstacle_speed = base_obstacle_speed;
        total_spawn_interval = base_spawn_interval;

        if (slow_power_up_active && slow_timer.getElapsedTime().asSeconds() < slow_duration) {
            applySlowPowerUp();
        }
        else {
            slow_power_up_active = false;
        }

        if (fast_power_up_active && fast_timer.getElapsedTime().asSeconds() < fast_duration) {
            applyFastPowerUp();
        }
        else {
            fast_power_up_active = false;
        }

        if (prey_active) {
            if (deltaTime < 0.3) {
                prey.move({ 0.f, -40.0f * deltaTime });
            }
            if (prey.getPosition().y < -20.f) {
                prey_active = false;
            }
        }

        if (!is_switching_lanes) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && currentLane > 0 && !left_pressed) {
                currentLane--;
                startX = player_sprite.getPosition().x;
                targetX = 7.f + currentLane * 21.f;
                lane_switch_clock.restart();
                lane_transition_progress = 0.0f;
                is_switching_lanes = true;
                left_pressed = true;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && currentLane < 2 && !right_pressed) {
                currentLane++;
                startX = player_sprite.getPosition().x;
                targetX = 7.f + currentLane * 21.f;
                lane_switch_clock.restart();
                lane_transition_progress = 0.0f;
                is_switching_lanes = true;
                right_pressed = true;
            }
        }

        // Handle smooth movement
        if (is_switching_lanes) {
            float elapsed = lane_switch_clock.getElapsedTime().asSeconds();
            lane_transition_progress = elapsed / lane_switch_time;

            if (lane_transition_progress >= 1.0f) {
                lane_transition_progress = 1.0f;
                is_switching_lanes = false;
            }

            float newX = startX + (targetX - startX) * lane_transition_progress;
            player_sprite.setPosition({ newX, player_sprite.getPosition().y });
        }

        // Reset key press states
        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) left_pressed = false;
        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) right_pressed = false;

        static bool isFirstTexture = true;
        static sf::Clock animationClock;
        if (animationClock.getElapsedTime().asSeconds() > 0.15f) {
            player_sprite.setTexture(isFirstTexture ? &player_texture_2 : &player_texture_1);
            isFirstTexture = !isFirstTexture;
            animationClock.restart();
        }

        player_hitbox.setPosition({
            player_sprite.getPosition().x + player_sprite.getSize().x * 0.2f,
            player_sprite.getPosition().y + player_sprite.getSize().y * 0.2f
            });

        if (spawnTimer.getElapsedTime().asSeconds() >= total_spawn_interval) {
            int first_object_lane = rand() % 3;
            int second_object_lane = -1;
            int third_object_lane = -1;

            spawnObstacle(first_object_lane);

            if (rand() % 7 == 0) {
                do { second_object_lane = rand() % 3; } while (first_object_lane == second_object_lane);
                spawnObstacle(second_object_lane);
            }

            if (rand() % 4 == 0) {
                do { third_object_lane = rand() % 3; } while (first_object_lane == third_object_lane || second_object_lane == third_object_lane);
                if (rand() % 10 == 0) {
                    spawnPowerUp(third_object_lane);
                }
                else {
                    spawnCoin(third_object_lane);
                }
            }

            score++;

            if (score % 10 == 0) {
                if (base_obstacle_speed < 3.0f) base_obstacle_speed += 0.1f;
                if (base_spawn_interval > 0.4f) base_spawn_interval -= 0.05f;
            }

            spawnTimer.restart();
        }

        for (auto& obj : obstacles) {
            float speedMultiplier = (obj.getTexture() == &obstacle_texture_2 || obj.getTexture() == &obstacle_texture_3 ||
                obj.getTexture() == &obstacle_texture_4 || obj.getTexture() == &obstacle_texture_5)
                ? 1.2f : 1.0f;
            obj.move({ 0.f, total_obstacle_speed * speedMultiplier * deltaTime * 60 });
        }

        obstacles.erase(std::remove_if(obstacles.begin(), obstacles.end(), [](const sf::RectangleShape& obj) {
            return obj.getPosition().y > 600.f;
            }), obstacles.end());

        background.move({ 0.f, total_obstacle_speed * deltaTime * 60 });
        if (background.getPosition().y >= 0) {
            background.setPosition({ 0.f, -124.f });
        }

        sf::Text coins_collected_text(font, std::to_string(coins_collected));
        sf::Text score_text(font, std::to_string(score));

        coins_collected_text.setCharacterSize(6);
        coins_collected_text.setFillColor(sf::Color::White);
        coins_collected_text.setPosition({ 10, 3 });

        score_text.setCharacterSize(6);
        score_text.setFillColor(sf::Color::White);
        float textWidth = score_text.getLocalBounds().size.x;
        score_text.setPosition({ 64 - textWidth - 2, 3 });

        font.setSmooth(false);
        draw(coins_collected_text, score_text);

        checkCollisions();
    }
    void handle_input(const sf::Event::MouseButtonPressed* mouseButtonPressed) {
        if (mouseButtonPressed->button == sf::Mouse::Button::Left) {
            sf::Vector2f clickPos(static_cast<float>(mouseButtonPressed->position.x / 8), static_cast<float>(mouseButtonPressed->position.y / 8));
            if (show_game_over_screen && exit_button.getGlobalBounds().contains(clickPos)) {
                turnOff();
            }
        }
    }
    void draw(sf::Text& coin_text, sf::Text& score_text) {
        if (can_draw) {
            window->clear(sf::Color::Black);
            window->draw(background);
            window->draw(player_sprite);
            if (true) window->draw(prey);
            for (auto& obj : obstacles) {
                window->draw(obj);
            }
            window->draw(ui_coin);
            window->draw(coin_text);
            window->draw(score_text);
            if (show_game_over_screen) {
                sf::Sprite game_over_screen_sprite(game_over_screen_texture);
                sf::Text coins_collected_text(font, std::to_string(coins_collected));
                sf::Text score_text(font, std::to_string(score));
                sf::Text highscore_text(font, std::to_string(player->getMinigameHighscore()));
                game_over_screen_sprite.setPosition({ 3,12 });
                coins_collected_text.setCharacterSize(6);
                coins_collected_text.setFillColor(sf::Color::White);
                coins_collected_text.setPosition({ 36, 38 });
                score_text.setCharacterSize(6);
                score_text.setFillColor(sf::Color::White);
                score_text.setPosition({ 36, 48 });
                highscore_text.setCharacterSize(6);
                highscore_text.setFillColor(sf::Color::White);
                highscore_text.setPosition({ 36, 58 });
                window->draw(game_over_screen_sprite);
                window->draw(coins_collected_text);
                window->draw(score_text);
                window->draw(highscore_text);
                can_draw = false;
            }
            window->display();
        }
    }
};
#endif