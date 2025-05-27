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
const bool CoreStats::any() const noexcept { return Strength != 0 || Intellect != 0 || Agility != 0 || Armor != 0 || ElementRes != 0; }

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

std::ostream& operator<<(std::ostream& os, const CoreStats& cs) {
	os << "[ ";
	if (cs.Strength != 0) { os << ((cs.Strength > 0) ? "+" : "") << cs.Strength << " str "; }
	if (cs.Intellect != 0) { os << ((cs.Intellect > 0) ? "+" : "") << cs.Intellect << " int "; }
	if (cs.Agility != 0) { os << ((cs.Agility > 0) ? "+" : "") << cs.Agility << " agi "; }
	if (cs.Armor != 0) { os << ((cs.Armor > 0) ? "+" : "") << cs.Armor << " arm "; }
	if (cs.ElementRes != 0) { os << ((cs.ElementRes > 0) ? "+" : "") << cs.ElementRes << " res "; }
	os << "]";
	return os;
}