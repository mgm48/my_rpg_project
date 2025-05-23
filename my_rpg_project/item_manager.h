#pragma once
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
};
