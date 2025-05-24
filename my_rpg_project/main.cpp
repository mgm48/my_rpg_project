#include <iostream>
#include "playercharacter.h"
#include "item_manager.h"
int main() {
	const int n = 1;
	PlayerCharacter p1(new Warrior());
	PlayerCharacter p2(new Warrior());
	PlayerCharacter p3(new Wizard());
	PlayerCharacter p4(new Rogue());
	PlayerCharacter p5(new Cleric());
	PlayerCharacter* ps[n] = { &p1 };//, &p2 &p3, &p4, &p5 };


	//armor stuff
	CoreStats plate_armor_stats(0, 0, 0, 5, 3);
	Item* FullPlateMail = ItemManager::CreateArmor("Shiny Plate Armor", CoreStats(0, 0, 0, 5, 3), ARMORSLOT::CHEST);
	Item* LeatherArmor = ItemManager::CreateArmor("Leather Armor", CoreStats(0, 0, 0, 2, 1), ARMORSLOT::CHEST);

	Item* LongSword = ItemManager::CreateWeapon("Long Sword", CoreStats(), WEAPONSLOT::MELEE, 3, 9);



	ItemManager::Equip(FullPlateMail, &p1);
	ItemManager::Equip(LongSword, &p1);

	for (int j = 0; j < n; j++) {
		for (int i = 0; i < 2; i++) {
			std::cout
				<< ps[j]->getClassName() << " " << (j + 1)
				<< " Level " << ps[j]->getLevel() << '\n'
				<< "-EXP: " << ps[j]->getCurrentExp() << '/' << ps[j]->getExpToNextLevel() << '\n'
				<< "-HP: " << ps[j]->getCurrentHP() << '/' << ps[j]->getMaxHP() << '\n'
				<< "-MP: " << ps[j]->getCurrentMP() << '/' << ps[j]->getMaxMP() << '\n'
				<< "-Stength: " << ps[j]->getTotalStrength() << '\n'
				<< "-Intellect: " << ps[j]->getTotalIntellect() << '\n'
				<< "-Agility: " << ps[j]->getTotalAgility() << '\n'
				<< "-Armor: " << ps[j]->getTotalArmor() << '\n'
				<< "-ElementRes: " << ps[j]->getTotalElementRes() << '\n'
				<< '\n';

			auto AllAbilities = ps[j]->getAbilityList();
			auto AllBuffs = ps[j]->getBuffList();

			if (!AllAbilities.empty()) {
				std::cout << "-Abilities:\n";
				for (auto& abil : AllAbilities) {
					std::cout << "  -" << abil.Name << '\n';
				}
			}

			if (!AllBuffs.empty()) {
				std::cout << "-Buffs:\n";
				for (auto& b : AllBuffs) {
					std::cout << "  -" << b.Name << '\n';
				}
			}

			std::cout << "-Armor:\n";
			for (int i = 0; i < (int)ARMORSLOT::NUM_SLOTS; i++) {
				const Armor* tmp = dynamic_cast<Armor*>(ps[j]->getEquippedArmorAt(i));

				if (tmp) {
					std::cout << " " << tmp->Name << ", A:(" << tmp->Stats.Armor << ") R:(" << tmp->Stats.ElementRes << ")\n";
				}
			}

			std::cout << "-Weapons:\n";
			for (int i = 0; i < (int)WEAPONSLOT::NUM_SLOTS; i++) {
				const Weapon* tmp = dynamic_cast<Weapon*>(ps[j]->getEquippedWeaponAt(i));

				if (tmp) {
					std::cout << " " << tmp->Name << ", D:(" << tmp->MinDamage << "-" << tmp->MaxDamage << ")\n";
				}
			}



			std::cout << '\n';
			if (i < 1) {
				ps[j]->gainExp(100u);

				ArmorBuff arm_buff("StoneShield", 10, 5);
				StrengthBuff str_debuff("Weakness", 10, -2);
				ps[j]->applyBuff(str_debuff);
				ps[j]->applyBuff(arm_buff);
				
				ItemManager::Equip(LeatherArmor, &p1);
			}
		}
	}
	std::cout << "health before taking damage: " << p1.getCurrentHP() << '/' << p1.getMaxHP() << '\n';
	p1.takeDamage(20);
	std::cout << "health after taking damage: " << p1.getCurrentHP() << '/' << p1.getMaxHP() << '\n';
	Item* HealPotion = ItemManager::CreatePotion("Minor Heal Potion", 3u, 3u);
	ItemManager::MoveToBackpack(HealPotion, &p1);
	ItemManager::Use(HealPotion, &p1);
	std::cout << "health after using potion: " << p1.getCurrentHP() << '/' << p1.getMaxHP() << '\n';

	ItemManager::MoveToBackpack(
		ItemManager::CreateWeapon("Rusty Hand Axe", CoreStats(), WEAPONSLOT::MELEE, 2, 4),
		&p1);

	{
		auto inv = p1.getBackpackList();
		std::cout << "Inventory: ";
		for (auto it : inv) {
			std::cout << *it << ", ";
		}

		ItemManager::Use(HealPotion, &p1);
		ItemManager::Use(HealPotion, &p1);
	}
	std::cout << '\n';
	std::cout << "health after using 2 potions: " << p1.getCurrentHP() << '/' << p1.getMaxHP() << '\n';

	{
		auto inv = p1.getBackpackList();
		std::cout << "Inventory (after using potions): ";
		for (auto it : inv) {
			std::cout << *it << ", ";
		}
	}

	std::cout << "\n----END\n\n\n\n";



	return 0;
}