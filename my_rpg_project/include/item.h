#pragma once
#include "corestats.h"
#include "buff.h"
#include <string>
//#include <iostream>
#include <typeinfo>

class ItemDelegate {
public:
	std::string Name;
protected:
	virtual ~ItemDelegate() = 0 {}
	ItemDelegate(std::string name) : Name(name) {}
	friend class Item;
};


class EquipmentDelegate : public ItemDelegate {
public:
	const std::uint32_t UniqueId; //for non stackable items
	CoreStats Stats;
protected:
	virtual ~EquipmentDelegate() = 0 {}
	EquipmentDelegate(std::string name, CoreStats cstats);
private:
};

class Potion : public ItemDelegate {
public:
	t_pw HealAmount;
	item_count Quantity;
	const Buff* GetBuff() const;
	void SetBuff(Buff* new_buff);
	
private: 
	Buff* _buff;
	Potion(std::string name, t_pw hp_heal = 1u, item_count q = 1, Buff* b = nullptr);
	~Potion();
	friend class ItemManager;
};

enum class ARMORSLOT { HEAD, CHEST, LEGS, FEET, HANDS, RING1, RING2, NECK, NUM_SLOTS };  // NUM SLOTS FOR MAKING ARRAYS OF ARMOR SLOTS
class Armor final : public EquipmentDelegate {
public:
	ARMORSLOT Slot;
private:
	Armor(std::string name, CoreStats cstats, ARMORSLOT slot);
	Armor() = delete; //so no one can use a default empty constructor
	Armor(const Armor&) = delete;
	Armor(const Armor&&) = delete;	
	~Armor(); // only ItemManger can clean this up
	friend class ItemManager;
};

enum class WEAPONSLOT { MELEE, RANGED, NUM_SLOTS };
class Weapon final : public EquipmentDelegate {
public:
	WEAPONSLOT Slot;
	t_dmg MinDamage;
	t_dmg MaxDamage;
	bool is2H; //twohander vs onehander
private:
	Weapon(std::string name, CoreStats stats, WEAPONSLOT slot, t_dmg mind, t_dmg maxd, bool hands = false);
	Weapon() = delete; //so no one can use a default empty constructor
	Weapon(const Weapon&) = delete;  //no copying
	Weapon(const Weapon&&) = delete; //no moving an object into this one
	~Weapon();  // only ItemManger can clean this up
	friend class ItemManager;
};

// use this one in your runtime code
class Item {
public:
	const ItemDelegate* GetData() { return _data; } //const pointer, cant be modified except const cast but thats too much
	bool isMarkedForDeletion() const { return _marked_for_deletion; }
	bool isMarkedAsBackpackRefGone() const { return _marked_as_backpack_ref_gone; }
private:
	~Item() { //to prevent memory leaks 
		if (_data) {
			delete _data;
			_data = nullptr;
		}
	}
	ItemDelegate* _data; //we need to instatiate this at runtime, also private so it cant getchanged
	bool _marked_for_deletion = false;
	bool _marked_as_backpack_ref_gone = false; //has been equipped or moved somewhere else
	Item(ItemDelegate* item) : _data(item) {}
	friend class ItemManager; //friend clases can instantiate this class
	friend class PlayerCharacter;
};
