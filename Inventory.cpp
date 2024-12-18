#include "Inventory.h"
#include "Item.h"
#include <vector>
#include <random>
#include <fstream>

using namespace std;

Inventory::Inventory(int maxSlots)
{
    m_maxSlots = maxSlots;
}

bool Inventory::addItem(Item item) {
    if(isFull()) return false;
    else {
      m_items.push_back(item);
      return true;
    }
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

int Inventory::getMaxInventorySlots() {
    return m_maxSlots;
}

void Inventory::save(std::ofstream& fout) const {
    fout.write(reinterpret_cast<const char*>(&m_maxSlots), sizeof(int));

    size_t itemCount = m_items.size();
    fout.write(reinterpret_cast<const char*>(&itemCount), sizeof(size_t));

    for (const auto& item : m_items) {
        item.save(fout);
    }
}

void Inventory::load(std::ifstream& fin) {
    fin.read(reinterpret_cast<char*>(&m_maxSlots), sizeof(int));

    size_t itemCount;
    fin.read(reinterpret_cast<char*>(&itemCount), sizeof(size_t));

    m_items.clear();
    for (size_t i = 0; i < itemCount; ++i) {
        Item item(ItemType::SAW); // Default item type, will be overwritten
        item.load(fin);
        m_items.push_back(item);
    }
}
