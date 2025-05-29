#pragma once
#include "buff.h"
#include <cstdint>
#include <string>

enum class ABILITYTARGET { SELF, ALLY, ENEMY };
enum class ABILITYSCALER { NONE, STR, AGI, INT };

class Ability {
public:
	Ability(std::string name = "unnamed",
		uint32_t cost = 0u,
		uint32_t cd = 1u,
		uint32_t hpe = 1u,
		Buff* b = nullptr,
		ABILITYTARGET t = ABILITYTARGET::SELF,
		ABILITYSCALER s = ABILITYSCALER::NONE);

	~Ability();

	uint32_t CooldownLeft;

	[[nodiscard]] const bool OnCooldown() const noexcept;
	void PutOnCooldown() noexcept;
	[[nodiscard]] const std::string GetName() const noexcept;
	[[nodiscard]] const uint32_t GetCooldown() const noexcept;
	[[nodiscard]] const uint32_t GetHPEffect() const noexcept;
	[[nodiscard]] const Buff* GetBuff() const noexcept;
	[[nodiscard]] const uint32_t GetCost() const noexcept;
	[[nodiscard]] const ABILITYTARGET GetTarget() const noexcept;
	[[nodiscard]] const ABILITYSCALER GetScaler() const noexcept;

private:
	std::string Name;
	uint32_t Cost;  // assume mp if there is a cost
	uint32_t Cooldown;  // number of rounds you have to wait before using it again
	uint32_t HpEffect;
	Buff* GivenBuff;
	ABILITYTARGET Target;
	ABILITYSCALER Scaler;
};