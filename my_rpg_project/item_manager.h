#pragma once
#include "types.h"
#include "items.h"

//item creation manager, only one allowed to make items

class ItemManager {
public: 
	static Item* createArmor(std::string name, CoreStats cstats, ARMORSLOT slot) { //pointer so that it doesnt copy data
		Item* tmpi = new Item(new Armor(name, cstats, slot));
		return tmpi; //returns copy of pointer to data
	}
	static Item* createWeapon(std::string name, CoreStats cstats, WEAPONSLOT slot, t_dmg min, t_dmg max, bool twohanded = false) {
		Item* temp_item = new Item(new Weapon(name, cstats, slot, min, max, twohanded));
		return temp_item;
	}

	static Item* createPotion(std::string name, t_pw heal = 1u, item_count q = 1, Buff* effect = nullptr) { //like a buff
		Item* temp_item = new Item(new Potion(name, heal, (q < 1 ? 1 : q), effect));
		return temp_item;
	}
};
