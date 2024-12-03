#include <string>
#include <utility>
#include <random>
#include "Item.h"
#include "ItemType.h"
#include "Entity.h"
#include "Shotgun.h"
#include "Inventory.h"
#include <fstream>

using namespace std;

Item::Item(ItemType type) {
    m_Type = type;
}

ItemType Item::getType() {
    return m_Type;
}

void Item::save(std::ofstream& fout) const {
    int type = static_cast<int>(m_Type);
    fout.write(reinterpret_cast<const char*>(&type), sizeof(int));
}

void Item::load(std::ifstream& fin) {
    int type;
    fin.read(reinterpret_cast<char*>(&type), sizeof(int)); // Read the integer from the file
    m_Type = static_cast<ItemType>(type); // Convert the integer back to ItemType
}

//Returns 1. Whether the item has been used successfully, and 2. The message to be sent.
pair<bool, string> Item::use(Entity &user, Entity &target, Shotgun &gun) {
    switch(m_Type) {
        case ItemType::SAW: {
            gun.increaseTempDamage(gun.getUpcomingDamage());
            return make_pair(true, string("Saw Used! The upcomming shot now deals double damage!"));
        }
        case ItemType::MAGNIFYING_GLASS: {
            if(gun.getUpcomingShell() == Shell::BLANK) return make_pair(true, "Magnifying Glass Used! The shell is Blank!");
            else if(gun.getUpcomingShell() == Shell::LIVE) return make_pair(true, "Magnifying Glass Used! The shell is Live!");
            else return make_pair(false, "Error Occured! Unknown Shell Type!");
        }
        case ItemType::INVERTER: {
            gun.invertUpcomingShell();
            return make_pair(true, "Inverter Used! The shell is now inverted!");
        }
        case ItemType::HEART: {
            if(user.getCurrentLives() == user.getMaxLives()) {
                return make_pair(false, "Unable to use item: Max Health Already!");
            }
            else {
                user.heal(1);
                return make_pair(true, "Heart Used!");
            }
        }
        case ItemType::HANDCUFF: {
            target.addPunishedRounds(1);
            return make_pair(true, "Handcuff Used! The opponent will skip " + to_string(target.getPunishedRounds()) + " round(s)!");
        }
        case ItemType::MAGNET: {
            if(user.getInventory().isFull()) {
                return make_pair(false, "Inventory full!");
            }
            int itemCount = target.getInventory().getItemCount();
            if (itemCount <= 0) {
                return make_pair(false, "The dealer does not have any items!" + itemCount);
            }
            random_device dev;
            mt19937 rng(dev()); 
            uniform_int_distribution<mt19937::result_type> dist(0, itemCount - 1);

            int random_slot = dist(rng);
            Item item = target.getInventory().getSlotItem(random_slot);
            ItemType itemType = item.getType();
            target.getInventory().resetSlot(random_slot);
            user.getInventory().addItem(itemType);
            return make_pair(true, "Magnet Used! Stole 1 item from the opponent!");
        }
        default: {
            return make_pair(false, "Unknown Item Type!");
        }
    }
}
