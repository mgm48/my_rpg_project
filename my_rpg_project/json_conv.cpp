#include "json_conv.h"
#include "location.h"
#include "item.h"

void to_json(json& j, const Item& I) {
    //j = nlohmann::json{ {"object", "Item"}, {"name", I.name}, {"type", I.type}, {"stat", I.stat} };
}
void from_json(const json& j, Item& I) {
    //I.name = j.at("name").get<std::string>();
   // I.type = j.at("type").get<Type>();
    //I.stat = j.at("stat").get<int>();
}

void to_json(json& j, const Location& L) {
    j = { {"object", "Location"}, {"name", L.Name}, {"encounter_rate", L._encounter_rate}, {"dim_y", L.DIM_Y }, {"dim_x", L.DIM_X }, { "enemies", L.enemies } };
}
void from_json(const json& j, Location& L) {
    L.Name = j.at("name").get<std::string>();
    L.DIM_Y = j.at("dim_y").get<int>();
    L.DIM_X = j.at("dim_x").get<int>();
    L._encounter_rate = j.at("encounter_rate").get<float>();
    L.enemies = j.at("enemies").get<std::vector<std::string> >();
}
