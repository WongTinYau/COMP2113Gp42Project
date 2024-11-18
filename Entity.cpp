#include <string>
#include "Inventory.h"

using namespace std;

Entity::Entity(string displayName, int maxLives, int inventorySize) {
    m_displayName = displayName;
    m_maxLives = maxLives;
    m_currentLives = maxLives;
    m_inventory = Inventory(inventorySize);
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
    return m_inventory;
}