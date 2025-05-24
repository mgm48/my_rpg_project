#pragma once
#include "corestats.h"
#include "buffs.h"
#include <string>
#include <typeinfo>

class ItemDelegate {
public:
	std::string Name;
	virtual const char* GetType() = 0; //just to make this pure virtual
protected:
	ItemDelegate(std::string name) : Name(name) {}
};

#define GETTYPE const char* GetType() override { return typeid(*this).name(); };

class EquipmentDelegate : public ItemDelegate {
public:
	const std::uint32_t UniqueId; //for non stackable items
	CoreStats Stats;
protected:
	EquipmentDelegate(std::string name, CoreStats cstats);
};

class Potion : public ItemDelegate {
public:
	Buff* Effect;
	t_pw HealAmount;
	item_count Quantity;

	~Potion() {
		if (Effect) {
			delete Effect;
			Effect = nullptr;
		}
	}

	GETTYPE
private: 
	Potion(std::string name, t_pw heal = 1u, item_count q = 1, Buff* b = nullptr) : ItemDelegate(name), HealAmount(heal), Quantity(q), Effect(b) {}

	friend class ItemManager;
};




enum class ARMORSLOT { HELMET, CHEST, LEGS, BOOTS, GLOVES, RING1, RING2, NECK, NUM_SLOTS };  // NUM SLOTS FOR MAKING ARRAYS OF ARMOR SLOTS
class Armor final : public EquipmentDelegate {
public:
	ARMORSLOT Slot;

	GETTYPE//will return class armor

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
	t_dmg MinDamage;
	t_dmg MaxDamage;
	bool is2H; //twohander vs onehander

	GETTYPE
private:
	Weapon(std::string name, CoreStats stats, WEAPONSLOT slot, t_dmg mind, t_dmg maxd, bool hands = false) : 
		EquipmentDelegate(name, stats), Slot(slot), MinDamage(mind), MaxDamage(maxd), is2H(hands) {
	}

	Weapon() = delete; //so no one can use a default empty constructor
	Weapon(const Weapon&) = delete;  //no copying
	Weapon(const Weapon&&) = delete; //no moving an object into this one

	friend class ItemManager;
};

#include <iostream>  // for testing
// use this one in your runtime code
class Item {
public:
	const ItemDelegate* GetData() { return _data; } //const pointer, cant be modified except const cast but thats too much
	~Item() { //to prevent memory leaks 
		if (_data) {
			delete _data;
			_data = nullptr;
		}
	}
	bool isMarkedForDeletion() const { return marked_for_deletion; }

private:
	ItemDelegate* _data; //we need to instatiate this at runtime, also private so it cant getchanged
	bool marked_for_deletion = false;
	Item(ItemDelegate* item) : _data(item) {}

	friend class ItemManager; //friend clases can instantiate this class
	friend class PlayerCharacter;

	friend std::ostream& operator<<(std::ostream& os, const Item& t) {
		Armor* tmp_cast = dynamic_cast<Armor*>(t._data);
		if (tmp_cast) {
			return os << tmp_cast->Name << "(Armor: " << tmp_cast->Stats.Armor << ", Resist: " << tmp_cast->Stats.ElementRes << ')';
		}
		Weapon* tmp_cast2 = dynamic_cast<Weapon*>(t._data);
		if (tmp_cast2) {
			return  os << tmp_cast2->Name << "(Damage: " << tmp_cast2->MinDamage << '-' << tmp_cast2->MaxDamage << ')';
		}
		Potion* tmp_cast3 = dynamic_cast<Potion*>(t._data);
		if (tmp_cast3) {
			return os << tmp_cast3->Name << '(' << tmp_cast3->Quantity << ')';
		}
		return os;
	}

};
