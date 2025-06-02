#include "pch.h"

//things in testing 
#include "my_rpg_project/printer.h"
#include "my_rpg_project/constants.h"
#include "my_rpg_project/location.h"
#include <iostream>
#include <string>

Player* p1 = nullptr;
Fightable* mon = nullptr;
Location* loc = nullptr;
int monsters_defeated = 0;


void display_character_sheet() {
	print_character_sheet(p1);

	std::cin.ignore(100, '\n');
	std::cout << "\n Press Enter to close the sheet.\n";
	char c = getchar();
}

bool open_inventory(bool in_combat = false) {
	bool close = false;
	bool action_used = false;
	int selected = 0;

	while (!close || !action_used) {
		system("CLS");
		auto list_of_items = p1->us.GetBackpackList();	int num_items = (int) list_of_items.size();
		if (num_items == 0) { selected = 0; }
		else if (selected > num_items - 1 ) { selected = num_items - 1; }

		std::cout
			<< "CURRENT INVENTORY\n"
			<< "-----------------\n\n";
		int backpack_count = 0;
		for (const auto& item : list_of_items) {
			if (selected == backpack_count) { std::cout << "> "; print_item(item); std::cout << '\n'; }
			else { std::cout << "  " << item->GetData()->Name << '\n'; }
			backpack_count++;
		}
		std::cin.clear();
		std::cin.ignore(100, '\n');
		std::cout << "\nAction -> (x)Close; (w)Up; (s)Down; (e)Use/Equip Selected;" 
			<< ((!in_combat) ? " (d)Delete Selected;" : "") << " -> ";
		char c = getchar();
		switch (c) {
			case 'x':
				close = true;
				return action_used;
				break;
			case 'w':
				if (selected > 0 && num_items > 1) { selected--; }
				else { selected = 0; }
				break;
			case 's':
				if (selected < num_items - 1 && num_items > 1) { selected++; }
				else { selected = (num_items > 1) ? (num_items - 1) : 0 ; }
				break;
			case 'e':
				if (list_of_items.empty())
					continue;
				if (ItemManager::IsItemUseable(list_of_items[selected]))
					action_used = ItemManager::Use(list_of_items[selected], &(p1->us));
				else if (ItemManager::IsItemEquippable(list_of_items[selected]))
					action_used = ItemManager::Equip(list_of_items[selected], &(p1->us));
				break;
			case 'd':
				if (!in_combat) {
					if (list_of_items.empty())
						continue;
					action_used = ItemManager::DiscardFromBackpack(list_of_items[selected], &(p1->us));
				}
				break;
			default:
				break;
		}
		if (in_combat) { close = action_used; }
	}
	return action_used;
}
//
//bool combat_inventory() {
//	bool close = false;
//	bool action_used = false;
//	int selected = 0;
//	while (!close && !action_used) {
//		auto list_of_items = p1->us.GetBackpackList(); 	int num_items = (int)list_of_items.size();
//		if (num_items == 0) { selected = 0; }
//		else if (selected > num_items - 1) { selected = num_items - 1; }
//		std::cout
//			<< "CURRENT INVENTORY\n"
//			<< "-----------------\n\n";
//		int backpack_count = 0;
//		for (const auto& item : list_of_items) {
//			if (selected == backpack_count) { std::cout << "> "; print_item(item); }
//			else { std::cout << "  " << item->GetData()->Name; }
//			std::cout << '\n';
//			backpack_count++;
//		}
//		std::cin.clear();
//		std::cin.ignore(100, '\n');
//		std::cout << "\nAction -> (x)Close; (w)Up; (s)Down; (e)Use/Equip Selected; -> ";
//		char c = getchar();
//		switch (c) {
//		case 'x':
//			close = true;
//			break;
//		case 'w':
//			if (selected > 0 && num_items > 1) { selected--; }
//			else { selected = 0; }
//			break;
//		case 's':
//			if (selected < num_items - 1 && num_items > 1) { selected++; }
//			else { selected = (num_items > 1) ? (num_items - 1) : 0; }
//			break;
//		case 'e':
//			if (list_of_items.empty())
//				continue;
//			if (ItemManager::IsItemUseable(list_of_items[selected]))
//				action_used = ItemManager::Use(list_of_items[selected], &(p1->us));
//			else if (ItemManager::IsItemEquippable(list_of_items[selected]))
//				action_used = ItemManager::Equip(list_of_items[selected], &(p1->us));
//			break;
//		default:
//			break;
//		}
//
//	}
//	return action_used;
//}

