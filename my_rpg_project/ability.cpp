#include "ability.h"

Ability::Ability(std::string name, uint32_t cost, uint32_t cd, uint32_t hpe, Buff* b, ABILITYTARGET t, ABILITYSCALER s)
	: Name(name), Cost(cost), Cooldown(cd), HpEffect(hpe), GivenBuff(b), Target(t), Scaler(s) {
}

Ability::~Ability() {
	if (GivenBuff) {
		delete GivenBuff;
		GivenBuff = nullptr;
	}
}