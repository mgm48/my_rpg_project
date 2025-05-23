#pragma once
#include "corestats.h"
#include <string>
#include <typeinfo>

class ItemDelegate {
public:
	std::string Name;
	virtual const char* GetType() = 0;
protected:
	ItemDelegate(std::string name) : Name(name) {}
};

// use this one in your runtime code
class Item {
public:
	const ItemDelegate* GetData() { return _data; } //const pointer, cant be modified except const cast but thats too much
	~Item() { //to prevent memory leaks 
		delete _data;
		_data = nullptr;
	}
private: 
	ItemDelegate* _data; //we need to instatiate this at runtime, also private so it cant getchanged
	Item(ItemDelegate* item) : _data(item) {}
	friend class ItemManager; //friend clases can instantiate this class
	friend class PlayerCharacter;
};

class EquipmentDelegate : public ItemDelegate {
public:
	const std::uint32_t UniqueId; //for non stackable items
	CoreStats Stats;
protected:
	EquipmentDelegate(std::string name, CoreStats cstats);
};


enum class ARMORSLOT { HELMET, CHEST, LEGS, BOOTS, GLOVES, RING1, RING2, NECK, NUM_SLOTS };  // NUM SLOTS FOR MAKING ARRAYS OF ARMOR SLOTS
class Armor final : public EquipmentDelegate {
public:
	ARMORSLOT Slot;

	const char* GetType() override { return typeid(*this).name(); }; //will return class armor

private:
	Armor(std::string name, CoreStats cstats, ARMORSLOT slot) : EquipmentDelegate(name, cstats), Slot(slot) {}

	Armor() = delete; //so no one can use a default empty constructor
	Armor(const Armor&) = delete;
	Armor(const Armor&&) = delete;	

	friend class ItemManager;
};

enum class WEAPONSLOT { MELEE, RANGED, NUM_SLOTS };
class Weapon final : public EquipmentDelegate {
public:
	WEAPONSLOT Slot;
	t_dmg minDmg;
	t_dmg maxDmg;
	bool is2H; //twohander vs onehander
	const char* GetType() override { return typeid(*this).name(); };

private:
	Weapon(std::string name, CoreStats stats, WEAPONSLOT slot, t_dmg mind, t_dmg maxd, bool hands = false) : 
		EquipmentDelegate(name, stats), Slot(slot), minDmg(mind), maxDmg(maxd), is2H(hands) {
	}

	Weapon() = delete; //so no one can use a default empty constructor
	Weapon(const Weapon&) = delete;  //no copying
	Weapon(const Weapon&&) = delete; //no moving an object into this one

	friend class ItemManager;
};