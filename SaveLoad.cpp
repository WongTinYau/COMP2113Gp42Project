#include "SaveLoad.h"
#include "GameState.h"
#include <fstream>
#include <iostream>

void SaveGame(const GameState& state) {
    std::ofstream fout("savegame.dat", std::ios::binary);
    if (!fout) {
        std::cout << "Error: Could not open save file!" << std::endl;
        return;
    }
  
    size_t levelLength = state.currentLevel.size();
    fout.write(reinterpret_cast<const char*>(&levelLength), sizeof(size_t));
    fout.write(state.currentLevel.c_str(), levelLength);

    // Save entities
    state.player.save(fout);
    state.dealer.save(fout);

    // Save shotgun
    fout.write(reinterpret_cast<const char*>(&state.shotgun), sizeof(Shotgun));

    // Save turn order
    fout.write(reinterpret_cast<const char*>(&state.isPlayerTurn), sizeof(bool));

    // Save dealer item queue
    size_t queueSize = state.dealerItemQueue.size();
    fout.write(reinterpret_cast<const char*>(&queueSize), sizeof(size_t));
    for (const auto& item : state.dealerItemQueue) {
        item.save(fout);
    }

    // Save dealer next choice
    fout.write(reinterpret_cast<const char*>(&state.dealerNextChoice), sizeof(int));

    // Save total playtime
    fout.write(reinterpret_cast<const char*>(&state.totalPlayTime), sizeof(long));

    fout.close();
    std::cout << "Game saved successfully." << std::endl;
}

bool LoadGame(GameState& state) {
    std::ifstream fin("savegame.dat", std::ios::binary);
    if (!fin) {
        std::cout << "Error: No save file found!" << std::endl;
        return false;
    }

    // Load current level
    size_t levelLength;
    fin.read(reinterpret_cast<char*>(&levelLength), sizeof(size_t));
    state.currentLevel.resize(levelLength);
    fin.read(&state.currentLevel[0], levelLength);

    // Load entities
    state.player.load(fin);
    state.dealer.load(fin);

    // Load shotgun
    state.shotgun.load(fin);
    
    // Load turn order
    fin.read(reinterpret_cast<char*>(&state.isPlayerTurn), sizeof(bool));

    // Load dealer item queue
    size_t queueSize;
    fin.read(reinterpret_cast<char*>(&queueSize), sizeof(size_t));
    state.dealerItemQueue.clear();
    for (size_t i = 0; i < queueSize; ++i) {
        Item item(ItemType::SAW); // Default initialization; overwritten when loaded
        item.load(fin);
        state.dealerItemQueue.push_back(item);
    }

    // Load dealer next choice
    fin.read(reinterpret_cast<char*>(&state.dealerNextChoice), sizeof(int));

    // Load total playtime
    fin.read(reinterpret_cast<char*>(&state.totalPlayTime), sizeof(long));

    fin.close();
    std::cout << "Game loaded successfully." << std::endl;
    return true;
}
