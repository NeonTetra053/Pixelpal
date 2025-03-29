#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <map>
#include <string>
#include "Tamagotchi.hpp"
#include "minigame.h"
#include "player.h"
#include "savedata.h"

class Game {
private:
    sf::RenderWindow window;
    sf::View view;
    sf::Clock statClock;
    sf::Clock gameClock;
    sf::Clock deltaClock;

    Player player;
    Dog myPet;
    Shop shop;
    MiniGame miniGame;
    FeedMenu feed_menu;
    HatMenu hat_menu;
    AffectionMenu affection_menu;

    int room;
    bool is_light_off;

    // Tekstury i UI
    sf::Texture hunger, hygiene, energy, happiness;
    sf::Texture background, background_2, background_3, background_4, background_5;
    sf::Texture light_off_texture;
    sf::Font font;
    sf::Text text;
    sf::Texture ui;
    sf::Texture tamagotchi_texture;
    sf::Texture action_button_frame;
    sf::Texture activity_texture_1, activity_texture_2, activity_texture_3, activity_texture_4, activity_texture_5;
    sf::Texture hat_texture;

    sf::RectangleShape activity_button;
    sf::RectangleShape shop_button;
    sf::RectangleShape heart_button;

    sf::Sprite hungerIcon, hygieneIcon, energyIcon, happinessIcon;
    sf::Sprite background_sprite, light_off_sprite, ui_sprite;
    sf::Sprite action_button, activity_icon;

    void processEvents();
    void update();
    void render();
    bool loadAssets();

public:
    Game();
    void run();
    void saveGame() {
        if (SaveManager::saveGame("save.json", player, myPet)) {
            std::cout << "Game saved successfully to save.json!" << std::endl;
        }
        else {
            std::cerr << "Failed to save game!" << std::endl;
        }
    }

    void loadGame() {
        if (SaveManager::loadGame("save.json", player, myPet)) {
            std::cout << "Game loaded successfully from save.json!" << std::endl;
        }
        else {
            std::cerr << "No save file found or error loading!" << std::endl;
        }
    }
};

Game::Game()
    : window(sf::VideoMode({ 64 * 8, 126 * 8 }), "Pixelpal"),
    shop(myPet, player, window),
    miniGame(myPet, player, window),
    feed_menu(myPet, player, window),
    hat_menu(myPet, window),
    affection_menu(myPet, window),
    room(0),
    is_light_off(false){

    window.setPosition(sf::Vector2i(0, 0));
    view = window.getView();
    view.setSize({ 64.f, 126.f });
    view.setCenter({ 64.f / 2, 126.f / 2 });

    text.setFont(font);
    text.setCharacterSize(6);
    text.setFillColor(sf::Color::White);
    text.setPosition({ 20, 20 });

    if (!loadAssets()) {
        std::cerr << "Error loading assets!" << std::endl;
    }
}

bool Game::loadAssets() {
    return background.loadFromFile("backgrounds/living_room.png") &&
        background_2.loadFromFile("backgrounds/kitchen.png") &&
        background_3.loadFromFile("backgrounds/bathroom.png") &&
        background_4.loadFromFile("backgrounds/outside.png") &&
        background_5.loadFromFile("backgrounds/wardrobe.png") &&
        light_off_texture.loadFromFile("backgrounds/light_off.png") &&
        font.openFromFile("assets/font/font.otf") &&
        ui.loadFromFile("ui/hud.png") &&
        action_button_frame.loadFromFile("ui/action_button.png") &&
        hunger.loadFromFile("icons/hunger_green.png") &&
        hygiene.loadFromFile("icons/hygiene_green.png") &&
        energy.loadFromFile("icons/energy_green.png") &&
        happiness.loadFromFile("icons/happiness_green.png") &&
        activity_texture_1.loadFromFile("ui/activity_icon_1.png") &&
        activity_texture_2.loadFromFile("ui/activity_icon_2.png") &&
        activity_texture_3.loadFromFile("ui/activity_icon_3.png") &&
        activity_texture_4.loadFromFile("ui/activity_icon_4.png") &&
        activity_texture_5.loadFromFile("ui/activity_icon_5.png") &&
        hat_texture.loadFromFile("assets/friend/hats/hat_1.png") &&
        tamagotchi_texture.loadFromFile("assets/friend/dog_happy_1.png");
}

void Game::run() {
    while (window.isOpen()) {
        processEvents();
        update();
        render();
    }
}

