#pragma once
#ifndef TAMAGOTCHI_HPP
#define TAMAGOTCHI_HPP

#include <SFML/Graphics.hpp>
#include "player.h"
#include <iostream>
#include <memory>
#include <string>
class Tamagotchi {
protected:
    int affection;
    int coins;
    int hat;
    float hunger;
    float happiness;
    float energy;
    float hygiene;
    sf::Clock animationClock;
    bool isHappyAnimationActive = false;
    sf::Clock happyAnimationTimer;
    bool isFirstSprite;
    sf::Texture neutralTexture1, neutralTexture2;
    sf::Texture boredTexture1, boredTexture2;
    sf::Texture hungryTexture1, hungryTexture2;
    sf::Texture tiredTexture1, tiredTexture2;
    sf::Texture sleepingTexture1, sleepingTexture2;
    sf::Texture happy_texture_1, happy_texture_2;
    sf::Texture hat_texture;
    sf::Texture hat_texture_0, hat_texture_1, hat_texture_2, hat_texture_3, hat_texture_4, hat_texture_5, hat_texture_6, hat_texture_7, hat_texture_8, hat_texture_9, hat_texture_10, hat_texture_11;
public:
    sf::Vector2f tamagotchi_position = { 16, 64 };
    sf::Vector2f hat_position = { 15, 4 };
    Tamagotchi() : hunger(20), happiness(50), energy(70), hygiene(100), affection(1), coins(0) {
        if (!hat_texture_0.loadFromFile("assets/friend/hats/hat_0.png") ||
            !hat_texture_1.loadFromFile("assets/friend/hats/hat_1.png") ||
            !hat_texture_2.loadFromFile("assets/friend/hats/hat_2.png") ||
            !hat_texture_3.loadFromFile("assets/friend/hats/hat_3.png") ||
            !hat_texture_4.loadFromFile("assets/friend/hats/hat_4.png") ||
            !hat_texture_5.loadFromFile("assets/friend/hats/hat_5.png") ||
            !hat_texture_6.loadFromFile("assets/friend/hats/hat_6.png") ||
            !hat_texture_7.loadFromFile("assets/friend/hats/hat_7.png") ||
            !hat_texture_8.loadFromFile("assets/friend/hats/hat_8.png") ||
            !hat_texture_9.loadFromFile("assets/friend/hats/hat_9.png") ||
            !hat_texture_10.loadFromFile("assets/friend/hats/hat_10.png") ||
            !hat_texture_11.loadFromFile("assets/friend/hats/hat_11.png")) {
            std::cerr << "Failed to load hat menu asset!" << std::endl;
        }
    }
    virtual ~Tamagotchi() {
    }
    virtual std::string getType() const = 0;
    virtual sf::Texture setEmotionSprite(bool is_light_off) { return neutralTexture1; }

    void update();

    void draw(sf::RenderWindow& window);

    int getCoins() const { return coins; }

    float getHunger() const { return hunger; }
    float getHappiness() const { return happiness; }
    float getEnergy() const { return energy; }
    float getHygiene() const { return hygiene; }

    void decreaseStats() {
        decreaseHunger();
        decreaseHappiness();
        decreaseEnergy();
        decreaseHygiene();
    }

    void decreaseHunger() { if (hunger > 0) hunger--; }
    void decreaseHappiness() { if (happiness > 0) happiness--; }
    void decreaseEnergy() { if (energy > 0) energy--; }
    void decreaseHygiene() { if (hygiene > 0) hygiene--; }

    void increaseHunger(float amount) {
        hunger += amount;
        if (hunger > 100) { hunger = 100; }
        isHappyAnimationActive = true;
        happyAnimationTimer.restart();

    }
    void increaseHappiness(float amount) {
        happiness += amount;
        if (happiness > 100) { happiness = 100; }
    }
    void increaseEnergy(float amount) {
        energy += amount;
        if (energy > 100) { energy = 100; }
    }
    void increaseHygiene(float amount) {
        hygiene += amount;
        if (hygiene > 100) { hygiene = 100; }
    }

    void addCoins(int amount) {
        coins += amount;
    }
    void setHunger(int value) {
        hunger = value;
    }
    void setHappiness(int value) {
        happiness = value;
    }
    void setEnergy(int value) {
        energy = value;
    }
    void setHygiene(int value) {
        hygiene = value;
    }

