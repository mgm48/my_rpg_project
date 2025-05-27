#include "playercharacter.h"
#include "random.h"
#include <memory>

//PlayerCharacterDelegate

PlayerCharacterDelegate::PlayerCharacterDelegate() : Stats() {
	_current_level = 1u;
	_current_exp = 0u;
	_exp_to_next_level = LEVEL2AT;
	HP = std::make_unique<PointWell>();
}
PlayerCharacterDelegate::PlayerCharacterDelegate(t_pw bhp, t_stat str, t_stat in, t_stat agi) : Stats(str, in, agi) {
	_current_level = (t_level)1u;
	_current_exp = (t_exp)0u;
	_exp_to_next_level = LEVEL2AT;
	HP = std::make_unique<PointWell>(bhp);
}

PlayerCharacterDelegate::~PlayerCharacterDelegate() {}

[[nodiscard]] t_level PlayerCharacterDelegate::GetLevel() const noexcept { return _current_level; }
[[nodiscard]] t_exp PlayerCharacterDelegate::GetCurrentExp() const noexcept { return _current_exp; }
[[nodiscard]] t_exp PlayerCharacterDelegate::GetExpToNextLevel() const noexcept { return _exp_to_next_level; }

void PlayerCharacterDelegate::GiveExp(const t_exp gained_exp) noexcept {
	_current_exp += gained_exp;
	while (check_if_leveled()) {}
}

[[nodiscard]] const bool PlayerCharacterDelegate::check_if_leveled() noexcept {
	static const t_level LEVELSCALAR = 2u;
	if (_current_exp >= _exp_to_next_level) {
		_current_level++;
		level_char_up();
		_exp_to_next_level *= LEVELSCALAR;
		return true;
	}
	return false;
}

//PlayerCharacter

void PlayerCharacter::move_to_backpack(Item* item_to_move) noexcept { _backpack.push_back(item_to_move); }
void PlayerCharacter::cleanup_backpack() noexcept { //to be refactored
	//stable partition puts everything that has the condition at the start, and the iterator is to the first marked for deletion item
	const auto to_remove = std::stable_partition( _backpack.begin(), _backpack.end(), //returns iterator
		[](const Item* i) -> bool {return !i->isMarkedForDeletion(); } ); //lambda funtion

	std::for_each(to_remove, _backpack.end(), [](Item* i) {ItemManager::DeleteItem(i); }); //deletes the actual items
	_backpack.erase(to_remove, _backpack.end()); //delete the pointers to the items


	const auto to_remove_ref = std::stable_partition(_backpack.begin(), _backpack.end(), 
		[](const Item* i) -> bool {return !i->isMarkedAsBackpackRefGone(); });
	_backpack.erase(to_remove_ref, _backpack.end());

}

PlayerCharacter::PlayerCharacter(PlayerCharacterDelegate* pc) : _player_class(pc), _equip_modifier() {
	auto i = 0;
	for (i = 0; i < (unsigned long long)ARMORSLOT::NUM_SLOTS; i++) {
		_equipped_armor[i] = nullptr;
	}
	for (i = 0; i < (unsigned long long)WEAPONSLOT::NUM_SLOTS; i++) {
		_equipped_weapons[i] = nullptr;
	}
}
PlayerCharacter::~PlayerCharacter() {
	delete _player_class;
	_player_class = nullptr;
	auto i = 0;
	for (i = 0; i < (unsigned long long)ARMORSLOT::NUM_SLOTS; i++) {
		if (_equipped_armor[i]) {
			delete _equipped_armor[i];
			_equipped_armor[i] = nullptr;
		}
	}
	for (i = 0; i < (unsigned long long)WEAPONSLOT::NUM_SLOTS; i++) {
		if (_equipped_weapons[i]) {
			delete _equipped_weapons[i];
			_equipped_weapons[i] = nullptr;
		}
	}
}

[[nodiscard]] const char* PlayerCharacter::GetClass() const noexcept{ return _player_class->GetClass() ;}

[[nodiscard]] const t_level PlayerCharacter::GetLevel() const noexcept { return _player_class->GetLevel(); }
[[nodiscard]] const t_exp PlayerCharacter::GetCurrentExp() const noexcept { return _player_class->GetCurrentExp(); }
[[nodiscard]] const t_exp PlayerCharacter::GetExpToNextLevel() const noexcept { return _player_class->GetExpToNextLevel(); }

[[nodiscard]] const bool PlayerCharacter::IsMaxHP() const noexcept { return _player_class->HP->IsFull(); }
[[nodiscard]] const t_pw PlayerCharacter::GetMaxHP() const noexcept { return _player_class->HP->GetMax(); }
[[nodiscard]] const t_pw PlayerCharacter::GetCurrentHP() const noexcept { return _player_class->HP->GetCurrent(); }
[[nodiscard]] const bool PlayerCharacter::IsMagicUser() const noexcept { if (_player_class->MP) { return true; } else { return false; } }
[[nodiscard]] const t_pw PlayerCharacter::GetCurrentMP() const noexcept {
	if (_player_class->MP)
		return _player_class->MP->GetCurrent();
	else
		return 0;
}
[[nodiscard]] const t_pw PlayerCharacter::GetMaxMP() const noexcept {
	if (_player_class->MP)
		return _player_class->MP->GetMax();
	else
		return 0;
}

