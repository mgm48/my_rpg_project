#include "pch.h"
#include "random.h"
#include <iostream>
#include <string>

Player* p1 = nullptr;
Fightable* mon = nullptr;
int monsters_defeated = 0;

static void print_equipped_weapon(const Weapon* weapon) {
	switch (weapon->Slot) {
	case WEAPONSLOT::MELEE:{ std::cout << "MELEE: "; break; }
	case WEAPONSLOT::RANGED: { std::cout << "RANGED: "; break; }
	default: break; }
	std::cout << weapon->Name << " DMG(" << weapon->MinDamage << " - " << weapon->MaxDamage << ")";
	if (weapon->Stats.any()) { std::cout << " " << weapon->Stats; }

}
//enum class ARMORSLOT { HEAD, CHEST, LEGS, FEET, HANDS, RING1, RING2, NECK, NUM_SLOTS };
static void print_equipped_armor(const Armor* armor) {
	switch (armor->Slot) {
	case ARMORSLOT::HEAD: { std::cout << "HEAD: "; break; }
	case ARMORSLOT::CHEST: { std::cout << "CHEST: "; break; }
	case ARMORSLOT::LEGS: { std::cout << "LEGS: "; break; }
	case ARMORSLOT::FEET: { std::cout << "FEET: "; break; }
	case ARMORSLOT::HANDS: { std::cout << "HANDS: "; break; }
	case ARMORSLOT::RING1: { std::cout << "RING1: "; break; }
	case ARMORSLOT::RING2: { std::cout << "RING2: "; break; }
	case ARMORSLOT::NECK: { std::cout << "NECK: "; break; }
	default: break; }
	std::cout << armor->Name;
	if (armor->Stats.any()) { std::cout << " " << armor->Stats; }
}

static void print_item(Item* it) {
	if (ItemManager::IsItemArmor(it)) {
		const Armor* armor = dynamic_cast<const Armor*>(it->GetData());
		std::cout << armor->Name << ". " << armor->Stats;
	}
	else if (ItemManager::IsItemWeapon(it)) {
		const Weapon* weapon = dynamic_cast<const Weapon*>(it->GetData());
		std::cout << weapon->Name << ". " << weapon->Stats << ". DMG: " << weapon->MinDamage << " - " << weapon->MaxDamage;
	}
	else if (ItemManager::IsItemPotion(it)) {
		const Potion* pot = dynamic_cast<const Potion*>(it->GetData());
		std::cout << pot->Name << ". Heal:" << pot->HealAmount << ". Quantity: " << pot->Quantity;
	}
	else {
		std::cout << "Something weird happened, item error.";
	}
}

