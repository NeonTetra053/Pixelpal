#pragma once
#include <string>
#include <unordered_map>
#include <fstream>
#include "json.hpp"

// Forward declarations
class Player;
class Tamagotchi;

using json = nlohmann::json;

struct SaveData {
    // Player data
    int coins;
    int minigame_highscore;
    std::unordered_map<std::string, int> inventory;

    // Pet data
    std::string pet_type;
    float hunger;
    float happiness;
    float energy;
    float hygiene;
    int affection;
    int current_hat;

    json toJson() const;
    void fromJson(const json& j);
};

class SaveManager {
public:
    static bool saveGame(const std::string& filename, const Player& player, const Tamagotchi& pet);
    static bool loadGame(const std::string& filename, Player& player, Tamagotchi& pet);
};