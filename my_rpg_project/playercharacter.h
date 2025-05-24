#pragma once
#include "stats.h"
#include "pointwell.h"
#include "abilities.h"
#include "items.h"
#include "types.h"
#include <memory>
#include <string>
#include <vector>
#include <algorithm>


class PlayerCharacterDelegate : public Stats { // delegate is a pure abstract class
public:
	static const t_exp LEVEL2AT = 100u;
	static const bool restore = true;
	static const bool norest = false;
	
	PlayerCharacterDelegate() : Stats() {
		CurrentLevel = 1u;
		CurrentExp = 0u;
		ExpToNextLevel = LEVEL2AT;
		HP = std::make_unique<PointWell>();
	}
	PlayerCharacterDelegate(t_pw bhp, t_stat str, t_stat in, t_stat agi) : Stats() {
		CurrentLevel = (t_level)1u;
		CurrentExp = (t_exp)0u;
		ExpToNextLevel = LEVEL2AT;
		HP = std::make_unique<PointWell>(bhp);
		increaseStats(str, in, agi);
	}

	void gainExp(t_exp gained_exp) {
		CurrentExp += gained_exp;
		while (check_if_leveled()) {}
	}
	void applyBuff(Buff b) { addNewBuff(b); }

	std::vector<Buff> getBuffList() { return Buffs; }

	t_level getLevel() { return CurrentLevel; }
	t_exp getCurrentExp() { return CurrentExp; }
	t_exp getExpToNextLevel() { return ExpToNextLevel; }

	virtual void LevelUp() = 0;
	virtual std::string getClassName() = 0;

	std::unique_ptr<PointWell> HP;
	std::unique_ptr<PointWell> MP;

	std::vector<Ability> Abilities;

protected:
	t_level CurrentLevel;
	t_exp CurrentExp;
	t_exp ExpToNextLevel;

	bool check_if_leveled() {
		static const t_level LEVELSCALAR = 2u;
		if (CurrentExp >= ExpToNextLevel) {
			CurrentLevel++;
			LevelUp();
			ExpToNextLevel *= LEVELSCALAR;
			return true;
		}
		return false;
	}
};
//las macros no entienden new lines, de ahí poner los backslashes
#define PCCONSTRUCT \
HP->setMax(BASEHP);\
HP->addCur(BASEHP);\
if (MP) { \
  MP->setMax(BASEMP); \
  MP->addCur(BASEMP); \
}\
increaseStats(BASESTR, BASEINT, BASEAGI);\


#define LEVELUP \
HP->addMax((t_pw)(BASEHP / 2.f), restore);\
increaseStats((t_stat)((BASESTR + 1u) / 2.f), (t_stat)((BASEINT + 1u) / 2.f), (t_stat)((BASEAGI + 1u) / 2.f));\


#define CHARACTERDEF(basehp, basemp, basestr, baseint, baseagi, rest)\
	static const bool restore = rest;\
	static const t_pw BASEHP = (t_pw)basehp;\
	static const t_pw BASEMP = (t_pw)basemp;\
	static const t_stat BASESTR = (t_stat)basestr;\
	static const t_stat BASEINT = (t_stat)baseint;\
	static const t_stat BASEAGI = (t_stat)baseagi;\


class Warrior : public PlayerCharacterDelegate {
public:
	CHARACTERDEF( 18, 0, 5, 2, 2, restore)

	std::string getClassName() override { return std::string("Warrior"); }

	Warrior() : PlayerCharacterDelegate(BASEHP, BASESTR, BASEINT, BASEAGI) {
		//PCCONSTRUCT
	}

private:
	void LevelUp() override {
		LEVELUP
		if (CurrentLevel == 2) {
			Abilities.emplace_back("PowerAttack", 0u, 3u, ABILITYTARGET::ENEMY, 4u, ABILITYSCALER::STR);
		}
	}
};

class Cleric : public PlayerCharacterDelegate {
public:

	CHARACTERDEF( 14, 10, 3, 5, 1, restore)

	std::string getClassName() override { return std::string("Cleric"); }
	
	Cleric() : PlayerCharacterDelegate(BASEHP, BASESTR, BASEINT, BASEAGI) {
		MP = std::make_unique<PointWell>(BASEMP);
		Abilities.emplace_back("Heal",2u,1u,ABILITYTARGET::ALLY, 2u, ABILITYSCALER::INT);
		//PCCONSTRUCT
	}
private:
	void LevelUp() override {
		LEVELUP
		if (CurrentLevel == 2) {
			Abilities.emplace_back("Smite", 2u, 1u, ABILITYTARGET::ENEMY, 2u, ABILITYSCALER::INT);
		}
	}
};

class Wizard : public PlayerCharacterDelegate {
public:
	CHARACTERDEF( 10, 14, 1, 8, 1, norest)


	std::string getClassName() override { return std::string("Wizard"); }

	Wizard() : PlayerCharacterDelegate(BASEHP, BASESTR, BASEINT, BASEAGI) {
		MP = std::make_unique<PointWell>(BASEMP);
		Abilities.emplace_back("Firebolt", 2u, 1u, ABILITYTARGET::ENEMY, 4u, ABILITYSCALER::INT);
		//PCCONSTRUCT
	}
private:
	void LevelUp() override {
		LEVELUP
			MP->addMax(1u, true);
	}
};

class Rogue : public PlayerCharacterDelegate {
public:
	CHARACTERDEF(12, 0, 3, 3, 5, norest)

