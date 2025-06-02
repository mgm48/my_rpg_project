#pragma once

#include "typing.h"
#include <string>
#include <iostream>

enum class LOCTYPE{DUNGEON, VILLAGE};
enum class DIRECTION { SOUTH, WEST,NORTH,EAST,NUM_DIR };

class Location {
public:
	std::string Name;
	int DIM_Y;
	int DIM_X;
	Location* Connections[(t_enum)DIRECTION::NUM_DIR] = {nullptr,nullptr,nullptr,nullptr}; //S:0 W:1 N:2 E:3

	Location(std::string nam = "Generic Location", int Y = 12, int X = 12) : Name(nam), DIM_Y(Y), DIM_X(X) {
	}

	const bool IsConnectionPoint(int y, int x){
		if (Connections[(t_enum)DIRECTION::SOUTH] && y == DIM_Y - 1 && x == DIM_X / 2) { return true; } //south is y:dim -1, x:dim/2
		else if (Connections[(t_enum)DIRECTION::WEST] && y == DIM_Y / 2 && x == 0) { return true; } //west is y:dim/2, x:0
		else if(Connections[(t_enum)DIRECTION::NORTH] && y == 0 && x == DIM_X / 2) { return true; } //north is y:0, x:dim/2
		else if (Connections[(t_enum)DIRECTION::EAST] && y == DIM_Y / 2 && x == DIM_X - 1) { return true; } //east is y:dim/2, x:dim-1
		return false;
	}

	DIRECTION GetConnection(int y, int x) {
		if (Connections[(t_enum)DIRECTION::SOUTH] && y == DIM_Y - 1 && x == DIM_X / 2) { return DIRECTION::SOUTH; } //south is y:dim -1, x:dim/2
		else if (Connections[(t_enum)DIRECTION::WEST] && y == DIM_Y / 2 && x == 0) { return DIRECTION::WEST; } //west is y:dim/2, x:0
		else if (Connections[(t_enum)DIRECTION::NORTH] && y == 0 && x == DIM_X / 2) { return DIRECTION::NORTH; } //north is y:0, x:dim/2
		else if (Connections[(t_enum)DIRECTION::EAST] && y == DIM_Y / 2 && x == DIM_X - 1) { return DIRECTION::EAST; } //east is y:dim/2, x:dim-1
		return DIRECTION::NUM_DIR;
	}


	static DIRECTION op(const DIRECTION dir) {
		switch (dir) {
			case DIRECTION::SOUTH: return DIRECTION::NORTH;
			case DIRECTION::NORTH: return DIRECTION::SOUTH;
			case DIRECTION::EAST: return DIRECTION::WEST;
			case DIRECTION::WEST: return DIRECTION::EAST;
			default: return DIRECTION::NUM_DIR;
		}
	}

	bool establish_connection(Location* &L, DIRECTION dir) {
		if (Connections[(t_enum)dir] || L->Connections[(t_enum)op(dir)]) { return false; }
		else {
			Connections[(t_enum)dir] = L;
			L->Connections[(t_enum)op(dir)] = this;
		}
	}
	

	void print_info() {
		std::cout << "Location: " << Name << "\n"
			<< "Dimension Y: " << DIM_Y << " Dimension X: " << DIM_X << "\n";
		for (auto i = 0; i < (t_enum)DIRECTION::NUM_DIR; i++) {
			if (Connections[i]) { std::cout << "Connection " << i << " to " << Connections[i]->Name << "\n"; }
		}
	}
};