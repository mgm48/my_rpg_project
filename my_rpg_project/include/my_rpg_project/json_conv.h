#pragma once
#include <nlohmann/json.hpp>

class Location;
class Item;

// for convenience
using json = nlohmann::json;

//to serialize enums
//NLOHMANN_JSON_SERIALIZE_ENUM(TaskState, {
//    {TS_INVALID, nullptr},
//    {TS_STOPPED, "stopped"},
//    {TS_RUNNING, "running"},
//    {TS_COMPLETED, "completed"},
//    })

void to_json(json& j, const Item& I);
void from_json(const json& j, Item& I);

void to_json(json& j, const Location& L);
void from_json(const json& j, Location& L);
