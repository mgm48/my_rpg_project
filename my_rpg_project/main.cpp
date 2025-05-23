#include <iostream>
#include "playercharacter.h"
#include "item_manager.h"
int main() {
	const int n = 2;
	PlayerCharacter p1(new Warrior());
	PlayerCharacter p2(new Warrior());
	PlayerCharacter p3(new Wizard());
	PlayerCharacter p4(new Rogue());
	PlayerCharacter p5(new Cleric());
	PlayerCharacter* ps[n] = { &p1, &p2 };//, &p3, &p4, &p5 };


	//armor stuff
	CoreStats plate_armor_stats(0, 0, 0, 5, 3);
	Item* FullPlateMail = ItemManager::createArmor("Shiny Plate Armor", plate_armor_stats, ARMORSLOT::CHEST);
	if (p1.Equip(FullPlateMail))
		std::cout << "equip success!\n";
	else
		std::cout << "equip failed!\n";

	CoreStats leather_helm_stats(0, 0, 0, 1, 1);
	Item* LeatherHelm = ItemManager::createArmor("Plain Leather Helmet", leather_helm_stats, ARMORSLOT::HELMET);
	if (p2.Equip(LeatherHelm))
		std::cout << "equip success!\n";
	else
		std::cout << "equip failed!\n";

	Item* LongSword = ItemManager::createWeapon("Long Sword", CoreStats(), WEAPONSLOT::MELEE, 3, 9);
	if (p1.Equip(LongSword))
		std::cout << "equip success!\n";
	else
		std::cout << "equip failed!\n";

	Item* HealPotion = ItemManager::createPotion("Minor Heal Potion", 1u, 5u);



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
					std::cout << " " << tmp->Name << ", D:(" << tmp->minDmg << "-" << tmp->maxDmg << ")\n";
				}
			}



			std::cout << '\n';
			if (i < 1) {
				ps[j]->gainExp(100u);
				if (j == 1) {
					ArmorBuff arm_buff("StoneShield", 10, 5);
					StrengthBuff str_debuff("Weakness", 10, -2);
					ps[j]->applyBuff(str_debuff);
					ps[j]->applyBuff(arm_buff);
				}
			}

			ps[j]->takeDamage(4);
			std::cout << "Ouch! Before healing!" << "-HP: " << ps[j]->getCurrentHP() << '/' << ps[j]->getMaxHP() << '\n';
			if (ps[j]->Use(HealPotion))
				std::cout << "Healed!" << ps[j]->getCurrentHP() << '/' << ps[j]->getMaxHP() << '\n';
			else
				std::cout << "heal failed!\n";

		}
	}



	return 0;
}