bool ability_selection(){
	bool close = false;
	bool action_used = false;
	const char* fail_msg = "";
	int selected = 0;

	while (!close && !action_used) {
		system("CLS");
		auto current_abilities = p1->us.GetAbilityList();;	int num_items = (int)current_abilities.size();
		if (num_items == 0) { selected = 0; }
		else if (selected > num_items - 1) { selected = num_items - 1; }

		std::cout
			<< "CURRENT ABILITIES\n\n";
		int abilities_count = 0;
		for (const auto& abil : current_abilities) {
			std::cout << ((selected == abilities_count) ? "> " : "  ");
			std::cout << abil->GetName() << '\n'; //todo print cooldown, cost
			abilities_count++;
		}
		std::cin.clear();
		std::cin.ignore(100, '\n');
		std::cout << fail_msg;
		fail_msg = "";
		std::cout << "\nAction -> (x)Close; (w)Up; (s)Down; (e)Use Selected;" << " -> ";
		char c = getchar();
		switch (c) {
		case 'x':
			close = true;
			return action_used;
			break;
		case 'w':
			if (selected > 0 && num_items > 1) { selected--; }
			else { selected = 0; }
			break;
		case 's':
			if (selected < num_items - 1 && num_items > 1) { selected++; }
			else { selected = (num_items > 1) ? (num_items - 1) : 0; }
			break;
		case 'e':
			if (current_abilities[selected]->CooldownLeft == 0) {
				if (current_abilities[selected]->GetTarget() == ABILITYTARGET::ENEMY) {
					int total_damage = 0;
					total_damage += current_abilities[selected]->GetHPEffect();
					switch (current_abilities[selected]->GetScaler()) {
					case ABILITYSCALER::STR:
						total_damage += (int)(p1->us.GetTotalStrength() / 2.f);
						break;
					case ABILITYSCALER::INT:
						total_damage += (int)(p1->us.GetTotalIntellect() / 2.f);
						break;
					case ABILITYSCALER::AGI:
						total_damage += (int)(p1->us.GetTotalAgility() / 2.f);
						break;
					default:
						break;
					}
					mon->monster.HP.SubCur(total_damage);
				}
				else {  // itsa heal (probably)
					int total_heal = 0;
					total_heal += current_abilities[selected]->GetHPEffect();
					switch (current_abilities[selected]->GetScaler()) {
					case ABILITYSCALER::STR:
						total_heal += (int)(p1->us.GetTotalStrength() / 2.f);
						break;
					case ABILITYSCALER::INT:
						total_heal += (int)(p1->us.GetTotalIntellect() / 2.f);
						break;
					case ABILITYSCALER::AGI:
						total_heal += (int)(p1->us.GetTotalAgility() / 2.f);
						break;
					default:
						break;
					}
					p1->us.Heal(total_heal);
				}
				current_abilities[selected]->PutOnCooldown();
			}
			else { fail_msg = "\nAbility couldn't be used.\n"; }
			
			break;
		default:
			break;
		}
	}
	return action_used;
}

