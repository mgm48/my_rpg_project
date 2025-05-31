#pragma once
#include "typing.h"
#include "buff.h"
#include <vector>


class Stats {
	CoreStats base;
	CoreStats mod; //modifiers
public:
	Stats(t_stat str = 1, t_stat inte = 1, t_stat agi = 1, t_stat arm = 0, t_stat res = 0);
	
	t_stat GetStrength();
	t_stat GetIntellect();
	t_stat GetAgility();
	t_stat GetArmor();
	t_stat GetElementRes();

	t_stat GetTotalStrength();
	t_stat GetTotalIntellect();
	t_stat GetTotalAgility();
	t_stat GetTotalArmor();
	t_stat GetTotalElementRes();
protected:
	void increase_stats(t_stat str = 0, t_stat inte = 0, t_stat agi = 0, t_stat arm = 0, t_stat res = 0);
	void increase_stats(CoreStats cs);
	std::vector<Buff> Buffs;
	void add_buff(Buff b);
private:
	void recalculate_buffs();
};