    std::string getHungerState() const {
        if (hunger > 50) {
            return "green";
        }
        else if (hunger > 15) {
            return "yellow";
        }
        else {
            return "red";
        }
    }

    std::string getHappinessState() const {
        if (happiness > 50) {
            return "green";
        }
        else if (happiness > 15) {
            return "yellow";
        }
        else {
            return "red";
        }
    }

    std::string getEnergyState() const {
        if (energy > 50) {
            return "green";
        }
        else if (energy > 15) {
            return "yellow";
        }
        else {
            return "red";
        }
    }

    std::string getHygieneState() const {
        if (hygiene > 50) {
            return "green";
        }
        else if (hygiene > 15) {
            return "yellow";
        }
        else {
            return "red";
        }
    }

    std::string getEmotion() const {
        if (energy < 15) {
            return "tired";
        }
        if (hunger < 15) {
            return "hungry";
        }
        if (happiness < 15) {
            return "bored";
        }

        return "neutral";
    }
    void needs_update(bool is_light_off) {
        decreaseHappiness();
        decreaseHunger();
        decreaseHygiene();
        if (is_light_off) {
            increaseEnergy(1.5);
        }
        else {
            decreaseEnergy();
        }
    }
    void setHat(int option) {
        switch (option) {
        case 0:
            hat_texture = hat_texture_0;
            break;
        case 1:
            hat_texture = hat_texture_1;
            break;
        case 2:
            hat_texture = hat_texture_2;
            break;
        case 3:
            hat_texture = hat_texture_3;
            break;
        case 4:
            hat_texture = hat_texture_4;
            break;
        case 5:
            hat_texture = hat_texture_5;
            break;
        case 6:
            hat_texture = hat_texture_6;
            break;
        case 7:
            hat_texture = hat_texture_7;
            break;
        case 8:
            hat_texture = hat_texture_8;
            break;
        case 9:
            hat_texture = hat_texture_9;
            break;
        case 10:
            hat_texture = hat_texture_10;
            break;
        case 11:
            hat_texture = hat_texture_11;
            break;
        }
        hat = option;
    }
    void draw(sf::RenderWindow& window, bool is_light_off) {
        sf::Texture tamagotchi_texture = setEmotionSprite(is_light_off);
        sf::Sprite tamagotchi_sprite(tamagotchi_texture);
        sf::Sprite hat_sprite(hat_texture);
        hat_sprite.setPosition(tamagotchi_position - hat_position);
        tamagotchi_sprite.setPosition(tamagotchi_position);

        window.draw(tamagotchi_sprite);
        window.draw(hat_sprite);
    }
    virtual void toSaveData(SaveData& data) const {
        data.hunger = hunger;
        data.happiness = happiness;
        data.energy = energy;
        data.hygiene = hygiene;
        data.affection = affection;
        data.pet_type = getType();
        data.current_hat = hat;
    }
    virtual void fromSaveData(const SaveData& data) {
        hunger = data.hunger;
        happiness = data.happiness;
        energy = data.energy;
        hygiene = data.hygiene;
        affection = data.affection;
        hat = data.current_hat;
        setHat(hat);
    }
};

class Dog : public Tamagotchi {
private:

public:
    Dog() : Tamagotchi() {
        isFirstSprite = true;
        loadTextures();
        std::cout << "Dog created!" << std::endl;
    }

    ~Dog() {
        std::cout << "Dog destroyed!" << std::endl;
    }

    std::string getType() const override { return "Dog"; }

    void loadTextures() {
        neutralTexture1.loadFromFile("assets/friend/dog/dog_neutral_1.png");
        neutralTexture2.loadFromFile("assets/friend/dog/dog_neutral_2.png");
        boredTexture1.loadFromFile("assets/friend/dog/dog_bored_1.png");
        boredTexture2.loadFromFile("assets/friend/dog/dog_bored_2.png");
        hungryTexture1.loadFromFile("assets/friend/dog/dog_hungry_1.png");
        hungryTexture2.loadFromFile("assets/friend/dog/dog_hungry_2.png");
        tiredTexture1.loadFromFile("assets/friend/dog/dog_tired_1.png");
        tiredTexture2.loadFromFile("assets/friend/dog/dog_tired_2.png");
        sleepingTexture1.loadFromFile("assets/friend/dog/dog_sleeping_1.png");
        sleepingTexture2.loadFromFile("assets/friend/dog/dog_sleeping_2.png");
        happy_texture_1.loadFromFile("assets/friend/dog/dog_happy_1.png");
        happy_texture_2.loadFromFile("assets/friend/dog/dog_happy_2.png");
    }

