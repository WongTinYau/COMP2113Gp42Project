#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>
#include "Item.h"

class Item;

class Inventory {
public:
    Inventory(int maxSlots = 4);
    void addItem(Item item);
    void addRandomItems(int itemCount);
    int getItemCount();
    void resetSlot(int slot);
    bool isFull();
    Item getSlotItem(int slot);
    std::vector<Item> getItems();
private:
    int m_maxSlots;
    std::vector<Item> m_items;
};

#endif //INVENTORY_H