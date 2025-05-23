#pragma once
#include "types.h"
#include "buffs.h"
#include <vector>


class Stats {
	CoreStats base;
	CoreStats mod; //modifiers

public:
	
	explicit Stats(t_stat str = 1, t_stat inte = 1, t_stat agi = 1, 
		t_stat arm = 0, t_stat res = 0) : base(str, inte, agi, arm, res){
	}
	
	t_stat getStrength() { return base.Strength; }
	t_stat getIntellect() { return base.Intellect; }
	t_stat getAgility() { return base.Agility; }
	t_stat getArmor() { return base.Armor; }
	t_stat getElementRes() { return base.ElementRes; }

	t_stat getStrengthModifier() { return mod.Strength; }
	t_stat getIntellectModifier() { return mod.Intellect; }
	t_stat getAgilityModifier() { return mod.Agility; }
	t_stat getArmorModifier() { return mod.Armor; }
	t_stat getElementResModifier() { return mod.ElementRes; }

	t_stat getTotalStrength() { return (base.Strength + mod.Strength > 1) ? base.Strength + mod.Strength : 1; }
	t_stat getTotalIntellect() { return (base.Intellect + mod.Intellect > 1) ? base.Intellect + mod.Intellect : 1; }
	t_stat getTotalAgility() { return (base.Agility + mod.Agility > 1) ? base.Agility + mod.Agility : 1;}
	t_stat getTotalArmor() { return (base.Armor + mod.Armor > 0) ? base.Armor + mod.Armor : 0;}
	t_stat getTotalElementRes() { return (base.ElementRes + mod.ElementRes > 0) ? base.ElementRes + mod.ElementRes : 0; }


protected:
	std::vector<Buff> Buffs;

	void increaseStats(t_stat str = 0, t_stat inte = 0, t_stat agi = 0, t_stat arm = 0, t_stat res = 0) {
		base.add(str, inte, agi, arm, res);
	}
	void increaseStats(CoreStats cs) {
		base += cs;
	}
	void addNewBuff(Buff b) {
		for (auto& buff : Buffs) { //if the buff is already in the list of applied buffs
			if (b.Name == buff.Name) {
				buff.Duration = b.Duration;
				return;
			}
		}
		Buffs.push_back(b);
		recalculate_buffs();
	}
	
private:
	void recalculate_buffs() {

		mod.reset();

		for (const auto& b : Buffs) {
			mod += b.Modifiers;
		}
	}
};