    sf::Texture setEmotionSprite(bool is_light_off) override {
        if (animationClock.getElapsedTime().asSeconds() >= 0.7f) {
            isFirstSprite = !isFirstSprite;
            animationClock.restart();
        }

        sf::Texture* texture = nullptr;
        if (isHappyAnimationActive && happyAnimationTimer.getElapsedTime().asSeconds() < 2.0f) {
            texture = isFirstSprite ? &happy_texture_1 : &happy_texture_2;
            hat_position = { 0, 7 };
        }
        else {
            isHappyAnimationActive = false;

            std::string emotion = getEmotion();
            if (is_light_off) {
                texture = isFirstSprite ? &sleepingTexture1 : &sleepingTexture2;
                hat_position = isFirstSprite ? sf::Vector2f{ 0,6 } : sf::Vector2f{ 0,5 };
            }
            else if (emotion == "neutral") {
                texture = isFirstSprite ? &neutralTexture1 : &neutralTexture2;
                hat_position = { 0,7 };
            }
            else if (emotion == "bored") {
                if (getHungerState() != "red") {
                    texture = isFirstSprite ? &boredTexture1 : &boredTexture2;
                    hat_position = { 0,7 };
                }
                else {
                    texture = isFirstSprite ? &hungryTexture1 : &hungryTexture2;
                    hat_position = isFirstSprite ? sf::Vector2f{ 0,6 } : sf::Vector2f{ 0,5 };
                }
            }
            else if (emotion == "tired") {
                texture = getHungerState() != "red" ? &tiredTexture1 : &tiredTexture2;
                hat_position = { 0,6 };
            }
            else if (emotion == "hungry") {
                texture = isFirstSprite ? &hungryTexture1 : &hungryTexture2;
                hat_position = isFirstSprite ? sf::Vector2f{ 0,6 } : sf::Vector2f{ 0,5 };
            }
        }

        return *texture;
    }
};


class Cat : public Tamagotchi {
public:
    Cat() : Tamagotchi() {
        isFirstSprite = true;
        loadTextures();
        std::cout << "Cat created!" << std::endl;
    }

    ~Cat() {
        std::cout << "Cat destroyed!" << std::endl;
    }

    std::string getType() const override { return "Cat"; }

    void loadTextures() {
        neutralTexture1.loadFromFile("assets/friend/cat/cat_neutral_1.png");
        neutralTexture2.loadFromFile("assets/friend/cat/cat_neutral_2.png");
        boredTexture1.loadFromFile("assets/friend/cat/cat_bored_1.png");
        boredTexture2.loadFromFile("assets/friend/cat/cat_bored_2.png");
        hungryTexture1.loadFromFile("assets/friend/cat/cat_hungry_1.png");
        hungryTexture2.loadFromFile("assets/friend/cat/cat_hungry_2.png");
        tiredTexture1.loadFromFile("assets/friend/cat/cat_tired_1.png");
        tiredTexture2.loadFromFile("assets/friend/cat/cat_tired_2.png");
        sleepingTexture1.loadFromFile("assets/friend/cat/cat_sleeping_1.png");
        sleepingTexture2.loadFromFile("assets/friend/cat/cat_sleeping_2.png");
    }

    sf::Texture setEmotionSprite(bool is_light_off) override {
        if (animationClock.getElapsedTime().asSeconds() >= 0.7f) {
            isFirstSprite = !isFirstSprite;
            animationClock.restart();
        }

        std::string emotion = getEmotion();
        sf::Texture* texture = nullptr;

        if (is_light_off) {
            texture = isFirstSprite ? &sleepingTexture1 : &sleepingTexture2;
            hat_position = isFirstSprite ? sf::Vector2f{ 0,6 } : sf::Vector2f{ 0,5 };
        }
        else if (emotion == "neutral") {
            texture = isFirstSprite ? &neutralTexture1 : &neutralTexture2;
            hat_position = { 0,7 };
        }
        else if (emotion == "bored") {
            if (getHungerState() != "red") {
                texture = isFirstSprite ? &boredTexture1 : &boredTexture2;
                hat_position = { 0,7 };
            }
            else {
                texture = isFirstSprite ? &hungryTexture1 : &hungryTexture2;
                hat_position = isFirstSprite ? sf::Vector2f{ 0,6 } : sf::Vector2f{ 0,5 };
            }
        }
        else if (emotion == "tired") {
            if (getHungerState() != "red") {
                texture = &tiredTexture1;
            }
            else {
                texture = &tiredTexture2;
            }
            hat_position = { 0,4 };
        }
        else if (emotion == "hungry") {
            texture = isFirstSprite ? &hungryTexture1 : &hungryTexture2;
            hat_position = isFirstSprite ? sf::Vector2f{ 0,6 } : sf::Vector2f{ 0,5 };
        }

        if (texture) {
            return *texture;
        }
    }
};

