#include "item.h"

//we are doing this in the cpp file so it initialises to 0 when the program compiles
// don't change this, only the EquipmentDelegate constructor should touch this
static std::uint32_t EQUIPMENTUNIQUEIDITERATOR = 0u;

EquipmentDelegate::EquipmentDelegate(std::string name, CoreStats cstats) 
    : ItemDelegate(name), Stats(cstats), UniqueId(++EQUIPMENTUNIQUEIDITERATOR) {}

const Buff* Potion::GetBuff() const { return _buff; }
void Potion::SetBuff(Buff* new_buff) {
  if (_buff) {
    delete _buff;
    _buff = nullptr;
  }
  _buff = new_buff;
}
Potion::Potion(std::string name, t_pw hp_heal, item_count quant, Buff* buf)
  : ItemDelegate(name), _buff(buf), HealAmount(hp_heal), Quantity(quant) {
}
Potion::~Potion() {  // only ItemManger can clean this up
  if (_buff) {
    delete _buff;
    _buff = nullptr;
  }
}

Armor::Armor(std::string name, CoreStats cstats, ARMORSLOT slot) : EquipmentDelegate(name, cstats), Slot(slot) {}
Armor::~Armor() {}

Weapon::Weapon(std::string name, CoreStats stats, WEAPONSLOT slot, t_dmg mind, t_dmg maxd, bool hands) :
    EquipmentDelegate(name, stats), Slot(slot), MinDamage(mind), MaxDamage(maxd), is2H(hands) {}
Weapon::~Weapon() {}
