#include "item_manager.h"
#include "playercharacter.h"


bool ItemManager::IsItemEquippable(const Item* in) {
	if (dynamic_cast<Armor*>(in->_data) || dynamic_cast<Weapon*>(in->_data)) return true;
	else return false;
}
bool ItemManager::IsItemUseable(const Item* in) {
	if (dynamic_cast<Potion*>(in->_data)) return true;
	else return false;
}

[[nodiscard]] Item* ItemManager::CreateArmor(std::string name, CoreStats cstats, ARMORSLOT slot) { //pointer so that it doesnt copy data
	Item* tmpi = new Item(new Armor(name, cstats, slot));
	return tmpi; //returns copy of pointer to data
}
void ItemManager::CastItemToArmor(const Item* in, Armor*& out) {
	if (!in) return;
	out = dynamic_cast<Armor*>(in->_data);
}

bool ItemManager::IsItemArmor(const Item* in) {
	if (dynamic_cast<Armor*>(in->_data)) return true;
	else return false;
}

[[nodiscard]] Item* ItemManager::CreateWeapon(std::string name, CoreStats cstats, WEAPONSLOT slot, t_dmg min, t_dmg max, bool twohanded) {
	Item* temp_item = new Item(new Weapon(name, cstats, slot, min, max, twohanded));
	return temp_item;
}

void ItemManager::CastItemToWeapon(const Item* in, Weapon*& out) { //we need the reference bc if not it passes a copy of the pointer
	if (!in) return;
	out = dynamic_cast<Weapon*>(in->_data);
}

bool ItemManager::IsItemWeapon(const Item* in) {
	if (dynamic_cast<Weapon*>(in->_data)) return true;
	return false;
}

[[nodiscard]] Item* ItemManager::CreatePotion(std::string name, t_pw Heal, item_count q, Buff* effect) { //like a buff
	Item* temp_item = new Item(new Potion(name, Heal, (q < 1 ? 1 : q), effect));
	return temp_item;
}

void ItemManager::CastItemToPotion(const Item* in, Potion*& out) {
	if (!in) return;
	out = dynamic_cast<Potion*>(in->_data);
}
bool ItemManager::IsItemPotion(const Item* in) {
	if (dynamic_cast<Potion*>(in->_data)) return true;
	return false;
}


bool ItemManager::Equip(Item* thing, PlayerCharacter* p_char) {
	if (!p_char || !thing || !thing->GetData()) //most likely to fail to be on the left, as it will be checked first
		return false;

	Armor* armor = dynamic_cast<Armor*>(thing->_data);
	if (armor) {
		//check what slot it is
		unsigned long long slot_num = (unsigned long long)armor->Slot;

		if (p_char->_equipped_armor[slot_num]) { //delete old armor
			Armor* armor_quit = dynamic_cast<Armor*>(p_char->_equipped_armor[slot_num]->_data);

			p_char->_equipped_armor[slot_num]->_marked_as_backpack_ref_gone = false;
			MoveToBackpack(p_char->_equipped_armor[slot_num], p_char);
			p_char->_equip_modifier -= armor_quit->Stats; //remove modifiers
			p_char->_equipped_armor[slot_num] = thing;
		}
		else { p_char->_equipped_armor[slot_num] = thing; } //Equip
		thing->_marked_as_backpack_ref_gone = true;

		p_char->_equip_modifier += armor->Stats;
		p_char->cleanup_backpack();

		return true;
	}

	Weapon* weapon = dynamic_cast<Weapon*>(thing->_data);
	if (weapon) {
		unsigned long long slot_num = (unsigned long long)weapon->Slot;

		if (p_char->_equipped_weapons[slot_num]) { //delete old armor
			Weapon* weapon_quit = dynamic_cast<Weapon*>(p_char->_equipped_armor[slot_num]->_data);

			p_char->_equipped_weapons[slot_num]->_marked_as_backpack_ref_gone = false;
			MoveToBackpack(p_char->_equipped_weapons[slot_num], p_char);
			p_char->_equip_modifier -= weapon_quit->Stats; //remove modifiers
			p_char->_equipped_weapons[slot_num] = thing;
		}
		else { p_char->_equipped_weapons[slot_num] = thing; }
		thing->_marked_as_backpack_ref_gone = true;

		p_char->_equip_modifier += weapon->Stats;
		p_char->cleanup_backpack();

		return true;
	}

	// if item fails to equip, move it to the characters backpack
	//thing->_marked_as_backpack_ref_gone = false;
	//MoveToBackpack(thing, p_char);

	return false;
}

bool ItemManager::Use(Item* thing, PlayerCharacter* p_char) {
	if (!p_char || !thing || !thing->GetData())
		return false;

	Potion* potion = dynamic_cast<Potion*>(thing->_data);
	if (potion && potion->Quantity > 0) {

		if (potion->_buff) {
			p_char->ApplyBuff(*potion->_buff);
		}

		// if max health and trying to use a heal potion, don't use itS
		if (p_char->IsMaxHP() && !potion->_buff)
			return false; // don't use the potion

		//if its negative and on 1 it'll just stay there
		p_char->HealthModify(potion->HealAmount);

		potion->Quantity--;

		if (potion->Quantity == 0) {
			thing->_marked_for_deletion = true;
			p_char->cleanup_backpack();
		}
		return true;

	}
	return false;
}


bool ItemManager::MoveToBackpack(Item* thing, PlayerCharacter* p_char) {
	if (!p_char || !thing || !thing->GetData()) //most likely to fail to be on the left, as it will be checked first ( also makes sure we dont access nullpointers)
		return false;

	p_char->_backpack.push_back(thing);
	return true;
}
bool ItemManager::DiscardFromBackpack(Item* thing, PlayerCharacter* p_char) {
	if (!p_char || !thing || !thing->GetData())
		return false;

	thing->_marked_for_deletion = true;
	p_char->cleanup_backpack();
	return true;
}

void ItemManager::DeleteItem(Item*& item_to_delete/*, std::vector<Item*>& pack_to_delete_from*/) {
	delete item_to_delete;
	item_to_delete = nullptr;
}