class Shop {
private:
    sf::Texture dogShopTexture;
    sf::Texture catShopTexture;
    bool is_open;
    int type;
    int shop_coins;
    sf::Font font;
    sf::RectangleShape button_1, button_2, button_3, button_4, button_5, button_6;
    int shop_prices[6] = { 3, 4, 5, 5, 7, 20 };
    std::string dog_items[6] = { "turkey_leg", "dog_tin_food", "broccoli", "bone", "beef", "cookie" };
    std::string cat_items[6] = { "fish", "cat_tin_food", "cat_dry_food", "milk", "egg", "catnip" };
    std::string shop_items[6];
    Player* player;
    Tamagotchi* pet;
    sf::RenderWindow* window;

public:
    Shop(Tamagotchi& pet_ref, Player& player_ref, sf::RenderWindow& window_ref) : is_open(false), pet(&pet_ref), player(&player_ref), window(&window_ref) {
        if (!dogShopTexture.loadFromFile("ui/shop_dog.png") ||
            !catShopTexture.loadFromFile("ui/shop_cat.png") ||
            !font.openFromFile("assets/font/font.otf")) {
            std::cerr << "Failed to load shop asset!" << std::endl;
        }
        button_1.setSize({ 53, 16 });
        button_2.setSize({ 53, 16 });
        button_3.setSize({ 53, 16 });
        button_4.setSize({ 53, 16 });
        button_5.setSize({ 53, 16 });
        button_6.setSize({ 53, 16 });
        button_1.setPosition({ 7, 28 });
        button_2.setPosition({ 7, 42 });
        button_3.setPosition({ 7, 58 });
        button_4.setPosition({ 7, 74 });
        button_5.setPosition({ 7, 90 });
        button_6.setPosition({ 7, 106 });

    }

    void open() {
        is_open = true;
        if (pet->getType() == "Dog") {
            type = 1;
        }
        else if (pet->getType() == "Cat") {
            type = 2;
        }
        shop_coins = player->getCoins();
    }

    void buy_item(int choice) {
        if (player->spendCoins(shop_prices[choice - 1])) {
            shop_coins = player->getCoins();
            switch (type) {
            case 1:
                player->addItem(dog_items[choice - 1], 1);
            case 2:
                player->addItem(cat_items[choice - 1], 1);
            }
        }
        else {
            std::cout << "youre too broke, L" << std::endl;
        }
        
    }
    void close() { is_open = false; }

    bool isShopOpen() const { return is_open; }

