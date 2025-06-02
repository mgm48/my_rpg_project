#pragma once
#include "typing.h"
#include "corestats.h"
#include <string>

struct Buff {
	Buff();

	Buff(const char* name,t_stat str = 0, t_stat inte = 0, 
		t_stat agi = 0, t_stat arm = 0, t_stat res = 0, uint16_t dur = 2u);
	
	Buff(const char* name, CoreStats cs, uint16_t dur = 2u);

	std::string Name;
	uint16_t Duration;

	CoreStats Modifiers;

	Buff& operator=(const char* name);
	
};


