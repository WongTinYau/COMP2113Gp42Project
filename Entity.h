#ifndef ENTITY_H
#define ENTITY_H

#include <string>

class Inventory;

class Entity {
public:
    /// @brief Constructs an entity.
    /// @param displayName (string) The display name for the Entity (for future use).
    /// @param maxLives (int) The maximum lives that the entity has.
    /// @param inventorySize (int) The maximum inventory slots that the entity has.
    Entity(std::string displayName, int maxLives, int inventorySize);

    /// @brief Reduces the number of lives of the entity.
    /// @param amount (int) The amount of lives to be deducted
    /// @return (int) The number of lives of the entity after damaging the entity.
    int damage(int amount);

    /// @brief Returns the current number of lives of the entity.
    /// @return (int) The current number of lives of the entity.
    int getCurrentLives();

    /// @brief Returns the maximum number of lives that entity could have.
    /// @return (int) The maximum number of lives that entity could have.
    int getMaxLives();

    /// @brief Increases the number of lives of the entity.
    /// @param amount (int) The amount of lives to be increased
    /// @return (int) The number of lives of the entity after healing the entity.
    int heal(int amount);

    /// @brief Increases the number of rounds to be skipped for the entity.
    /// @param amount (int) The number of rounds to be skipped for the entity.
    void addPunishedRounds(int amount);

    /// @brief Returns the number of rounds to be skipped for the entity.
    /// @return (int) The number of rounds to be skipped for the entity.
    int getPunishedRounds();

    /// @brief Reduces the number of rounds to be skipped for the entity. This should be called after the entity has been punished (The round has been skipped).
    /// @param amount (int) The number of rounds to be skipped for the entity.
    void reducePunishedRounds(int amount);

    /// @brief Returns the inventory of the entity.
    /// @return (Inventory) The inventory of the entity.
    Inventory& getInventory();

    /// @brief Default destructor.
    virtual ~Entity() = default;

    // Save and Load the Entity state
    void save(std::ofstream& fout) const;
    void load(std::ifstream& fin);

private:
    /// @brief The following variables should not be accessed from other .cpp files. Use the public functions instead.
    std::string m_displayName;
    int m_maxLives;
    int m_currentLives;
    int m_punishRounds = 0;
    Inventory* m_inventory;
};

#endif //ENTITY_H
