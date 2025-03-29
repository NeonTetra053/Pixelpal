#pragma once
#include <unordered_map>
#include <string>
#include "savedata.h"

class Player {
private:
    int coins;
    std::unordered_map<std::string, int> inventory;
    int minigame_highscore;

public:
    Player() : coins(15), minigame_highscore(0) {
        inventory = {
            {"fish", 0}, {"cat_tin_food", 0}, {"cat_dry_food", 0}, {"milk", 0},
            {"egg", 0}, {"catnip", 0}, {"turkey_leg", 0}, {"dog_tin_food", 0},
            {"broccoli", 0}, {"bone", 0}, {"beef", 0}, {"cookie", 0}
        };
    }

    int getCoins() const { return coins; }
    int getMinigameHighscore() const { return minigame_highscore; }
    void addCoins(int amount) {
        coins += amount;
    }
    void setMinigameHighscore(int amount) {
        minigame_highscore = amount;
    }
    bool spendCoins(int amount) {
        if (coins >= amount) {
            coins -= amount; 
            return true;
        }
        else {
            return false;
        }
    }

    int getAmount(const std::string& type) const {
        auto it = inventory.find(type);
        return (it != inventory.end()) ? it->second : 0;
    }

    void setAmount(const std::string& type, int amount) {
        if (inventory.find(type) != inventory.end()) {
            inventory[type] = amount;
        }
    }

    void addItem(const std::string& type, int amount) {
        if (inventory.find(type) != inventory.end()) {
            inventory[type] += amount;
        }
    }

    void removeItem(const std::string& type, int amount) {
        if (inventory.find(type) != inventory.end()) {
            inventory[type] = std::max(0, inventory[type] - amount);
        }
    }
    std::vector<int> getItemAmounts() const {
        std::vector<int> amounts;
        for (const auto& item : inventory) {
            amounts.push_back(item.second);
        }
        return amounts;
    }
    void toSaveData(SaveData& data) const {
        data.coins = coins;
        data.minigame_highscore = minigame_highscore;
        data.inventory = inventory;
    }
    void fromSaveData(const SaveData& data) {
        coins = data.coins;
        minigame_highscore = data.minigame_highscore;
        inventory = data.inventory;
    }
};