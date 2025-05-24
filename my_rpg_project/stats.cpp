#include "stats.h"

Stats::Stats(t_stat str, t_stat inte, t_stat agi,t_stat arm, t_stat res) 
	: base(str, inte, agi, arm, res) {}

t_stat Stats::GetStrength() { return base.Strength; }
t_stat Stats::GetIntellect() { return base.Intellect; }
t_stat Stats::GetAgility() { return base.Agility; }
t_stat Stats::GetArmor() { return base.Armor; }
t_stat Stats::GetElementRes() { return base.ElementRes; }

t_stat Stats::GetTotalStrength() { return (base.Strength + mod.Strength > 1) ? base.Strength + mod.Strength : 1; }
t_stat Stats::GetTotalIntellect() { return (base.Intellect + mod.Intellect > 1) ? base.Intellect + mod.Intellect : 1; }
t_stat Stats::GetTotalAgility() { return (base.Agility + mod.Agility > 1) ? base.Agility + mod.Agility : 1; }
t_stat Stats::GetTotalArmor() { return (base.Armor + mod.Armor > 0) ? base.Armor + mod.Armor : 0; }
t_stat Stats::GetTotalElementRes() { return (base.ElementRes + mod.ElementRes > 0) ? base.ElementRes + mod.ElementRes : 0; }


void Stats::increase_stats(t_stat str, t_stat inte, t_stat agi, t_stat arm, t_stat res) { base.add(str, inte, agi, arm, res); }
void Stats::increase_stats(CoreStats cs) { base += cs; }

void Stats::add_buff(Buff b) {
	for (auto& buff : Buffs) { //if the buff is already in the list of applied buffs
		if (b.Name == buff.Name) {
			buff.Duration = b.Duration;
			return;
		}
	}
	Buffs.push_back(b);
	recalculate_buffs();
}
void Stats::recalculate_buffs() {
	CoreStats tmp_mod;
	//mod.reset();
	for (const auto& b : Buffs) {
		tmp_mod += b.Modifiers;
	}
	mod = tmp_mod;
}