    void handle_input(const sf::Event::MouseButtonPressed* mouseButtonPressed) {
        if (mouseButtonPressed->button == sf::Mouse::Button::Left) {
            if (button_1.getGlobalBounds().contains(sf::Vector2f(static_cast<float>(mouseButtonPressed->position.x / 8), static_cast<float>(mouseButtonPressed->position.y / 8)))) {
                std::cout << "pressed shop button 1" << std::endl;
                buy_item(1);
            }
            else if (button_2.getGlobalBounds().contains(sf::Vector2f(static_cast<float>(mouseButtonPressed->position.x / 8), static_cast<float>(mouseButtonPressed->position.y / 8)))) {
                std::cout << "pressed shop button 2" << std::endl;
                buy_item(2);
            }
            else if (button_3.getGlobalBounds().contains(sf::Vector2f(static_cast<float>(mouseButtonPressed->position.x / 8), static_cast<float>(mouseButtonPressed->position.y / 8)))) {
                std::cout << "pressed shop button 3" << std::endl;
                buy_item(3);
            }
            else if (button_4.getGlobalBounds().contains(sf::Vector2f(static_cast<float>(mouseButtonPressed->position.x / 8), static_cast<float>(mouseButtonPressed->position.y / 8)))) {
                std::cout << "pressed shop button 4" << std::endl;
                buy_item(4);
            }
            else if (button_5.getGlobalBounds().contains(sf::Vector2f(static_cast<float>(mouseButtonPressed->position.x / 8), static_cast<float>(mouseButtonPressed->position.y / 8)))) {
                std::cout << "pressed shop button 5" << std::endl;
                buy_item(5);
            }
            else if (button_6.getGlobalBounds().contains(sf::Vector2f(static_cast<float>(mouseButtonPressed->position.x / 8), static_cast<float>(mouseButtonPressed->position.y / 8)))) {
                std::cout << "pressed shop button 6" << std::endl;
                buy_item(6);
            }
        }
    }
    void draw(sf::RenderWindow& window) {
        if (is_open) {
            sf::Sprite shopSprite(dogShopTexture);
            if (type == 1){
                shopSprite.setTexture(dogShopTexture);
            }
            else if (type == 2) {
                shopSprite.setTexture(catShopTexture);
            }
            shopSprite.setPosition({ 3,23 });
            sf::Text coin_amount(font, "Coins: " + std::to_string(shop_coins));
            coin_amount.setCharacterSize(6);
            coin_amount.setFillColor(sf::Color::White);
            coin_amount.setPosition({ 13, 15 });
            font.setSmooth(false);
            window.draw(coin_amount);
            window.draw(shopSprite);
        }
    }
};
class FeedMenu {
private:
    sf::Texture dogFeedTexture;
    sf::Texture catFeedTexture;
    bool isOpen;
    int type;
    sf::Font font;
    sf::RectangleShape button_1, button_2, button_3, button_4, button_5, button_6;
    std::vector<int> item_quantities;
    Player* player;
    Tamagotchi* pet;
    sf::RenderWindow* window;
    std::string dog_items[6] = { "turkey_leg", "dog_tin_food", "broccoli", "bone", "beef", "cookie" };
    std::string cat_items[6] = { "fish", "cat_tin_food", "cat_dry_food", "milk", "egg", "catnip" };

public:
    FeedMenu(Tamagotchi& pet_ref, Player& player_ref, sf::RenderWindow& window_ref) : isOpen(false), pet(&pet_ref), player(&player_ref), window(&window_ref) {
        if (!dogFeedTexture.loadFromFile("ui/dog_feed_menu.png") ||
            !catFeedTexture.loadFromFile("ui/cat_feed_menu.png") ||
            !font.openFromFile("assets/font/font.otf")) {
            std::cerr << "Failed to load feed menu asset!" << std::endl;
        }

        button_1.setSize({ 15, 13 });
        button_2.setSize({ 15, 13 });
        button_3.setSize({ 15, 13 });
        button_4.setSize({ 15, 13 });
        button_5.setSize({ 15, 13 });
        button_6.setSize({ 15, 13 });

        button_1.setPosition({ 7, 28 });
        button_2.setPosition({ 24, 28 });
        button_3.setPosition({ 41, 28 });
        button_4.setPosition({ 7, 43 });
        button_5.setPosition({ 24, 43 });
        button_6.setPosition({ 41, 43 });
    }

    void open() {
        isOpen = true;
        type = (pet->getType() == "Dog") ? 1 : 2;
        switch (type) {
        case 1:
            item_quantities = { player->getAmount("turkey_leg"), player->getAmount("dog_tin_food"), player->getAmount("broccoli"), player->getAmount("bone"), player->getAmount("beef"), player->getAmount("cookie") };
        case 2:
            item_quantities = { player->getAmount("turkey_leg"), player->getAmount("dog_tin_food"), player->getAmount("broccoli"), player->getAmount("bone"), player->getAmount("beef"), player->getAmount("cookie") };
        }

    }

