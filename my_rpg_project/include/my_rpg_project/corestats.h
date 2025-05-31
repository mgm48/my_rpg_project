#pragma once
#include "typing.h"
#include <iostream>


struct CoreStats {

	t_stat Strength;
	t_stat Intellect;
	t_stat Agility;
	t_stat Armor;
	t_stat ElementRes;

	CoreStats();
	CoreStats(t_stat str, t_stat inte, t_stat agi, t_stat arm, t_stat res);
	CoreStats(t_stat all);

	void set(t_stat str = 0, t_stat inte = 0, t_stat agi = 0, t_stat arm = 0, t_stat res = 0);
	void add(t_stat str = 0, t_stat inte = 0, t_stat agi = 0, t_stat arm = 0, t_stat res = 0);
	void remove(t_stat str = 0, t_stat inte = 0, t_stat agi = 0, t_stat arm = 0, t_stat res = 0);
	void reset();
	const bool any() const noexcept;

	CoreStats& operator+=(const CoreStats& rhs);
	CoreStats& operator-=(const CoreStats& rhs);
	CoreStats& operator=(const t_stat& rhs);

	friend std::ostream& operator<<(std::ostream& os, const CoreStats& cs);
};
