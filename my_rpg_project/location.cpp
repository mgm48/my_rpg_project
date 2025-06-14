#include "location.h"
#include "monster.h"
#include "files.h"
#include "logger.h"
#include <fstream>
 
Location::Location() { Name = "NULL"; DIM_Y = 1; DIM_X = 1; _encounter_rate = 0; }
Location::Location(std::string nam, int Y, int X)
	: Name(nam), DIM_Y(Y), DIM_X(X) { _encounter_rate = 0; } //pacifist location

Location::Location(std::string nam, int Y, int X, std::vector<std::string> e, float rate)
	: Name(nam), DIM_Y(Y), DIM_X(X), _encounter_rate(rate) {
	enemies = e;
}

const bool Location::IsConnectionPoint(int y, int x) {
	if (Connections[(t_enum)DIRECTION::SOUTH] && y == DIM_Y - 1 && x == DIM_X / 2) { return true; } //south is y:dim -1, x:dim/2
	else if (Connections[(t_enum)DIRECTION::WEST] && y == DIM_Y / 2 && x == 0) { return true; } //west is y:dim/2, x:0
	else if (Connections[(t_enum)DIRECTION::NORTH] && y == 0 && x == DIM_X / 2) { return true; } //north is y:0, x:dim/2
	else if (Connections[(t_enum)DIRECTION::EAST] && y == DIM_Y / 2 && x == DIM_X - 1) { return true; } //east is y:dim/2, x:dim-1
	return false;
}

DIRECTION Location::GetConnection(int y, int x) {
	if (Connections[(t_enum)DIRECTION::SOUTH] && y == DIM_Y - 1 && x == DIM_X / 2) { return DIRECTION::SOUTH; } //south is y:dim -1, x:dim/2
	else if (Connections[(t_enum)DIRECTION::WEST] && y == DIM_Y / 2 && x == 0) { return DIRECTION::WEST; } //west is y:dim/2, x:0
	else if (Connections[(t_enum)DIRECTION::NORTH] && y == 0 && x == DIM_X / 2) { return DIRECTION::NORTH; } //north is y:0, x:dim/2
	else if (Connections[(t_enum)DIRECTION::EAST] && y == DIM_Y / 2 && x == DIM_X - 1) { return DIRECTION::EAST; } //east is y:dim/2, x:dim-1
	return DIRECTION::NUM_DIR;
}

DIRECTION Location::op(const DIRECTION dir) {
	switch (dir) {
	case DIRECTION::SOUTH: return DIRECTION::NORTH;
	case DIRECTION::NORTH: return DIRECTION::SOUTH;
	case DIRECTION::EAST: return DIRECTION::WEST;
	case DIRECTION::WEST: return DIRECTION::EAST;
	default: return DIRECTION::NUM_DIR;
	}
}

bool Location::establish_connection(Location*& L, DIRECTION dir) {
	if (Connections[(t_enum)dir] || L->Connections[(t_enum)op(dir)]) { return false; }
	else {
		Connections[(t_enum)dir] = L;
		L->Connections[(t_enum)op(dir)] = this;
		return true;
	}
}
void Location::generate_enemy() {
	int r = rand() % enemies.size();
	//create monster

}

Location* Location::load_location(std::string nam) {
	print_log(MAIN_LOG, "Loading location " + nam);

	std::ifstream input(MAP_FILE);
	if (!input) {
		std::string e = "Error: File " + MAP_FILE + " failed to open.";
		print_log(MAIN_LOG, e.c_str());
		return nullptr;
	}

	json json_data = json::parse(input);
	//catch parse error
	for (auto& l : json_data["locations"]) {
		if (l.contains("object") && l["object"] == "Location" &&
			l.contains("name") && l["name"] == nam) {
			Location* L = new Location(l);
			print_log(MAIN_LOG, "Loaded location " + nam);
			return L;
		}
	}

	std::string e = "Error: Location " + nam + " failed to open.";
	print_log(MAIN_LOG, e.c_str());
	return nullptr;
}


