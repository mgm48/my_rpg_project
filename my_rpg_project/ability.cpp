#include "ability.h"

Ability::Ability(std::string name, uint32_t cost, uint32_t cd, uint32_t hpe, Buff* b, ABILITYTARGET t, ABILITYSCALER s)
	: Name(name), Cost(cost), Cooldown(cd), HpEffect(hpe), GivenBuff(b), Target(t), Scaler(s) {
	CooldownLeft = 0u;
}

Ability::~Ability() {
	if (GivenBuff) {
		delete GivenBuff;
		GivenBuff = nullptr;
	}
}

[[nodiscard]] const bool Ability::OnCooldown() const noexcept { return CooldownLeft > 0; }

void Ability::PutOnCooldown() noexcept{ CooldownLeft = this->Cooldown; }

const std::string Ability::GetName() const noexcept { return Name; }

const uint32_t Ability::GetCooldown() const noexcept { return Cooldown; }

const uint32_t Ability::GetHPEffect() const noexcept { return HpEffect; }

const Buff* Ability::GetBuff() const noexcept { return GivenBuff; }

const uint32_t Ability::GetCost() const noexcept { return Cost; }

const ABILITYTARGET Ability::GetTarget() const noexcept { return Target; }

const ABILITYSCALER Ability::GetScaler() const noexcept { return Scaler; }