void Game::processEvents() {
    while (const std::optional event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>())
            window.close();
        if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            if (keyPressed->code == sf::Keyboard::Key::Num5) {
                if (!miniGame.isGameOn()) {
                    miniGame.start();
                }
                else {
                    miniGame.quit();
                }
                std::cout << "Mini-game: " << (miniGame.isGameOn() ? "ON" : "OFF") << std::endl;
            }
            if (keyPressed->code == sf::Keyboard::Key::F5) {
                if (SaveManager::saveGame("save.json", player, myPet)) {
                    std::cout << "Game saved successfully!" << std::endl;
                }
            }
            else if (keyPressed->code == sf::Keyboard::Key::F9) {
                if (SaveManager::loadGame("save.json", player, myPet)) {
                    std::cout << "Game loaded successfully!" << std::endl;
                }
            }
        }
        if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>()) {

            if (mouseButtonPressed->button == sf::Mouse::Button::Left) {
                if (mouseButtonPressed->position.x >= 1 && mouseButtonPressed->position.x <= 10 * 8 && mouseButtonPressed->position.y >= 13 * 8 && mouseButtonPressed->position.y <= 21 * 8) {
                    room = (room - 1 + 5) % 5;
                    is_light_off = false;
                    if (feed_menu.isFeedMenuOpen()) {
                        feed_menu.close();
                    }
                }
                if (mouseButtonPressed->position.x >= 53 * 8 && mouseButtonPressed->position.x <= 63 * 8 && mouseButtonPressed->position.y >= 13 * 8 && mouseButtonPressed->position.y <= 21 * 8) {
                    room = (room + 1) % 5;
                    is_light_off = false;
                    if (feed_menu.isFeedMenuOpen()) {
                        feed_menu.close();
                    }
                }
                if (mouseButtonPressed->position.x >= 52 * 8 && mouseButtonPressed->position.x <= 62 * 8 && mouseButtonPressed->position.y >= 2 * 8 && mouseButtonPressed->position.y <= 8 * 8) {
                    is_light_off = false;
                    if (feed_menu.isFeedMenuOpen()) {
                        feed_menu.close();
                    }
                    if (shop.isShopOpen()) {
                        shop.close();
                    }
                    else {
                        shop.open();
                    }
                }
                /*if (!affection_menu.isAffectionMenuOpen()) {
                    affection_menu.open();
                }*/
                if (shop.isShopOpen()) {
                    shop.handle_input(mouseButtonPressed);
                }
                else if (activity_button.getGlobalBounds().contains(sf::Vector2f(static_cast<float>(mouseButtonPressed->position.x / 8),
                    static_cast<float>(mouseButtonPressed->position.y / 8)))) {
                    std::cout << "pressed activity button" << std::endl;
                    switch (room) {
                    case 0:
                        is_light_off = !is_light_off;
                        break;
                    case 1:
                        if (feed_menu.isFeedMenuOpen()) {
                            feed_menu.close();
                        }
                        else {
                            feed_menu.open();
                        }
                        break;
                    case 2:
                        myPet.setHygiene(100);
                        break;
                    case 3:
                        if (!miniGame.isGameOn()) {
                            miniGame.start();
                        }
                        else {
                            miniGame.stop();
                        }
                        break;
                    case 4:
                        if (hat_menu.isHatMenuOpen()) {
                            hat_menu.close();
                        }
                        else {
                            hat_menu.open();
                        }
                    }
                }

                if (feed_menu.isFeedMenuOpen()) {
                    feed_menu.handle_input(mouseButtonPressed);
                }
                if (hat_menu.isHatMenuOpen()) {
                    hat_menu.handle_input(mouseButtonPressed);
                }
                if (miniGame.isGameOn()) {
                    miniGame.handle_input(mouseButtonPressed);
                }
                std::cout << "Mouse x: " << mouseButtonPressed->position.x / 8 << std::endl;
                std::cout << "Mouse y: " << mouseButtonPressed->position.y / 8 << std::endl;
            }
        }
    }
    if (statClock.getElapsedTime().asSeconds() >= 1.2f) {
        myPet.needs_update(is_light_off);
        statClock.restart();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1)) {
        myPet.setHunger(100);
        std::cout << "Hunger set to 100!" << std::endl;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2)) {
        myPet.setHappiness(100);
        std::cout << "Hunger set to 100!" << std::endl;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num3)) {
        myPet.setEnergy(100);
        std::cout << "Hunger set to 100!" << std::endl;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num4)) {
        myPet.setHygiene(100);
        std::cout << "Hunger set to 100!" << std::endl;
    }
}

void Game::update() {
    if (statClock.getElapsedTime().asSeconds() >= 1.2f) {
        myPet.needs_update(is_light_off);
        statClock.restart();
    }

    if (!hunger.loadFromFile("icons/hunger_" + myPet.getHungerState() + ".png") ||
        !hygiene.loadFromFile("icons/hygiene_" + myPet.getHygieneState() + ".png") ||
        !energy.loadFromFile("icons/energy_" + myPet.getEnergyState() + ".png") ||
        !happiness.loadFromFile("icons/happiness_" + myPet.getHappinessState() + ".png")) {
        return;
    }
    hungerIcon.setTexture(hunger);
    hygieneIcon.setTexture(hygiene);
    energyIcon.setTexture(energy);
    happinessIcon.setTexture(happiness);

    switch (room) {
    case 0:
        background_sprite.setTexture(background);
        activity_icon.setTexture(activity_texture_1);
        break;
    case 1:
        background_sprite.setTexture(background_2);
        activity_icon.setTexture(activity_texture_2);
        break;
    case 2:
        background_sprite.setTexture(background_3);
        activity_icon.setTexture(activity_texture_3);
        break;
    case 3:
        background_sprite.setTexture(background_4);
        activity_icon.setTexture(activity_texture_4);
        break;
    case 4:
        background_sprite.setTexture(background_5);
        activity_icon.setTexture(activity_texture_5);
        break;
    }
}

void Game::render() {
    window.clear();
    window.draw(background_sprite);
    myPet.draw(window, is_light_off);

    if (is_light_off) {
        window.draw(light_off_sprite);
    }

    window.draw(ui_sprite);
    window.draw(hungerIcon);
    window.draw(happinessIcon);
    window.draw(hygieneIcon);
    window.draw(energyIcon);
    window.draw(action_button);
    window.draw(activity_icon);

    shop.draw(window);
    feed_menu.draw();
    hat_menu.draw();
    affection_menu.draw();

    window.display();
}