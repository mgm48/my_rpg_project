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

struct Fightable {
	Fightable(int hp, int min, int max) : monster(hp, min, max) {
		xpworth = (hp + min + max) * 2;
	}
	bool IsAlive() { return (monster.HP.GetCurrent() > 0); }
	Monster monster;
	int xpos = 3;
	int ypos = 3;
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
