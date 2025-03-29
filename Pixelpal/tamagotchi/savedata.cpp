#include "savedata.h"
#include "player.h"
#include "Tamagotchi.hpp"

json SaveData::toJson() const {
    return {
        {"player", {
            {"coins", coins},
            {"minigame_highscore", minigame_highscore},
            {"inventory", inventory}
        }},
        {"pet", {
            {"type", pet_type},
            {"hunger", hunger},
            {"happiness", happiness},
            {"energy", energy},
            {"hygiene", hygiene},
            {"affection", affection},
            {"current_hat", current_hat}
        }}
    };
}

void SaveData::fromJson(const json& j) {
    coins = j["player"]["coins"];
    minigame_highscore = j["player"]["minigame_highscore"];

    for (auto& item : j["player"]["inventory"].items()) {
        inventory[item.key()] = item.value();
    }

    pet_type = j["pet"]["type"];
    hunger = j["pet"]["hunger"];
    happiness = j["pet"]["happiness"];
    energy = j["pet"]["energy"];
    hygiene = j["pet"]["hygiene"];
    affection = j["pet"]["affection"];
    current_hat = j["pet"]["current_hat"];
}

bool SaveManager::saveGame(const std::string& filename, const Player& player, const Tamagotchi& pet) {
    SaveData data;
    player.toSaveData(data);
    pet.toSaveData(data);

    json j = data.toJson();

    std::ofstream file(filename);
    if (!file.is_open()) return false;

    file << j.dump(4);
    file.close();
    return true;
}

bool SaveManager::loadGame(const std::string& filename, Player& player, Tamagotchi& pet) {
    std::ifstream file(filename);
    if (!file.is_open()) return false;

    try {
        json j;
        file >> j;
        file.close();

        SaveData data;
        data.fromJson(j);

        player.fromSaveData(data);
        pet.fromSaveData(data);
        return true;
    }
    catch (const std::exception& e) {
        std::cerr << "Error loading save: " << e.what() << std::endl;
        return false;
    }
}