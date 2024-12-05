#include <string>
#include "Entity.h"
#include "Inventory.h"
#include <fstream>

using namespace std;

Entity::Entity(string displayName, int maxLives, int inventorySize) {
    m_displayName = displayName;
    m_maxLives = maxLives;
    m_currentLives = maxLives;
    m_inventory = new Inventory(inventorySize);
}

int Entity::damage(int amount) {
    m_currentLives -= amount;
    if (m_currentLives < 0) {
        m_currentLives = 0;
    }
    return m_currentLives;
}

int Entity::getCurrentLives() {
    return m_currentLives;
}

int Entity::getMaxLives() {
    return m_maxLives;
}

int Entity::heal(int amount) {
    m_currentLives += amount;
    if (m_currentLives > m_maxLives) {
        m_currentLives = m_maxLives;
    }
    return m_currentLives;
}

void Entity::addPunishedRounds(int amount) {
    m_punishRounds += amount;
}

int Entity::getPunishedRounds() {
    return m_punishRounds;
}

void Entity::reducePunishedRounds(int amount) {
    m_punishRounds -= amount;
    if (m_punishRounds < 0) {
        m_punishRounds = 0;
    }
}

Inventory& Entity::getInventory() {
    return *m_inventory;
}

void Entity::save(std::ofstream& fout) const {
    size_t nameLength = m_displayName.size();
    fout.write(reinterpret_cast<const char*>(&nameLength), sizeof(size_t));
    fout.write(m_displayName.c_str(), nameLength);
    fout.write(reinterpret_cast<const char*>(&m_maxLives), sizeof(int));
    fout.write(reinterpret_cast<const char*>(&m_currentLives), sizeof(int));
    m_inventory->save(fout); 
}

void Entity::load(std::ifstream& fin) {
    size_t nameLength;
    fin.read(reinterpret_cast<char*>(&nameLength), sizeof(size_t));
    m_displayName.resize(nameLength);
    fin.read(&m_displayName[0], nameLength);
    fin.read(reinterpret_cast<char*>(&m_maxLives), sizeof(int));
    fin.read(reinterpret_cast<char*>(&m_currentLives), sizeof(int));
    m_inventory->load(fin);
}
