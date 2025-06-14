#pragma once

#include "typing.h"
#include "json_conv.h"
#include <string>

class Monster;
//enum class LOCTYPE{DUNGEON, VILLAGE};
enum class DIRECTION { SOUTH, WEST,NORTH,EAST,NUM_DIR };

class Location {
private: 
	std::vector<std::string> enemies;
	float _encounter_rate;
public:
	std::string Name;
	int DIM_Y;
	int DIM_X;
	Location* Connections[(t_enum)DIRECTION::NUM_DIR] = {nullptr,nullptr,nullptr,nullptr}; //S:0 W:1 N:2 E:3

	Location();
	Location(std::string nam, int Y, int X);
	Location(std::string nam, int Y, int X, std::vector<std::string> e, float rate);
	
	const bool IsConnectionPoint(int y, int x);
	DIRECTION GetConnection(int y, int x);


	static DIRECTION op(const DIRECTION dir);
	bool establish_connection(Location*& L, DIRECTION dir);
	
	void generate_enemy();

	static Location* load_location(std::string nam);

	friend void to_json(json& j, const Location& L);
	friend void from_json(const json& j, Location& L);
};