void display_character_sheet() {
	ItemManager::Equip(ItemManager::CreateArmor("Helmet", CoreStats(2,0,0,0,0), ARMORSLOT::HEAD), &(p1->us));
	ItemManager::Equip(ItemManager::CreateArmor("Legs", CoreStats(-3, 0, 0, 5, 0), ARMORSLOT::LEGS), &(p1->us));
	ItemManager::Equip(ItemManager::CreateWeapon("Dagger", CoreStats(0, 0, 0, 0, 0), WEAPONSLOT::MELEE,1,3), &(p1->us));
	system("CLS");
	std::cout
		<< "Your Character\n"
		<< "-----------------\n"
		<< "Lvl " << p1->us.GetLevel() << " " << p1->us.GetClass() << "\n"
		<< "Hit Points: " << p1->us.GetCurrentHP() << "/" << p1->us.GetMaxHP() << '\n';
	if(p1->us.IsMagicUser()){ std::cout << "Mana: " << p1->us.GetCurrentMP() << "/" << p1->us.GetMaxMP() << '\n';}
	std::cout
		<< "STR: " << p1->us.GetTotalStrength() << " INT: " << p1->us.GetTotalIntellect() << " AGI: " << p1->us.GetTotalAgility() << '\n'
		<< "ARMOR: " << p1->us.GetTotalArmor() << "  RES: " << p1->us.GetTotalElementRes() << '\n'
		<< "\nEquipped Gear\n";
	
	auto i = 0;
	for (i = 0; i < (unsigned long long)ARMORSLOT::NUM_SLOTS; i++) {
		if (p1->us.GetEquippedArmorAt(i)) { print_equipped_armor(p1->us.GetEquippedArmorAt(i)); std::cout << "\n"; }
	}
	for (i = 0; i < (unsigned long long)WEAPONSLOT::NUM_SLOTS; i++) {
		if (p1->us.GetEquippedWeaponAt(i)) { print_equipped_weapon(p1->us.GetEquippedWeaponAt(i)); std::cout << "\n"; }
	}

	/*if (p1->us.GetEquippedWeaponAt((unsigned long long)WEAPONSLOT::MELEE)) {
		std::string weapon_name = p1->us.GetEquippedWeaponAt((unsigned long long)WEAPONSLOT::MELEE)->Name;
		std::cout << "MELEE: " << weapon_name << "d(" << p1->us.GetEquippedWeaponAt((unsigned long long)WEAPONSLOT::MELEE)->MinDamage << '-' << p1->us.GetEquippedWeaponAt((unsigned long long)WEAPONSLOT::MELEE)->MaxDamage << ")\n";
	}
	if (p1->us.GetEquippedWeaponAt((unsigned long long)WEAPONSLOT::RANGED)) {
		std::string weapon_name = p1->us.GetEquippedWeaponAt((unsigned long long)WEAPONSLOT::RANGED)->Name;
		std::cout << "RANGED: " << weapon_name << "d(" << p1->us.GetEquippedWeaponAt((unsigned long long)WEAPONSLOT::RANGED)->MinDamage << '-' << p1->us.GetEquippedWeaponAt((unsigned long long)WEAPONSLOT::RANGED)->MaxDamage << ")\n";
	}
	if (p1->us.GetEquippedArmorAt((unsigned long long)ARMORSLOT::HEAD)) {
		std::string armor_name = p1->us.GetEquippedArmorAt((unsigned long long)ARMORSLOT::HEAD)->Name;
		std::cout << "HEAD: " << armor_name << '\n';
	}
	if (p1->us.GetEquippedArmorAt((unsigned long long)ARMORSLOT::NECK)) {
		std::string armor_name = p1->us.GetEquippedArmorAt((unsigned long long)ARMORSLOT::NECK)->Name;
		std::cout << "NECK: " << armor_name << '\n';
	}
	if (p1->us.GetEquippedArmorAt((unsigned long long)ARMORSLOT::CHEST)) {
		std::string armor_name = p1->us.GetEquippedArmorAt((unsigned long long)ARMORSLOT::CHEST)->Name;
		std::cout << "CHEST: " << armor_name << '\n';
	}
	if (p1->us.GetEquippedArmorAt((unsigned long long)ARMORSLOT::HANDS)) {
		std::string armor_name = p1->us.GetEquippedArmorAt((unsigned long long)ARMORSLOT::HANDS)->Name;
		std::cout << "HANDS: " << armor_name << '\n';
	}
	if (p1->us.GetEquippedArmorAt((unsigned long long)ARMORSLOT::RING1)) {
		std::string armor_name = p1->us.GetEquippedArmorAt((unsigned long long)ARMORSLOT::RING1)->Name;
		std::cout << "RING1: " << armor_name << '\n';
	}
	if (p1->us.GetEquippedArmorAt((unsigned long long)ARMORSLOT::RING2)) {
		std::string armor_name = p1->us.GetEquippedArmorAt((unsigned long long)ARMORSLOT::RING2)->Name;
		std::cout << "RING2: " << armor_name << '\n';
	}
	if (p1->us.GetEquippedArmorAt((unsigned long long)ARMORSLOT::LEGS)) {
		std::string armor_name = p1->us.GetEquippedArmorAt((unsigned long long)ARMORSLOT::LEGS)->Name;
		std::cout << "LEGS: " << armor_name << '\n';
	}
	if (p1->us.GetEquippedArmorAt((unsigned long long)ARMORSLOT::FEET)) {
		std::string armor_name = p1->us.GetEquippedArmorAt((unsigned long long)ARMORSLOT::FEET)->Name;
		std::cout << "FEET: " << armor_name << '\n';
	}*/

	std::cin.ignore(100, '\n');
	std::cout << "\n press Enter to continue\n";
	char c = getchar();
}

