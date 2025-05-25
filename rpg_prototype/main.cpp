#include "pch.h"
#include "random.h"
#include <iostream>
#include <string>

Player* p1 = nullptr;
Fightable* mon = nullptr;
int monsters_defeated = 0;

void create_monster(Fightable* tmp_mon, const Player* base_calc) {
	if (!base_calc) 
		return;
	
	if (tmp_mon) { delete tmp_mon; tmp_mon = nullptr; }

	int lowest_hp = base_calc->us.GetLevel() * 2;
	int max_hp = base_calc->us.GetLevel() * 8;
	int lowest_dam = base_calc->us.GetLevel();
	int max_dam = base_calc->us.GetLevel() * 2;

	tmp_mon = new Fightable(Random::NTK(lowest_hp, max_hp), lowest_dam, max_dam);

	while (abs(tmp_mon->ypos - p1->ypos) < 3 || abs(tmp_mon->ypos - p1->ypos) < 3) {
		tmp_mon->xpos = Random::NTK(1, DIM_X - 2);
		tmp_mon->ypos = Random::NTK(1, DIM_Y - 2);
	}

	mon = tmp_mon;
}




void show_map() {
		system("CLS");
	for (int i = 0; i < DIM_Y; i++) {
		for (int j = 0; j < DIM_X + 1; j++) {
			if (i == p1->ypos && j == p1->xpos) { std::cout << 'P'; }
			else if (i == mon->ypos && j == mon->xpos) { std::cout << 'M'; }
			else
				std::cout << the_map[i][j];
		}
		std::cout << '\n';
	}
}

void fight(Player& player1) {
	if (!mon) {
		return;
	}
	while (player1.IsAlive() && mon->IsAlive()) {
		system("CLS");
		// display fight interface
		std::cout
			<< "Player         vs       Monster\n"
			<< "hp: " << player1.us.GetCurrentHP() << '/' << player1.us.GetMaxHP() << "                  hp: " << mon->monster.HP.GetCurrent() << '/' << mon->monster.HP.GetMax() << '\n'
			<< "action(a:attack): ";
		char action = '1';
		while (action != 'a') {
			action = getchar();
		}
		mon->monster.HP.SubCur(player1.us.MeleeAttack());

		if (mon->IsAlive()) {
			player1.us.TakeDamage(mon->monster.Attack());
		}
	}

	if (player1.IsAlive()) {
		std::cout << "You Won vs the Monster!\n";
		std::cout << "xp gained: " << mon->xpworth << '\n';
		player1.us.GiveExp(mon->xpworth);
		monsters_defeated++;
		create_monster(mon, &player1);
	}
	else {
		std::cout << "You were defeated by the Monster!\n";
	}

	std::cin.ignore(100, '\n');
	std::cout << "\n Press Enter to Continue\n";
	char a = getchar();

}

void update() {
	if (mon->ypos == p1->ypos && mon->xpos == p1->xpos) { fight(*p1); }
}

bool move_player(Player &p, char c) {
	switch (c) {
		case 'w':
			if (p.ypos != 1) { p.prev_xpos = p.xpos; p.prev_ypos = p.ypos; p.ypos--; }
			else { std::cout << "\nTHERE IS A WALL THERE MY GUY"; }
			return true;
		case 's':
			if (p.ypos != DIM_Y - 2) { p.prev_xpos = p.xpos; p.prev_ypos = p.ypos; p.ypos++; } //else = wall
			else { std::cout << "\nTHERE IS A WALL THERE MY GUY"; }
			return true;
		case 'a':
			if (p.xpos != 1) { p.prev_xpos = p.xpos; p.prev_ypos = p.ypos; p.xpos--; }
			else { std::cout << "\nTHERE IS A WALL THERE MY GUY"; }
			return true;
		case 'd':
			if (p.xpos != DIM_X - 2) { p.prev_xpos = p.xpos; p.prev_ypos = p.ypos; p.xpos++; }
			else { std::cout << "\nTHERE IS A WALL THERE MY GUY"; }
			return true;
		default: 
			return false;
	}
	return false;
}


const char* char_description(int i) {
	switch (i) {
		case 1:
			return "just a little innocent cleric sir";
		case 2:
			return "A            Brave            Warrior.";
		case 3:
			return "a rascal, a scoundrel, a thief, THEEEE ROGUE";
		case 4:
			return "The prestigious, magnificent Wizard.";
		default:
			return "";
	}
}


//include game visual library to use
int main(int argc, char** argv) {

	bool runnin = true;
	std::cout << "\nHello! Welcome to this world! \n\n Choose who you want to be: \n"
		<< "1 = Cleric    2 = Warrior\n"
		<< "3 = Rogue     4 = Wizard\n";

	int choice;
	std::cin >> choice;
	while (choice > 4 || choice < 1 || !std::cin){
		std::cin.clear();    // Restore input stream to working state
		std::cin.ignore(100, '\n');    // Get rid of any garbage that user might have entered
		std::cout << "I'm sorry but that is not allowed :(. Choose again: ";
		std::cin >> choice;    // After cin is restored and any garbage in the stream has been cleared, store user input in number again
	}
	std::cout << "\nGreat! You will become " << char_description(choice) << '\n';

	switch (choice) {
	case 1: { p1 = new Player(new Cleric()); } break;
	case 2: { p1 = new Player(new Warrior()); } break;
	case 3: { p1 = new Player(new Rogue()); } break;
	case 4: { p1 = new Player(new Wizard()); } break;
	default:
		return -12;  // failed to make player character
	}
	create_monster(mon, p1);

	//Pause before starting
	char a = 'p';
	std::cout << "\nPress -m- to start playing: ";
	while (a != 'm') { a = getchar(); }
	
	show_map();

	bool p_move;
	for (;;) {
		p_move = false;
		std::cout << "\nmove(wasd): ";
		while (!p_move) {
			char c = getchar();
			p_move = move_player(*p1,c);
			/*switch (c) {
			case 'w':
				if (p1.ypos != 1) { p1.prev_xpos = p1.xpos; p1.prev_ypos = p1.ypos; p1.ypos--; }
				else { walled = true; }
				cont = true;
				break;
			case 's':
				if (p1.ypos != DIM_Y - 2) { p1.prev_xpos = p1.xpos; p1.prev_ypos = p1.ypos; p1.ypos++; }
				else { walled = true; }
				cont = true;
				break;
			case 'a':
				if (p1.xpos != 1) { p1.prev_xpos = p1.xpos; p1.prev_ypos = p1.ypos; p1.xpos--; }
				else { walled = true; }
				cont = true;
				break;
			case 'd':
				if (p1.xpos != DIM_X - 2) { p1.prev_xpos = p1.xpos; p1.prev_ypos = p1.ypos; p1.xpos++; }
				else { walled = true; }
				cont = true;
				break;
			default:
				break;
			}*/
			std::cin.clear(); //to clear the input stream
		}
		update();

		if (p1->IsAlive()) {
			show_map();
		}
		else {
			break;
		}

		//std::cout << "\nPlayer Pos: " << p1->ypos << ", " << p1->xpos << "\n";
		//std::cout << "\nPlayer Prev Pos: " << p1->prev_ypos << ", " << p1->prev_xpos << "\n";
	}
	std::cout << "Total Monsters Defeated: " << monsters_defeated << '\n';
	char c = getchar();
	return EXIT_SUCCESS;
}