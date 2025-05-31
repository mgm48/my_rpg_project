#pragma once
#include "typing.h"
#include "pointwell.h"
#include <memory>

class Monster {
public:
	Monster(t_pw hp, t_dmg min, t_dmg max);
	PointWell HP;
	[[nodiscard]] const t_dmg Attack() const;
	[[nodiscard]] const t_dmg GetMinDamage() const noexcept;
	[[nodiscard]] const t_dmg GetMaxDamage() const noexcept;
private:
	t_dmg MinDamage;
	t_dmg MaxDamage;
	Monster() = delete;
	Monster(const Monster&) = delete;
	Monster(const Monster&&) = delete;
};

