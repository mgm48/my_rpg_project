#pragma once
#include "types.h"
#include "items.h"

//item creation manager, only one allowed to make items
//remember : static functions are associated with the class, do not create an instance of it

class ItemManager {
public: 
	static Item* CreateArmor(std::string name, CoreStats cstats, ARMORSLOT slot) { //pointer so that it doesnt copy data
		Item* tmpi = new Item(new Armor(name, cstats, slot));
		return tmpi; //returns copy of pointer to data
	}
	static Item* CreateWeapon(std::string name, CoreStats cstats, WEAPONSLOT slot, t_dmg min, t_dmg max, bool twohanded = false) {
		Item* temp_item = new Item(new Weapon(name, cstats, slot, min, max, twohanded));
		return temp_item;
	}

	static Item* CreatePotion(std::string name, t_pw heal = 1u, item_count q = 1, Buff* effect = nullptr) { //like a buff
		Item* temp_item = new Item(new Potion(name, heal, (q < 1 ? 1 : q), effect));
		return temp_item;
	}


	// Equips a weapon or armor and returns true, returns false if the action failed.
	// if an item was previously equipped in that slot, it will move to the character's backpack
	static bool Equip(Item* thing, PlayerCharacter* p_char) {
		if (!thing->GetData() || !thing || !p_char) //most likely to fail to be on the right, as it will be checked first
			return false;

		Armor* armor = dynamic_cast<Armor*>(thing->_data);
		if (armor) {
			//check what slot it is
			unsigned long long slot_num = (unsigned long long)armor->Slot;

			if (p_char->EquippedArmor[slot_num]) { //delete old armor
				Armor* armor_quit = dynamic_cast<Armor*>(p_char->EquippedArmor[slot_num]->_data);

				MoveToBackpack(p_char->EquippedArmor[slot_num], p_char);
				p_char->EquipmentModifier -= armor_quit->Stats; //remove modifiers
				p_char->EquippedArmor[slot_num] = thing;
			} else {
				p_char->EquippedArmor[slot_num] = thing; //Equip
			}
			p_char->EquipmentModifier += armor->Stats;

			return true;
		}

		Weapon* weapon = dynamic_cast<Weapon*>(thing->_data);
		if (weapon) {
			unsigned long long slot_num = (unsigned long long)weapon->Slot;

			if (p_char->EquippedWeapons[slot_num]) { //delete old armor
				Weapon* weapon_quit = dynamic_cast<Weapon*>(p_char->EquippedArmor[slot_num]->_data);

				MoveToBackpack(p_char->EquippedWeapons[slot_num], p_char);
				p_char->EquipmentModifier -= weapon_quit->Stats; //remove modifiers
				p_char->EquippedWeapons[slot_num] = thing;
			}
			else {
				p_char->EquippedWeapons[slot_num] = thing; //Equip
			}

			p_char->EquipmentModifier += weapon->Stats;

			return true;
		}

		return false;
	}

	static bool Use(Item* thing, PlayerCharacter* p_char) {
		if (!thing->GetData() || !thing || !p_char) //most likely to fail to be on the right, as it will be checked first
			return false;

		Potion* potion = dynamic_cast<Potion*>(thing->_data);
		if (potion) {

			if (potion->Effect) {
				p_char->applyBuff(*potion->Effect);
			}

			// if max health and trying to use a heal potion, don't use itS
			if (p_char->pcclass->HP->isFull() && !potion->Effect)
				return false; // don't use the potion

			//if (potion->HealAmount > 0)
			p_char->pcclass->HP->addCur(potion->HealAmount);

			potion->Quantity--;

			if (potion->Quantity == 0) {
				thing->marked_for_deletion = true;
				p_char->cleanup_backpack();
			}
			return true;

		}
		return false;
	}
	static bool MoveToBackpack(Item* thing, PlayerCharacter* p_char) {
		if (!thing->GetData() || !thing || !p_char) //most likely to fail to be on the right, as it will be checked first
			return false;


		p_char->Backpack.push_back(thing);
		return true;
	}
};
