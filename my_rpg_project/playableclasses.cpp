#include "playableclasses.h"

//WARRIOR
Warrior::Warrior() : PlayerCharacterDelegate(BASEHP, BASESTR, BASEINT, BASEAGI) {}
const char* Warrior::GetClass() noexcept { return "Warrior"; }
void Warrior::level_char_up() noexcept {
	LEVELUP
		if (GetLevel() == 2) {
			Abilities.emplace_back("PowerAttack", 0u, 3u, 4u, nullptr, ABILITYTARGET::ENEMY, ABILITYSCALER::STR);
		}
}

//CLERIC
Cleric::Cleric() : PlayerCharacterDelegate(BASEHP, BASESTR, BASEINT, BASEAGI) {
	MP = std::make_unique<PointWell>(BASEMP);
	Abilities.emplace_back("Heal", 2u, 1u, 2u, nullptr, ABILITYTARGET::ALLY, ABILITYSCALER::INT);
}
const char* Cleric::GetClass() noexcept { return "Cleric"; }
void Cleric::level_char_up() noexcept {
	LEVELUP
		if (GetLevel() == 2) {
			Abilities.emplace_back("Smite", 2u, 1u, 2u, nullptr, ABILITYTARGET::ENEMY, ABILITYSCALER::INT);
		}
}

//WIZARD
Wizard::Wizard() : PlayerCharacterDelegate(BASEHP, BASESTR, BASEINT, BASEAGI) {
	MP = std::make_unique<PointWell>(BASEMP);
	Abilities.emplace_back("Firebolt", 2u, 1u, 4u, nullptr, ABILITYTARGET::ENEMY, ABILITYSCALER::INT);
}
const char* Wizard::GetClass() noexcept { return "Wizard"; }
void Wizard::level_char_up() noexcept {
	LEVELUP
		if (GetLevel() == 2) {
			Abilities.emplace_back("IceBolt", 3u, 1u, 6u, nullptr, ABILITYTARGET::ENEMY, ABILITYSCALER::INT);
			increase_stats(0, 1);
		}
}

//ROGUE
Rogue::Rogue() : PlayerCharacterDelegate(BASEHP, BASESTR, BASEINT, BASEAGI) {}
const char* Rogue::GetClass() noexcept { return "Rogue"; }
void Rogue::level_char_up() noexcept {
	LEVELUP
		if (GetLevel() == 2) {
			Abilities.emplace_back("PreciseAttack", 0u, 3u, 6u, nullptr, ABILITYTARGET::ENEMY, ABILITYSCALER::AGI);
		}
}