    void feedPet(int choice) {
        if (choice - 1 < item_quantities.size()) {
            switch (type) {
            case 1:
                if (player->getAmount(dog_items[choice - 1])) {
                    player->removeItem(dog_items[choice - 1], 1);
                    std::cout << "Fed pet with " << dog_items[choice - 1] << std::endl;
                    switch (choice) {
                        case 1:
                             pet->increaseHunger(25);
                             pet->increaseHappiness(5);
                             break;
                        case 2:
                            pet->increaseHunger(30);
                            pet->increaseHappiness(10);
                            break;
                        case 3:
                            pet->increaseHunger(40);
                            pet->increaseHappiness(5);
                            break;
                        case 4:
                            pet->increaseHunger(20);
                            pet->increaseHappiness(20);
                            break;
                        case 5:
                            pet->increaseHunger(50);
                            pet->increaseHappiness(15);
                            break;
                        case 6:
                            pet->increaseHunger(10);
                            pet->increaseHappiness(90);
                            break;
                    }
                    close();
                }
            case 2:
                if (player->getAmount(cat_items[choice - 1])) {
                    player->removeItem(cat_items[choice - 1], 1);
                    std::cout << "Fed pet with " << cat_items[choice - 1] << std::endl;
                    switch (choice) {
                    case 1:
                        pet->increaseHunger(25);
                        pet->increaseHappiness(5);
                        break;
                    case 2:
                        pet->increaseHunger(30);
                        pet->increaseHappiness(10);
                        break;
                    case 3:
                        pet->increaseHunger(40);
                        pet->increaseHappiness(5);
                        break;
                    case 4:
                        pet->increaseHunger(20);
                        pet->increaseHappiness(20);
                        break;
                    case 5:
                        pet->increaseHunger(50);
                        pet->increaseHappiness(15);
                        break;
                    case 6:
                        pet->increaseHunger(10);
                        pet->increaseHappiness(90);
                        break;
                    }
                    close();
                }
            }
        }
        else {
            std::cout << "Invalid choice!" << std::endl;
        }
    }

    void close() { isOpen = false; }
    bool isFeedMenuOpen() const { return isOpen; }

    void handle_input(const sf::Event::MouseButtonPressed* mouseButtonPressed) {
        if (mouseButtonPressed->button == sf::Mouse::Button::Left) {
            sf::Vector2f clickPos(static_cast<float>(mouseButtonPressed->position.x / 8), static_cast<float>(mouseButtonPressed->position.y / 8));
            if (button_1.getGlobalBounds().contains(clickPos)) feedPet(1);
            else if (button_2.getGlobalBounds().contains(clickPos)) feedPet(2);
            else if (button_3.getGlobalBounds().contains(clickPos)) feedPet(3);
            else if (button_4.getGlobalBounds().contains(clickPos)) feedPet(4);
            else if (button_5.getGlobalBounds().contains(clickPos)) feedPet(5);
            else if (button_6.getGlobalBounds().contains(clickPos)) feedPet(6);
        }
    }

    void draw() {
        if (isOpen) {
            sf::Sprite feedSprite(type == 1 ? dogFeedTexture : catFeedTexture);
            feedSprite.setPosition({ 3,23 });
            window->draw(feedSprite);

            font.setSmooth(false);
                sf::Text item_text(font, std::to_string(item_quantities[0]) + "    " + std::to_string(item_quantities[1]) + "    " + std::to_string(item_quantities[2]), 6);
                item_text.setFillColor(sf::Color::White);
                item_text.setPosition({ 16, 35 });
                window->draw(item_text);
                sf::Text item_text2(font, std::to_string(item_quantities[3]) + "    " + std::to_string(item_quantities[4]) + "    " + std::to_string(item_quantities[5]), 6);
                item_text2.setFillColor(sf::Color::White);
                item_text2.setPosition({ 16, 50 });
                window->draw(item_text2);
        }
    }
};
class HatMenu {
private:
    sf::Texture hat_menu_texture;
    bool is_open;
    sf::RectangleShape button_1, button_2, button_3, button_4, button_5, button_6, button_7, button_8, button_9, button_10, button_11, button_12;
    Tamagotchi* pet;
    sf::RenderWindow* window;

public:
    HatMenu(Tamagotchi& pet_ref, sf::RenderWindow& window_ref) : is_open(false), pet(&pet_ref), window(&window_ref) {
        if (!hat_menu_texture.loadFromFile("ui/hat_menu.png")){
            std::cerr << "Failed to load hat menu asset!" << std::endl;
        }

        button_1.setSize({ 15, 13 });
        button_2.setSize({ 15, 13 });
        button_3.setSize({ 15, 13 });
        button_4.setSize({ 15, 13 });
        button_5.setSize({ 15, 13 });
        button_6.setSize({ 15, 13 });
        button_7.setSize({ 15, 13 });
        button_8.setSize({ 15, 13 });
        button_9.setSize({ 15, 13 });
        button_10.setSize({ 15, 13 });
        button_11.setSize({ 15, 13 });
        button_12.setSize({ 15, 13 });

        button_1.setPosition({ 7, 28 });
        button_2.setPosition({ 24, 28 });
        button_3.setPosition({ 41, 28 });
        button_4.setPosition({ 7, 43 });
        button_5.setPosition({ 24, 43 });
        button_6.setPosition({ 41, 43 });
        button_7.setPosition({ 7, 58 });
        button_8.setPosition({ 24, 58 });
        button_9.setPosition({ 41, 58 });
        button_10.setPosition({ 7, 73 });
        button_11.setPosition({ 24, 73 });
        button_12.setPosition({ 41, 73 });
    }

