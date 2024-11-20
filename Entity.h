#ifndef ENTITY_H
#define ENTITY_H

#include <string>

class Inventory;

class Entity {
public:
    Entity(std::string displayName, int maxLives, int inventorySize);
    int damage(int amount);
    int getCurrentLives();
    int getMaxLives();
    int heal(int amount);
    void addPunishedRounds(int amount);
    int getPunishedRounds();
    void reducePunishedRounds(int amount);
    Inventory& getInventory();
    int getInventorySize();
    virtual ~Entity() = default;

private:
    std::string m_displayName;
    int m_maxLives;
    int m_currentLives;
    int m_punishRounds = 0;
    Inventory* m_inventory;
};

#endif //ENTITY_H
