#include "Inventory.h"
#include "Item.h"
#include <vector>
#include <random>

using namespace std;

Inventory::Inventory(int maxSlots)
{
    m_maxSlots = maxSlots;
}

void Inventory::addItem(Item item) {
    m_items.push_back(item);
}

void Inventory::addRandomItems(int itemCount) {
    int remainingSlots = m_maxSlots - m_items.size();
    if (itemCount > remainingSlots) {
        itemCount = remainingSlots;
    }

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(0, static_cast<int>(ItemType::MAGNET));

    for (int i = 0; i < itemCount; ++i) {
        Item randomItem = Item(static_cast<ItemType>(distrib(gen)));
        m_items.push_back(randomItem);
    }
}

int Inventory::getItemCount() {
    return m_items.size();
}

bool Inventory::isFull() {
    return m_items.size() >= m_maxSlots;
}

void Inventory::resetSlot(int slot) {
    if (slot >= 0 && slot < m_items.size()) {
        m_items.erase(m_items.begin() + slot);
    }
}

vector<Item> Inventory::getItems() {
    return m_items;
}

Item Inventory::getSlotItem(int slot) {
    return m_items[slot];
}