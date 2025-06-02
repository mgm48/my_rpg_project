#pragma once
#include <nlohmann/json.hpp>
#include "item.h"

// for convenience
using json = nlohmann::json;

//to serialize enums
//NLOHMANN_JSON_SERIALIZE_ENUM(TaskState, {
//    {TS_INVALID, nullptr},
//    {TS_STOPPED, "stopped"},
//    {TS_RUNNING, "running"},
//    {TS_COMPLETED, "completed"},
//    })

void to_json(json& j, const Item& I) {
    //j = nlohmann::json{ {"object", "Item"}, {"name", I.name}, {"type", I.type}, {"stat", I.stat} };
}
void from_json(const json& j, Item& I) {
    //I.name = j.at("name").get<std::string>();
   // I.type = j.at("type").get<Type>();
    //I.stat = j.at("stat").get<int>();
}