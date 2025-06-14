#pragma once
#include "my_rpg_project/monster.h"
#include "my_rpg_project/playercharacter.h"
#include "my_rpg_project/playableclasses.h"
#include "my_rpg_project/random.h"


struct Player {
	Player(PlayerCharacterDelegate* p) : us(p) {};
	Player() = delete;
	bool IsAlive() { return us.GetCurrentHP() > 0; }
	PlayerCharacter us;
	int prev_ypos = 1;
	int prev_xpos = 10;
	int ypos = 1;
	int xpos = 10;
};

struct Fightable {
	Fightable(int hp, int min, int max) : monster(hp, min, max, (hp + min + max) * 2) {
	}
	bool IsAlive() { return (monster.HP.GetCurrent() > 0); }
	Monster monster;
	int xpos = 1;
	int ypos = 1;
	Fightable() = delete;
};