Item* drop_random_item() {
	int seed = Random::NTK(1, 100);
	std::string name = "";
	CoreStats stats = CoreStats();

	//random buffs
	int enchant = Random::NTK(0, 10);
	if (enchant > 9) { name.append("+2 "); stats.add(2, 2, 2); }
	else if (enchant > 7) { name.append("+1 "); stats.add(1, 1, 1); }


	if (seed < 48) { //Armor
		ARMORSLOT aslot;
		if (seed < 6) { name.append("Helmet"); stats.add(0, 0, 0, 1, 0); aslot = ARMORSLOT::HEAD; }
		else if (seed < 12) { name.append("Breastplate"); stats.add(0, 0, 0, 2, 1); aslot = ARMORSLOT::CHEST; }
		else if (seed < 18) { name.append("Leg Guards"); stats.add(0, 0, 0, 1, 1); aslot = ARMORSLOT::LEGS; }
		else if (seed < 24) { name.append("Boots"); stats.add(0, 0, 0, 0, 1); aslot = ARMORSLOT::FEET; }
		else if (seed < 30) { name.append("Gloves"); stats.add(0, 0, 1, 1, 0); aslot = ARMORSLOT::HANDS; }
		else if (seed < 30) { name.append("Gloves"); stats.add(0, 0, 1, 1, 0); aslot = ARMORSLOT::HANDS; }
		else if (seed < 36) { name.append("Brilliant Ring"); stats.add(1, 1, 1, 0, 0); aslot = ARMORSLOT::RING1; }
		else if (seed < 42) { name.append("Small Ring"); stats.add(1, 1, 1, 0, 0); aslot = ARMORSLOT::RING2; }
		else { name.append("Neck Guard"); stats.add(0, 0, 0, 1, 2); aslot = ARMORSLOT::NECK; }
		return ItemManager::CreateArmor(name, stats, aslot);
	}
	else if (seed < 60) { //Weapon
		WEAPONSLOT wslot; t_dmg min, max;
		if (seed < 52) { name.append("Short Sword"); wslot = WEAPONSLOT::MELEE; min = 2; max = 3; }
		else if (seed < 55) { name.append("Short Bow"); wslot = WEAPONSLOT::RANGED; min = 2; max = 3; }
		else if (seed < 58) { name.append("Great Sword"); wslot = WEAPONSLOT::MELEE; min = 3; max = 6; }
		else { name.append("Archer's Bow"); wslot = WEAPONSLOT::RANGED; min = 2; max = 8; }
		return ItemManager::CreateWeapon(name, stats, wslot, min, max);
	}
	else if (seed < 91) { //Potion
		return ItemManager::CreatePotion("Potion Of Healing", Random::NTK(2, 5), Random::NTK(1, 6));
	}
	return nullptr;
}

void drop_test(int n) {
	std::cout << "\n";
	for (int i = 0; i < n; i++) {
		Item* it = drop_random_item();
		if (it) {
			print_item(it); std::cout << "\n";
			ItemManager::MoveToBackpack(it, &(p1->us));
		}
		else { std::cout << "No luck!\n"; }
	}
	std::cin.clear();
	std::cin.ignore(100, '\n');
	std::cout << "\nPress Enter to Continue\n";
	char a = getchar();
}

void create_monster(Fightable* tmp_mon, const Player* base_calc) {
	if (!base_calc)
		return;

	if (tmp_mon) { delete tmp_mon; tmp_mon = nullptr; }

	int lowest_hp = base_calc->us.GetLevel() * 2;
	int max_hp = base_calc->us.GetLevel() * 8;
	int lowest_dam = base_calc->us.GetLevel();
	int max_dam = base_calc->us.GetLevel() * 2;

	tmp_mon = new Fightable(Random::NTK(lowest_hp, max_hp), lowest_dam, max_dam);

	do {
		tmp_mon->xpos = Random::NTK(1, loc->DIM_X - 2); //DIM - 1 es la barrera
		tmp_mon->ypos = Random::NTK(1, loc->DIM_Y - 2);
	} while (abs(tmp_mon->xpos - p1->xpos) < 3 || abs(tmp_mon->ypos - p1->ypos) < 3);

	mon = tmp_mon;
}