bool open_inventory() {
	bool close = false;
	int selected = 0;

	while (!close) {
		system("CLS");
		auto list_of_items = p1->us.GetBackpackList();
		int num_items = list_of_items.size();
		if (num_items == 0) { selected = 0; }
		else if (selected > num_items - 1 ) { selected = num_items - 1; }

		std::cout
			<< "CURRENT INVENTORY\n"
			<< "-----------------\n\n";
		int backpack_count = 0;
		for (const auto& item : list_of_items) {
			if (selected == backpack_count) { std::cout << "> "; print_item(item); }
			else { std::cout << "  " << item->GetData()->Name; }
			std::cout << '\n';
			backpack_count++;
		}
		std::cin.clear();
		std::cin.ignore(100, '\n');
		std::cout << "\nAction -> Close(x); Up(w); Down(s); Use/Equip Selected(e); Delete Selected(d); -> ";
		char c = getchar();
		switch (c) {
			case 'x':
				close = true;
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
					ItemManager::Use(list_of_items[selected], &(p1->us));
				else if (ItemManager::IsItemEquippable(list_of_items[selected]))
					ItemManager::Equip(list_of_items[selected], &(p1->us));
				break;
			case 'd':
				if (list_of_items.empty())
					continue;
				ItemManager::DiscardFromBackpack(list_of_items[selected], &(p1->us));
				break;
			default:
				break;
		}
	}
	return close;
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
		tmp_mon->xpos = Random::NTK(1, DIM_X - 2); //DIM - 1 es la barrera
		tmp_mon->ypos = Random::NTK(1, DIM_Y - 2);
	} while (abs(tmp_mon->xpos - p1->xpos) < 3 || abs(tmp_mon->ypos - p1->ypos) < 3);

	mon = tmp_mon;
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
			int damage_to_take = player1.us.Defend(mon->monster.Attack());
			player1.us.TakeDamage(damage_to_take);
		}
	}

	if (player1.IsAlive()) {
		std::cout << "You Won vs the Monster!\n";
		//exp
		std::cout << "xp gained: " << mon->xpworth << "\n\n";
		player1.us.GiveExp(mon->xpworth);

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
	std::cout << "\n Press Enter to Continue\n";
	char a = getchar();

}

bool move_player(Player& p, char input) {
	if (input == 'w') {
		if (p.ypos != 1) { p.prev_xpos = p.xpos; p.prev_ypos = p.ypos; p.ypos--; }
		else { std::cout << "\nTHERE IS A WALL THERE MY GUY"; }
		return true;
	}
	else if (input == 's') {
		if (p.ypos != DIM_Y - 2) { p.prev_xpos = p.xpos; p.prev_ypos = p.ypos; p.ypos++; } //else = wall
		else { std::cout << "\nTHERE IS A WALL THERE MY GUY"; }
		return true;
	}
	else if (input == 'a') {
		if (p.xpos != 1) { p.prev_xpos = p.xpos; p.prev_ypos = p.ypos; p.xpos--; }
		else { std::cout << "\nTHERE IS A WALL THERE MY GUY"; }
		return true;
	}
	else if (input == 'd') {
		if (p.xpos != DIM_X - 2) { p.prev_xpos = p.xpos; p.prev_ypos = p.ypos; p.xpos++; }
		else { std::cout << "\nTHERE IS A WALL THERE MY GUY"; }
		return true;
	}
	else { return false; }
}

void update() { if (mon->ypos == p1->ypos && mon->xpos == p1->xpos) { fight(*p1); } }

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

	//drop_test(10);

	//Pause before starting
	char a = 'p';
	std::cout << "\nPress -a- to start playing: ";
	while (a != 'a') { a = getchar(); }
	
	show_map();

	bool action;
	char input;
	for (;;) {
		action = false;
		std::cout << "\n Action -> Move(wasd); CharacterSheet(e); Inventory(i); Respawn Monster(m); Generate Items(g); Exit(x); -> ";
		while (!action) {
			input = getchar();
			switch (input) {
				case 'w': case 'a': case 's': case 'd':
					action = move_player(*p1, input);
					break;
				case 'e':
					display_character_sheet();
					action = true;
					break;
				case 'i':
					action = open_inventory();
					break;
				case 'm':
					create_monster(mon, p1);
					action = true;
					break;
				case 'g':
					drop_test(5);
					action = true;
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

