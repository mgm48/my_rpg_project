#include "corestats.h"

CoreStats::CoreStats() {
	Strength = 0;
	Intellect = 0;
	Agility = 0;
	Armor = 0;
	ElementRes = 0;
}

CoreStats::CoreStats(t_stat str, t_stat inte, t_stat agi, t_stat arm, t_stat res)
	: Strength(str), Intellect(inte), Agility(agi), Armor(arm), ElementRes(res) {}

CoreStats::CoreStats(t_stat all)
	: Strength(all), Intellect(all), Agility(all), Armor(all), ElementRes(all) {
}

void CoreStats::set(t_stat str, t_stat inte, t_stat agi, t_stat arm, t_stat res) {
	this->Strength = str;
	this->Intellect = inte;
	this->Agility = agi;
	this->Armor = arm;
	this->ElementRes = res;
};
void CoreStats::add(t_stat str, t_stat inte, t_stat agi, t_stat arm, t_stat res) {
	this->Strength += str;
	this->Intellect += inte;
	this->Agility += agi;
	this->Armor += arm;
	this->ElementRes += res;
};
void CoreStats::remove(t_stat str, t_stat inte, t_stat agi, t_stat arm, t_stat res) {
	this->Strength -= str;
	this->Intellect -= inte;
	this->Agility -= agi;
	this->Armor -= arm;
	this->ElementRes -= res;
};
void CoreStats::reset() {
	this->Strength = 0;
	this->Intellect = 0;
	this->Agility = 0;
	this->Armor = 0;
	this->ElementRes = 0;
}


CoreStats& CoreStats::operator+=(const CoreStats& rhs) {
	this->Strength += rhs.Strength;
	this->Intellect += rhs.Intellect;
	this->Agility += rhs.Agility;
	this->Armor += rhs.Armor;
	this->ElementRes += rhs.ElementRes;
	return *this;
};
CoreStats& CoreStats::operator-=(const CoreStats& rhs) {
	this->Strength -= rhs.Strength;
	this->Intellect -= rhs.Intellect;
	this->Agility -= rhs.Agility;
	this->Armor -= rhs.Armor;
	this->ElementRes -= rhs.ElementRes;
	return *this;
};
CoreStats& CoreStats::operator=(const t_stat& rhs) { //igualar a un solo stat
	this->Strength = rhs;
	this->Intellect = rhs;
	this->Agility = rhs;
	this->Armor = rhs;
	this->ElementRes = rhs;
	return *this;
}