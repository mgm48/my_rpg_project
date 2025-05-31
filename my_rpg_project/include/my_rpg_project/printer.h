#pragma once
#include "item.h"
#include "playableclasses.h"
#include <iostream>

static void print_weapon(const Weapon* weapon) {
	if (!weapon)
		return;

	switch (weapon->Slot) {
	case WEAPONSLOT::MELEE: { std::cout << "MELEE: "; break; }
	case WEAPONSLOT::RANGED: { std::cout << "RANGED: "; break; }
	default: break;
	}
	std::cout << weapon->Name << ":  " << "Damage(" << weapon->MinDamage << " - " << weapon->MaxDamage << "); ";
	if (weapon->Stats.any()) { std::cout << weapon->Stats; }
}

static void print_armor(const Armor* armor) {
	if (!armor)
		return;

	switch (armor->Slot) {
	case ARMORSLOT::HEAD: { std::cout << "HEAD: "; break; }
	case ARMORSLOT::CHEST: { std::cout << "CHEST: "; break; }
	case ARMORSLOT::LEGS: { std::cout << "LEGS: "; break; }
	case ARMORSLOT::FEET: { std::cout << "FEET: "; break; }
	case ARMORSLOT::HANDS: { std::cout << "HANDS: "; break; }
	case ARMORSLOT::RING1: { std::cout << "RING1: "; break; }
	case ARMORSLOT::RING2: { std::cout << "RING2: "; break; }
	case ARMORSLOT::NECK: { std::cout << "NECK: "; break; }
	default: break;
	}
	std::cout << armor->Name << ":  ";
	if (armor->Stats.any()) { std::cout << armor->Stats; }
}

static void print_item(Item* it) {
	if (ItemManager::IsItemArmor(it)) {
		const Armor* armor = dynamic_cast<const Armor*>(it->GetData());
		std::cout << armor->Name << ":  ";
		if (armor->Stats.any()) { std::cout << armor->Stats; }
	}
	else if (ItemManager::IsItemWeapon(it)) {
		const Weapon* weapon = dynamic_cast<const Weapon*>(it->GetData());
		std::cout << weapon->Name << ":  " << "Damage(" << weapon->MinDamage << " - " << weapon->MaxDamage << ") ";
		if (weapon->Stats.any()) { std::cout << weapon->Stats; }
	}
	else if (ItemManager::IsItemPotion(it)) {
		const Potion* pot = dynamic_cast<const Potion*>(it->GetData()); //expand to buff potions
		std::cout << pot->Name << ":  " << ((pot->HealAmount > 0) ? "Heal(+" : "Heal(") << pot->HealAmount << "), Quantity(" << pot->Quantity << ");";
	}
	else {
		std::cout << "Something weird happened, item error.";
	}
}

static void print_character_sheet(Player*& p) {
	std::cout
		<< "\nYour Character\n"
		<< "-----------------\n"
		<< "Lvl " << p->us.GetLevel() << " " << p->us.GetClass() << " xp: " << p->us.GetCurrentExp() << "/" << p->us.GetExpToNextLevel() << "\n"
		<< "Hit Points: " << p->us.GetCurrentHP() << "/" << p->us.GetMaxHP() << '\n';
	if (p->us.IsMagicUser()) { std::cout << "Mana: " << p->us.GetCurrentMP() << "/" << p->us.GetMaxMP() << '\n'; }
	std::cout
		<< "STR: " << p->us.GetTotalStrength() << "  INT: " << p->us.GetTotalIntellect() << "  AGI: " << p->us.GetTotalAgility() << '\n'
		<< "ARMOR: " << p->us.GetTotalArmor() << "  RES: " << p->us.GetTotalElementRes() << '\n'
		<< "\nEquipped Gear\n" << "-----------------\n";

	auto i = 0;
	for (i = 0; i < (unsigned long long)ARMORSLOT::NUM_SLOTS; i++) {
		if (p->us.GetEquippedArmorAt(i)) { print_armor(p->us.GetEquippedArmorAt(i)); std::cout << "\n"; }
	}
	for (i = 0; i < (unsigned long long)WEAPONSLOT::NUM_SLOTS; i++) {
		if (p->us.GetEquippedWeaponAt(i)) { print_weapon(p->us.GetEquippedWeaponAt(i)); std::cout << "\n"; }
	}
}