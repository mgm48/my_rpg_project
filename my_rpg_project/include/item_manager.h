#pragma once
#include "types.h"
#include "item.h"

//item creation manager, only one allowed to make items
//remember : static functions are associated with the class, do not create an instance of it
class Potion;
class Armor;
class Weapon;
class PlayerCharacter;

class ItemManager {
public: 
	static bool IsItemEquippable(const Item* in);
	static bool IsItemUseable(const Item* in);

	static Item* CreateArmor(std::string name, CoreStats cstats, ARMORSLOT slot);
	static void CastItemToArmor(const Item* in, Armor*& out);
	static bool IsItemArmor(const Item* in);

	static Item* CreateWeapon(std::string name, CoreStats cstats, WEAPONSLOT slot, t_dmg min, t_dmg max, bool twohanded = false);
	static void CastItemToWeapon(const Item* in, Weapon*& out);
	static bool IsItemWeapon(const Item* in);

	static Item* CreatePotion(std::string name, t_pw Heal = 1u, item_count q = 1, Buff* effect = nullptr);
	static void CastItemToPotion(const Item* in, Potion*& out);
	static bool IsItemPotion(const Item* in);

	// Equips a weapon or armor and returns true, returns false if the action failed.
// if an item was previously equipped in that slot, it will move to the character's backpack
	static bool Equip(Item* item_to_equip, PlayerCharacter* p_char);

	static bool Use(Item* item_to_use, PlayerCharacter* p_char);

	static bool MoveToBackpack(Item* thing, PlayerCharacter* p_char);
	static bool DiscardFromBackpack(Item* thing, PlayerCharacter* p_char);

	static void DeleteItem(Item*& item_to_delete/*, std::vector<Item*>& pack_to_delete_from*/);
};