[[nodiscard]] const t_stat PlayerCharacter::GetStrength() const noexcept { return _player_class->GetStrength(); }
[[nodiscard]] const t_stat PlayerCharacter::GetIntellect() const noexcept { return _player_class->GetIntellect(); }
[[nodiscard]] const t_stat PlayerCharacter::GetAgility() const noexcept { return _player_class->GetAgility(); }
[[nodiscard]] const t_stat PlayerCharacter::GetArmor() const noexcept { return _player_class->GetArmor(); }
[[nodiscard]] const t_stat PlayerCharacter::GetElementRes() const noexcept { return _player_class->GetElementRes(); }

[[nodiscard]] const t_stat PlayerCharacter::GetTotalStrength() const noexcept { return _player_class->GetTotalStrength() + _equip_modifier.Strength; }
[[nodiscard]] const t_stat PlayerCharacter::GetTotalIntellect() const noexcept { return _player_class->GetTotalIntellect() + _equip_modifier.Intellect; }
[[nodiscard]] const t_stat PlayerCharacter::GetTotalAgility() const noexcept { return _player_class->GetTotalAgility() + _equip_modifier.Agility; }
[[nodiscard]] const t_stat PlayerCharacter::GetTotalArmor() const noexcept { return _player_class->GetTotalArmor() + _equip_modifier.Armor; }
[[nodiscard]] const t_stat PlayerCharacter::GetTotalElementRes() const noexcept { return _player_class->GetTotalElementRes() + _equip_modifier.ElementRes; }

[[nodiscard]] const std::vector<Ability> PlayerCharacter::GetAbilityList() const noexcept { return _player_class->Abilities; }
[[nodiscard]] const std::vector<Buff> PlayerCharacter::GetBuffList() const noexcept { return _player_class->GetBuffList(); }
[[nodiscard]] const std::vector<Item*> PlayerCharacter::GetBackpackList() const noexcept { return _backpack; }

[[nodiscard]] const Armor* PlayerCharacter::GetEquippedArmorAt(unsigned long long i) noexcept {
	if (!_equipped_armor[i]) return nullptr;
	return (dynamic_cast<Armor*>(_equipped_armor[i]->_data));
}
[[nodiscard]] const Weapon* PlayerCharacter::GetEquippedWeaponAt(unsigned long long i) noexcept {
	if (!_equipped_weapons[i]) return nullptr;
	return (dynamic_cast<Weapon*>(_equipped_weapons[i]->_data));
}

const int PlayerCharacter::Defend(t_dmg damage) const noexcept {
	int damage_to_take = damage - GetTotalArmor();
	if (damage_to_take < 1 && damage * 4 < GetTotalArmor()) { damage_to_take = 0; }
	else if (damage_to_take < 1) { damage_to_take = 1; }

	return damage_to_take;
}

const t_dmg PlayerCharacter::MeleeAttack() const noexcept {
	t_dmg dmg_done = 0;

	if (_equipped_weapons[(unsigned long long)WEAPONSLOT::MELEE]) {
		const Weapon* equipped_weapon = dynamic_cast<Weapon*>(_equipped_weapons[(unsigned long long)WEAPONSLOT::MELEE]->_data);
		if (equipped_weapon) {
			dmg_done = Random::NTK(equipped_weapon->MinDamage, equipped_weapon->MaxDamage);
		}
	}
	//default damage is 1/4 of total strength
	dmg_done += t_dmg(GetTotalStrength() / 4.f);

	return (dmg_done > 1) ? dmg_done : 1;
}
const t_dmg PlayerCharacter::RangedAttack() const noexcept {
	t_dmg dmg_done = 0;
	if (_equipped_weapons[(unsigned long long)WEAPONSLOT::RANGED]) {
		const Weapon* equipped_weapon = dynamic_cast<Weapon*>(_equipped_weapons[(unsigned long long)WEAPONSLOT::RANGED]->_data);
		// if weapon exists get the damage, else the base damage stays 0
		if (equipped_weapon) {
			dmg_done = Random::NTK(equipped_weapon->MinDamage, equipped_weapon->MaxDamage);
			dmg_done += t_dmg(GetTotalAgility() / 4.f);  // add 1/4 of agi as bonus ranged damage
		}
	}
	return (dmg_done > 1) ? dmg_done : 1;
}

void PlayerCharacter::GiveExp(t_exp amt) noexcept { _player_class->GiveExp(amt); }
void PlayerCharacter::TakeDamage(t_pw dmg) noexcept { _player_class->HP->SubCur(dmg); }
void PlayerCharacter::HealthModify(t_pw amt) noexcept { _player_class->HP->ModCur(amt); }
void PlayerCharacter::Heal(t_pw hl) noexcept { _player_class->HP->AddCur(hl); }
void PlayerCharacter::ApplyBuff(Buff buff) noexcept { _player_class->ApplyBuff(buff); }