#include "monster.h"
#include "random.h"

Monster::Monster() : HP(1), MinDamage(1), MaxDamage(1), ExpWorth(1) {
	Name = "NULL";
}

Monster::Monster(std::string nam,t_pw hp, t_dmg min, t_dmg max, t_exp xp)
	: Name(nam), HP(hp), MinDamage(min), MaxDamage(max), ExpWorth(xp) {}

Monster::Monster(t_pw hp, t_dmg min, t_dmg max, t_exp xp) 
	: HP(hp), MinDamage(min), MaxDamage(max), ExpWorth(xp) {
	Name = "Generic Monster";
}

const t_dmg Monster::Attack() const { if (MinDamage != MaxDamage) { return Random::NTK(MinDamage, MaxDamage); } else { return MaxDamage; } }

const t_dmg Monster::GetMinDamage() const noexcept { return MinDamage; }
const t_dmg Monster::GetMaxDamage() const noexcept { return MaxDamage; }
const t_exp Monster::GetExpYield() const noexcept { return ExpWorth; }