void fight(Player& player1) {
	if (!mon) { return; }

	enum class FightOptions { NONE, ATTACK, INVENTORY, ABILITY };
	int turn = 1;
	t_dmg last_mon_attack = -1;
	t_dmg last_player_attack = -1;
	FightOptions last_action = FightOptions::NONE;

	while (player1.IsAlive() && mon->IsAlive()) {
		FightOptions action_taken = FightOptions::NONE;
		char action = '1';
		while (action_taken == FightOptions::NONE) {
			// display fight interface
			system("CLS");
			std::cout
				<< "Player         vs       Monster                      " << "Turn " << turn << ".\n"
				<< "hp: " << player1.us.GetCurrentHP() << '/' << player1.us.GetMaxHP() << "               hp: " << mon->monster.HP.GetCurrent() << '/' << mon->monster.HP.GetMax() << "\n";
			
			if(turn > 1){ 
				if (last_action == FightOptions::ATTACK) { std::cout << "\nLast Player Attack: Dealt " << last_player_attack << " DMG."; }
				else if (last_action == FightOptions::INVENTORY) { std::cout << "\nLast Player Action: Used or Equipped an item."; }
				else if (last_action == FightOptions::ABILITY) { std::cout << "\nLast Player Action: Used an Ability."; } //todo obtain details about ability
				std::cout << "\nLast Monster Attack: " << last_mon_attack <<" DMG.";
			}
			std::cout << "\n\nAction -> ViewCharacter(e); Attack(a); Inventory(i); Abilities(b); -> ";
			action = getchar();
			t_dmg player_attack;
			switch (action) {
			case 'e':
				display_character_sheet();
				break;
			case 'a':
				action_taken = FightOptions::ATTACK;
				player_attack = player1.us.MeleeAttack();
				mon->monster.HP.SubCur(player_attack);
				last_player_attack = player_attack;
				break;
			case 'i':
				action_taken = (open_inventory(true)) ? FightOptions::INVENTORY : FightOptions::NONE; //if taken an action in inventory
				break;
			case 'b':
				action_taken = (ability_selection()) ? FightOptions::ABILITY : FightOptions::NONE;
				break;
			default:
				break;
			}
		}
		last_action = action_taken;
		if (mon->IsAlive()) {
			t_dmg damage_to_take = player1.us.Defend(mon->monster.Attack());
			player1.us.TakeDamage(damage_to_take);
			last_mon_attack = damage_to_take;
		}
		turn++;
	}

	if (player1.IsAlive()) {
		std::cout << "You Won vs the Monster!\n";
		//exp
		std::cout << "Gained: " << mon->xpworth << " exp\n";
		if (player1.us.GiveExp(mon->xpworth)) {
			std::cout << "Leveled up! New Lvl = " << player1.us.GetLevel() << "\n";
		}

		//loot item
		Item* loot = drop_random_item();
		if (loot) {
			std::cout << "Lucky! obtained " << loot->GetData()->Name << " as loot\n";
			if (ItemManager::MoveToBackpack(loot, &player1.us)) {
				std::cout << "the item was stored in your inventory\n";
			}
		}
		//get ready for the next round
		monsters_defeated++;
		create_monster(mon, &player1);
	}
	else {
		std::cout << "You were defeated by the Monster!\n";
	}

	std::cin.ignore(100, '\n');
	std::cout << " Press Enter to Continue\n";
	char a = getchar();

}

//todo make this two functions where one makes sure movement valid for an entity and returns enum move dir (pos updated on update)
bool move_player(Player &p, char input) {
	if (input == 'w') {
		if (p.ypos != 1 || loc->IsConnectionPoint(p.ypos - 1,p.xpos)) { p.prev_xpos = p.xpos; p.prev_ypos = p.ypos; p.ypos--; }
		return true;
	}
	else if (input == 's') {
		if (p.ypos != loc->DIM_Y - 2 || loc->IsConnectionPoint(p.ypos + 1, p.xpos)) { p.prev_xpos = p.xpos; p.prev_ypos = p.ypos; p.ypos++; } //else = wall
		return true;
	}
	else if (input == 'a') {
		if (p.xpos != 1 || loc->IsConnectionPoint(p.ypos, p.xpos - 1)) { p.prev_xpos = p.xpos; p.prev_ypos = p.ypos; p.xpos--; }
		return true;
	}
	else if (input == 'd') {
		if (p.xpos != loc->DIM_X - 2 || loc->IsConnectionPoint(p.ypos, p.xpos + 1)) { p.prev_xpos = p.xpos; p.prev_ypos = p.ypos; p.xpos++; }
		return true;
	}
	else { return false; }
}

