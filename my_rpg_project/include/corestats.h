#pragma once
#include "types.h"


struct CoreStats {

	t_stat Strength;
	t_stat Intellect;
	t_stat Agility;
	t_stat Armor;
	t_stat ElementRes;

	CoreStats(t_stat str = 0, t_stat inte = 0, t_stat agi = 0, t_stat arm = 0, t_stat res = 0)
		: Strength(str), Intellect(inte), Agility(agi), Armor(arm), ElementRes(res) {
	}

	void set(t_stat str = 0, t_stat inte = 0, t_stat agi = 0, t_stat arm = 0, t_stat res = 0) {
		this->Strength = str;
		this->Intellect = inte;
		this->Agility = agi;
		this->Armor = arm;
		this->ElementRes = res;
	};

	void add(t_stat str = 0, t_stat inte = 0, t_stat agi = 0, t_stat arm = 0, t_stat res = 0) {
		this->Strength += str;
		this->Intellect += inte;
		this->Agility += agi;
		this->Armor += arm;
		this->ElementRes += res;
	};
	void remove(t_stat str = 0, t_stat inte = 0, t_stat agi = 0, t_stat arm = 0, t_stat res = 0) {
		this->Strength -= str;
		this->Intellect -= inte;
		this->Agility -= agi;
		this->Armor -= arm;
		this->ElementRes -= res;
	};

	void reset() {
		this->Strength = 0;
		this->Intellect = 0;
		this->Agility = 0;
		this->Armor = 0;
		this->ElementRes = 0;
	}


	CoreStats& operator+=(const CoreStats& rhs) {
		this->Strength += rhs.Strength;
		this->Intellect += rhs.Intellect;
		this->Agility += rhs.Agility;
		this->Armor += rhs.Armor;
		this->ElementRes += rhs.ElementRes;
		return *this;
	};

	CoreStats& operator-=(const CoreStats& rhs) {
		this->Strength -= rhs.Strength;
		this->Intellect -= rhs.Intellect;
		this->Agility -= rhs.Agility;
		this->Armor -= rhs.Armor;
		this->ElementRes -= rhs.ElementRes;
		return *this;
	};

	CoreStats& operator=(const t_stat & rhs) { //igualar a un solo stat
		this->Strength = rhs;
		this->Intellect = rhs;
		this->Agility = rhs;
		this->Armor = rhs;
		this->ElementRes = rhs;
		return *this;
	}

	
};
