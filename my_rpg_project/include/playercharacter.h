#pragma once
#include "stats.h"
#include "pointwell.h"
#include "ability.h"
#include "item.h"
#include "types.h"
#include "item_manager.h"
#include <memory>
#include <string>
#include <vector>
#include <algorithm>


class PlayerCharacterDelegate : public Stats { // delegate is a pure abstract class
public:
	static const t_exp LEVEL2AT = 100u;
	PlayerCharacterDelegate();
	PlayerCharacterDelegate(t_pw bhp, t_stat str, t_stat in, t_stat agi);
	virtual ~PlayerCharacterDelegate() = 0;
	virtual const char* GetClass() = 0;
	[[nodiscard]] t_level GetLevel() const noexcept;
	[[nodiscard]] t_exp GetCurrentExp() const noexcept;
	[[nodiscard]] t_exp GetExpToNextLevel() const noexcept;
	void GiveExp(const t_exp gained_exp) noexcept;
	std::unique_ptr<PointWell> HP;
	std::unique_ptr<PointWell> MP;
	std::vector<Ability> Abilities;

	void ApplyBuff(Buff b) { add_buff(b); }
	std::vector<Buff> GetBuffList() { return Buffs; }
protected:
private:
	t_exp _current_exp;
	t_exp _exp_to_next_level;
	virtual void level_char_up() = 0;
	t_level _current_level;
	[[nodiscard]] const bool check_if_leveled() noexcept; 
};



class PlayerCharacter final {
public:
	PlayerCharacter(PlayerCharacterDelegate* pc);
	~PlayerCharacter();

	//Getters
	[[nodiscard]] const char* GetClass() const noexcept;
	[[nodiscard]] const t_level GetLevel() const noexcept;
	[[nodiscard]] const t_exp GetCurrentExp() const noexcept;
	[[nodiscard]] const t_exp GetExpToNextLevel() const noexcept;

	[[nodiscard]] const bool IsMaxHP() const noexcept;
	[[nodiscard]] const t_pw GetMaxHP() const noexcept;
	[[nodiscard]] const t_pw GetCurrentHP() const noexcept;
	[[nodiscard]] const bool IsMagicUser() const noexcept;
	[[nodiscard]] const t_pw GetCurrentMP() const noexcept;
	[[nodiscard]] const t_pw GetMaxMP() const noexcept;

	[[nodiscard]] const t_stat GetStrength() const noexcept;
	[[nodiscard]] const t_stat GetIntellect() const noexcept;
	[[nodiscard]] const t_stat GetAgility() const noexcept;
	[[nodiscard]] const t_stat GetArmor() const noexcept;
	[[nodiscard]] const t_stat GetElementRes() const noexcept;

	[[nodiscard]] const t_stat GetTotalStrength() const noexcept;
	[[nodiscard]] const t_stat GetTotalIntellect() const noexcept;
	[[nodiscard]] const t_stat GetTotalAgility() const noexcept;
	[[nodiscard]] const t_stat GetTotalArmor() const noexcept;
	[[nodiscard]] const t_stat GetTotalElementRes() const noexcept;

	[[nodiscard]] const std::vector<Ability> GetAbilityList() const noexcept;
	[[nodiscard]] const std::vector<Buff> GetBuffList() const noexcept;
	[[nodiscard]] const std::vector<Item*> GetBackpackList() const noexcept;

	[[nodiscard]] const Armor* GetEquippedArmorAt(unsigned long long i) noexcept;
	[[nodiscard]] const Weapon* GetEquippedWeaponAt(unsigned long long i) noexcept;

	const int Defend(t_dmg damage) const noexcept;
	const t_dmg MeleeAttack() const noexcept;
	const t_dmg RangedAttack() const noexcept;

	//Mutators
	void GiveExp(t_exp amt) noexcept;
	void TakeDamage(t_pw dmg) noexcept;
	void HealthModify(t_pw amt) noexcept;
	void Heal(t_pw hl) noexcept;
	void ApplyBuff(Buff buff) noexcept;
	
private:
	PlayerCharacterDelegate* _player_class;
	std::vector<Item*> _backpack;

	Item* _equipped_armor[(unsigned long long)ARMORSLOT::NUM_SLOTS]; //the array wants unsigned long long
	Item* _equipped_weapons[(unsigned long long)WEAPONSLOT::NUM_SLOTS];
	CoreStats _equip_modifier;

	void move_to_backpack(Item* item_to_move) noexcept;
	void cleanup_backpack() noexcept;
	friend class ItemManager;

	PlayerCharacter() = delete;
	PlayerCharacter(const PlayerCharacter&) = delete;
	PlayerCharacter(const PlayerCharacter&&) = delete;
};