	std::string getClassName() override { return std::string("Rogue"); }

	Rogue() : PlayerCharacterDelegate(BASEHP, BASESTR, BASEINT, BASEAGI) {
		//PCCONSTRUCT
	}
private:
	void LevelUp() override {
		LEVELUP
		if (CurrentLevel == 2) {
			Abilities.emplace_back("PreciseAttack", 0u, 3u, ABILITYTARGET::ENEMY, 6u, ABILITYSCALER::AGI);
		}
	}
};

class PlayerCharacter {
private: 
	PlayerCharacterDelegate* pcclass;
	Item* EquippedArmor[(unsigned long long)ARMORSLOT::NUM_SLOTS]; //the array wants unsigned long long
	Item* EquippedWeapons[(unsigned long long)WEAPONSLOT::NUM_SLOTS];
	CoreStats EquipmentModifier;
	std::vector<Item*> Backpack;
	void cleanup_backpack() { //to be refactored
		//stable partition puts everything that has the condition at the start, and the iterator is to the first marked for deletion item
		const auto to_remove = std::stable_partition(Backpack.begin(), Backpack.end(), //returns iterator
			[](const Item* i) -> bool {return !i->isMarkedForDeletion(); }); //lambda funtion

		std::for_each(to_remove, Backpack.end(), [](Item* i) {delete i; });

		Backpack.erase(to_remove, Backpack.end());
	}

	friend class ItemManager;

public:
	PlayerCharacter(PlayerCharacterDelegate* pc) : pcclass(pc), EquipmentModifier(0,0,0,0,0) {
		auto i = 0;
		for (i = 0; i < (unsigned long long)ARMORSLOT::NUM_SLOTS; i++) {
			EquippedArmor[i] = nullptr;
		}
		for (i = 0; i < (unsigned long long)WEAPONSLOT::NUM_SLOTS; i++) {
			EquippedWeapons[i] = nullptr;
		}
	}
	~PlayerCharacter() {
		delete pcclass;
		pcclass = nullptr;
		auto i = 0;
		for (i = 0; i < (unsigned long long)ARMORSLOT::NUM_SLOTS; i++) {
			if (EquippedArmor[i]) {
				delete EquippedArmor[i];
				EquippedArmor[i] = nullptr;
			}
		}
		for (i = 0; i < (unsigned long long)WEAPONSLOT::NUM_SLOTS; i++) {
			if (EquippedWeapons[i]) {
				delete EquippedWeapons[i];
				EquippedWeapons[i] = nullptr;
			}
		}
	}

	//Getters
	std::string getClassName() const { return pcclass->getClassName(); }
	t_level getLevel() const { return pcclass->getLevel(); }
	t_exp getCurrentExp() const { return pcclass->getCurrentExp(); }
	t_exp getExpToNextLevel() const { return pcclass->getExpToNextLevel(); }
	t_pw getMaxHP() const { return pcclass->HP->getMax(); }
	t_pw getCurrentHP() const { return pcclass->HP->getCurrent(); }
	t_pw getCurrentMP() const  {
		if (pcclass->MP)
			return pcclass->MP->getCurrent();
		else
			return 0;
	}
	t_pw getMaxMP() const  {
		if (pcclass->MP)
			return pcclass->MP->getMax();
		else
			return 0;
	}
	t_stat getStrength() const { return pcclass->getStrength(); }
	t_stat getIntellect() const { return pcclass->getIntellect(); }
	t_stat getAgility() const { return pcclass->getAgility(); }
	t_stat getArmor() const { return pcclass->getArmor(); }
	t_stat getElementRes() const { return pcclass->getElementRes(); }

	t_stat getTotalStrength() const { return pcclass->getTotalStrength() + EquipmentModifier.Strength; }
	t_stat getTotalIntellect() const { return pcclass->getTotalIntellect() + EquipmentModifier.Intellect; }
	t_stat getTotalAgility() const { return pcclass->getTotalAgility() + EquipmentModifier.Agility; }
	t_stat getTotalArmor() const { return pcclass->getTotalArmor() + EquipmentModifier.Armor; }
	t_stat getTotalElementRes() const { return pcclass->getTotalElementRes() + EquipmentModifier.ElementRes; }

	const std::vector<Ability> getAbilityList() const { return pcclass->Abilities; }
	const std::vector<Buff> getBuffList() const { return pcclass->getBuffList(); }
	const std::vector<Item*> getBackpackList() const { return Backpack; }

	EquipmentDelegate* getEquippedArmorAt(unsigned long long i) { 
		if (!EquippedArmor[i]) return nullptr; 
		return (dynamic_cast<Armor*>(EquippedArmor[i]->_data)); 
	}

	EquipmentDelegate* getEquippedWeaponAt(unsigned long long i) { 
		if (!EquippedWeapons[i]) return nullptr; 
		return (dynamic_cast<Weapon*>(EquippedWeapons[i]->_data)); 
	}

	//Mutators
	void gainExp(t_exp amt) { pcclass->gainExp(amt); }
	void takeDamage(t_pw dmg) { pcclass->HP->subCur(dmg); }
	void heal(t_pw hl) { pcclass->HP->addCur(hl); }

	void applyBuff(Buff buff) {
		pcclass->applyBuff(buff);
	}
	
private:

	// deleted constructors
	PlayerCharacter() = delete;
	PlayerCharacter(const PlayerCharacter&) = delete;
	PlayerCharacter(const PlayerCharacter&&) = delete;
};