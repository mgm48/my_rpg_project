#include "buff.h"

Buff::Buff() {
	Name = "undefined";
	Duration = 2u;
	Modifiers = CoreStats();
}

Buff::Buff(const char* name, uint16_t dur, t_stat str, t_stat inte, t_stat agi, t_stat arm, t_stat res)
	: Name(name), Duration(dur), Modifiers(str, inte, agi, arm, res) {
}

Buff::Buff(const char* name, CoreStats cs, uint16_t dur): Name(name), Duration(dur) {
	Modifiers = cs;
}

Buff& Buff::operator=(const char* name) {
	this->Name = std::string(name);
	this->Duration = 2u;
	this->Modifiers = CoreStats(0);
	return *this;
}