#pragma once
#include "typing.h"
#include "pointwell.h"
#include <memory>
#include <string>

class Monster {
public:
	Monster();
	Monster(t_pw hp, t_dmg min, t_dmg max, t_exp xp);
	Monster(std::string nam, t_pw hp, t_dmg min, t_dmg max, t_exp xp);
	std::string Name;
	PointWell HP;
	t_exp ExpWorth;
	[[nodiscard]] const t_dmg Attack() const;
	[[nodiscard]] const t_dmg GetMinDamage() const noexcept;
	[[nodiscard]] const t_dmg GetMaxDamage() const noexcept;
	[[nodiscard]] const t_exp GetExpYield() const noexcept;
private:
	t_dmg MinDamage;
	t_dmg MaxDamage;
	Monster(const Monster&) = delete;
	Monster(const Monster&&) = delete;

	friend class Location;
};

