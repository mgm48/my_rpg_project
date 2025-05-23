#pragma once
#include "types.h"
#include "stats.h"
#include "corestats.h"
#include <string>

struct Buff {
	Buff(const char* name, uint16_t dur = 2u, t_stat str = 0,
		t_stat inte = 0, t_stat agi = 0, t_stat arm = 0, t_stat res = 0)
		: Name(name), Duration(dur), Modifiers( str, inte, agi, arm, res) {
	}
	
	Buff(const char* name, CoreStats cs, uint16_t dur = 2u)
	: Name(name), Duration(dur) {
		Modifiers = cs;
	}

	std::string Name;
	uint16_t Duration;

	CoreStats Modifiers;
};

struct StrengthBuff : public Buff {
	StrengthBuff(const char* name, uint16_t dur = 2u, t_stat str = 0) : Buff(name, dur, str, 0, 0, 0, 0) {}
};

struct IntellectBuff : public Buff {
	IntellectBuff(const char* name, uint16_t dur = 2u, t_stat inte = 0) : Buff(name, dur, 0, inte, 0, 0, 0) {}
};

struct AgilityBuff : public Buff {
	AgilityBuff(const char* name, uint16_t dur = 2u, t_stat agi = 0) : Buff(name, dur, 0, 0, agi, 0, 0) {}
};

struct ArmorBuff : public Buff {
	ArmorBuff(const char* name, uint16_t dur = 2u, t_stat arm = 0) : Buff(name, dur, 0, 0, 0, arm, 0) {}
};

struct ElementResBuff : public Buff {
	ElementResBuff(const char* name, uint16_t dur = 2u, t_stat res = 0) : Buff(name, dur, 0, 0, 0, 0, res) {}
};

struct OmniBuff : public Buff {
	OmniBuff(const char* name, uint16_t dur = 2u, t_stat o = 0) : Buff(name, dur, o, o, o, o, o) {}
};

