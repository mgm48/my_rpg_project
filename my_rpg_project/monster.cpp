#include "monster.h"
#include "random.h"

Monster::Monster(t_pw hp, t_dmg min, t_dmg max) : HP(hp), MinDamage(min), MaxDamage(max) {}

const t_dmg Monster::Attack() const { return Random::NTK(MinDamage, MaxDamage); }

const t_dmg Monster::GetMinDamage() const noexcept { return MinDamage; }
const t_dmg Monster::GetMaxDamage() const noexcept { return MaxDamage; }