    void open() {
        is_open = true;
    }

    void giveHat(int option) {
        pet->setHat(option);
        close();
    }

    void close() { is_open = false; }
    bool isHatMenuOpen() const { return is_open; }

    void handle_input(const sf::Event::MouseButtonPressed* mouseButtonPressed) {
        if (mouseButtonPressed->button == sf::Mouse::Button::Left) {
            sf::Vector2f clickPos(static_cast<float>(mouseButtonPressed->position.x / 8), static_cast<float>(mouseButtonPressed->position.y / 8));
            if (button_1.getGlobalBounds().contains(clickPos)) giveHat(0);
            else if (button_2.getGlobalBounds().contains(clickPos)) giveHat(1);
            else if (button_3.getGlobalBounds().contains(clickPos)) giveHat(2);
            else if (button_4.getGlobalBounds().contains(clickPos)) giveHat(3);
            else if (button_5.getGlobalBounds().contains(clickPos)) giveHat(4);
            else if (button_6.getGlobalBounds().contains(clickPos)) giveHat(5);
            else if (button_7.getGlobalBounds().contains(clickPos)) giveHat(6);
            else if (button_8.getGlobalBounds().contains(clickPos)) giveHat(7);
            else if (button_9.getGlobalBounds().contains(clickPos)) giveHat(8);
            else if (button_10.getGlobalBounds().contains(clickPos)) giveHat(9);
            else if (button_11.getGlobalBounds().contains(clickPos)) giveHat(10);
            else if (button_12.getGlobalBounds().contains(clickPos)) giveHat(11);
        }
    }

    void draw() {
        if (is_open) {
            sf::Sprite hat_menu_sprite(hat_menu_texture);
            hat_menu_sprite.setPosition({ 3,23 });
            window->draw(hat_menu_sprite);
        }
    }
};

class AffectionMenu {
private:
    sf::Texture affection_menu_texture;
    bool is_open;
    sf::Font font;
    sf::RectangleShape button_1, button_2, button_3, button_4, button_5, button_6;
    Tamagotchi* pet;
    sf::RenderWindow* window;


public:
    AffectionMenu(Tamagotchi& pet_ref, sf::RenderWindow& window_ref) : is_open(false), pet(&pet_ref), window(&window_ref) {
        if (!affection_menu_texture.loadFromFile("ui/affection_menu.png") ||
            !font.openFromFile("assets/font/font.otf")) {
            std::cerr << "Failed to load hat menu asset!" << std::endl;
        }
        pet = &pet_ref;
        button_1.setSize({ 15, 13 });
        button_2.setSize({ 15, 13 });
        button_3.setSize({ 15, 13 });
        button_4.setSize({ 15, 13 });
        button_5.setSize({ 15, 13 });
        button_6.setSize({ 15, 13 });

        button_1.setPosition({ 7, 28 });
        button_2.setPosition({ 24, 28 });
        button_3.setPosition({ 41, 28 });
        button_4.setPosition({ 7, 43 });
        button_5.setPosition({ 24, 43 });
        button_6.setPosition({ 41, 43 });
    }

    void open() {
        is_open = true;
    }

    void close() { is_open = false; }
    bool isAffectionMenuOpen() const { return is_open; }

    void handle_input(const sf::Event::MouseButtonPressed* mouseButtonPressed) {
        if (mouseButtonPressed->button == sf::Mouse::Button::Left) {
            sf::Vector2f clickPos(static_cast<float>(mouseButtonPressed->position.x / 8), static_cast<float>(mouseButtonPressed->position.y / 8));
            
        }
    }

    void draw() {
        if (is_open) {
            sf::Sprite hat_menu_sprite(affection_menu_texture);
            hat_menu_sprite.setPosition({ 3,23 });
            window->draw(hat_menu_sprite);
        }
    }
};
#endif