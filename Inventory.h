#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>
#include "Item.h"
#include <fstream>

class Item;

class Inventory {
public:
    /// @brief Constructs an Inventory.
    /// @param maxSlots (int) The maximum slots of the entity (Default is 4).
    Inventory(int maxSlots = 4);

    /// @brief Default constructor for Inventory.
    Inventory() : m_maxSlots(4), m_items() {}

    /// @brief Adds an item to the inventory.
    /// @param item (Item) The item to be added to the inventory.
    /// @return (bool) Whether the item has been successfully added.
    bool addItem(Item item);

    /// @brief Adds a random of items to the inventory.
    /// @param itemCount (int) The amount of random items to be added.
    void addRandomItems(int itemCount);

    /// @brief Returns the amount of items in the inventory.
    /// @return (int) The amount of items in the inventory.
    int getItemCount();

    /// @brief Resets a slot of an item in the inventory (Deleting an item).
    /// @param slot (int) The slot of the item to be reset / deleted.
    void resetSlot(int slot);

    /// @brief Returns whether the inventory is full.
    /// @return (bool) Whether the inventory is full.
    bool isFull();

    /// @brief Returns an item by slot number.
    /// @param slot (int) The slot number of the item.
    /// @return (Item) The item of the specified slot number.
    Item getSlotItem(int slot);

    /// @brief Returns a vector of items of the inventory.
    /// @return The vector of items of the inventory.
    std::vector<Item> getItems();

    /// @brief Returns the maximum items that the inventory can store.
    /// @return The maximum items that the inventory can store.
    int getMaxInventorySlots();

    void save(std::ofstream& fout) const;
    void load(std::ifstream& fin);

private:
    /// @brief The following variables should not be accessed from other .cpp files. Use the public functions instead.
    int m_maxSlots;
    std::vector<Item> m_items;
};

#endif //INVENTORY_H