bool move_locations(Player &p,Location* &new_loc,const DIRECTION dir) {
	if (!new_loc || new_loc->Connections[(t_enum)dir] != loc) return false;

	switch (dir) {
		case DIRECTION::NORTH: //entering north
			p.prev_xpos = p.xpos; p.prev_ypos = p.ypos;
			p.xpos = new_loc->DIM_X / 2; p.ypos = 1;
			break;
		case DIRECTION::SOUTH: //entering south
			p.prev_xpos = p.xpos; p.prev_ypos = p.ypos;
			p.xpos = new_loc->DIM_X / 2; p.ypos = new_loc->DIM_Y - 2;
			break;
		case DIRECTION::EAST:  //entering east
			p.prev_xpos = p.xpos; p.prev_ypos = p.ypos;
			p.xpos = new_loc->DIM_X - 2; p.ypos = new_loc->DIM_Y / 2;
			break;
		case DIRECTION::WEST:  //entering west
			p.prev_xpos = p.xpos; p.prev_ypos = p.ypos;
			p.xpos = 1; p.ypos = new_loc->DIM_Y / 2;
			break;
		default:
			break;
	}
	loc = new_loc;
	return true;
}

void update() { 
	if (mon->ypos == p1->ypos && mon->xpos == p1->xpos) { fight(*p1); } 
	else if (loc->IsConnectionPoint(p1->ypos, p1->xpos)) {
		DIRECTION dir = loc->GetConnection(p1->ypos, p1->xpos);
		move_locations(*p1, loc->Connections[(t_enum)dir], Location::op(dir));
	}
}

void show_map() { //use location, player and monsters
	system("CLS");
	std::cout << loc->Name << "\n";
	for (int y = 0; y < loc->DIM_Y; y++) {
		for (int x = 0; x < loc->DIM_X; x++) {
			if (y == 0 || y == loc->DIM_Y - 1 || x == 0 || x == loc->DIM_X - 1) {
				if (loc->IsConnectionPoint(y,x)) { 
					std::cout << 'O'; 
				}
				else std::cout << 'x';
			}
			else if (y == p1->ypos && x == p1->xpos) { std::cout << 'P'; }
			else if (y == mon->ypos && x == mon->xpos) { std::cout << 'M'; }
			else
				std::cout << ' ';
		}
		std::cout << '\n';
	}
}


//include game visual library to use
int main(int argc, char** argv) {

	//print_log(MAIN_LOG, "hola");
	loc = new Location("Valley", 12, 30);
	Location* l2 = new Location("Village", 10, 17);
	loc->establish_connection(l2, DIRECTION::WEST);


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
	std::cout << "\nGreat! You will become " << descriptions[choice - 1] << '\n';

	switch (choice) {
	case 1: { p1 = new Player(new Cleric()); } break;
	case 2: { p1 = new Player(new Warrior()); } break;
	case 3: { p1 = new Player(new Rogue()); } break;
	case 4: { p1 = new Player(new Wizard()); } break;
	default:
		return -12;  // failed to make player character
	}
	create_monster(mon, p1);

	//random starting drops

	ItemManager::MoveToBackpack(drop_random_item(), &(p1->us));
	ItemManager::MoveToBackpack(drop_random_item(), &(p1->us));


	//Pause before starting
	std::cin.ignore(100, '\n');
	std::cout << " Press Enter to Continue\n";
	char a = getchar();
	
	show_map();
	enum class Actions { NONE, MOVE, INVENTORY, MONSTER, GOD_MODE };
	
	char input;
	for (;;) {
		Actions action = Actions::NONE;
		while (action == Actions::NONE) {
			show_map();
			std::cout << "\n Action -> Move(wasd); CharacterSheet(e); Inventory(i); Respawn Monster(m); Generate Items(g); Exit(x); -> ";
			input = getchar();
			switch (input) {
				case 'w': case 'a': case 's': case 'd':
					move_player(*p1, input); action = Actions::MOVE;
					break;
				case 'e':
					display_character_sheet(); 
					break;
				case 'i':
					action = (open_inventory()) ? Actions::INVENTORY : Actions::NONE;
					break;
				case 'm':
					create_monster(mon, p1);
					action = Actions::MONSTER;
					break;
				case 'g':
					drop_test(5);
					action = Actions::GOD_MODE;
					break;
				case 'x':
					return EXIT_SUCCESS;
				default:
					break;
			}
			std::cin.clear(); //to clear the input stream
		}

		update();

		if (p1->IsAlive()) {
			show_map();
		}
		else {
			break;
		}

		
	}
	std::cout << "Total Monsters Defeated: " << monsters_defeated << '\n';
	char c = getchar();
	return EXIT_SUCCESS;
}

