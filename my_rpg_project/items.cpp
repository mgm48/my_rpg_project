#include "items.h"

// don't change this, only the EquipmentDelegate constructor should touch this
static std::uint32_t EQUIPMENTUNIQUEIDITERATOR = 0u;

EquipmentDelegate::EquipmentDelegate(std::string name, CoreStats cstats)
	: ItemDelegate(name), Stats(cstats), UniqueId(++EQUIPMENTUNIQUEIDITERATOR) {
}

//we are doing this in the cpp file so it initialises to 0 when the program compiles
