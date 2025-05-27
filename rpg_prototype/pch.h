#pragma once
#include "monster.h"
#include "playercharacter.h"
#include "playableclasses.h"

struct Player {
	Player(PlayerCharacterDelegate* p) : us(p) {};
	Player() = delete;
	bool IsAlive() { return us.GetCurrentHP() > 0; }
	PlayerCharacter us;
	int prev_ypos = 10;
	int prev_xpos = 10;
	int ypos = 10;
	int xpos = 10;
};

//enum class CLASS { CLERIC, WARRIOR, ROGUE, WIZARD, NUM_CLASSES };
const char* descriptions[4]{ //so that choice + 1 == descriptions 
	"just a little innocent cleric",
	"            A            Brave            Warrior.",
	"the rascal, the scoundrel, the thief, THEEEE ROGUE",
	"The prestigious, magnificent Wizard."
};

struct Fightable {
	Fightable(int hp, int min, int max) : monster(hp, min, max) {
		xpworth = (hp + min + max) * 2;
	}
	bool IsAlive() { return (monster.HP.GetCurrent() > 0); }
	Monster monster;
	int xpos = 1;
	int ypos = 1;
	int xpworth;
	Fightable() = delete;
};

const int DIM_Y = 12;
const int DIM_X = 24;

char the_map[DIM_Y][DIM_X + 1] =
{ "xxxxxxxxxxxxxxxxxxxxxxxx",
	"x                      x",
	"x                      x",
	"x                      x",
	"x                      x",
	"x                      x",
	"x                      x",
	"x                      x",
	"x                      x",
	"x                      x",
	"x                      x",
	"xxxxxxxxxxxxxxxxxxxxxxxx" };
