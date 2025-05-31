#pragma once
#include "typing.h"

class PointWell { //could be health, mana, coins 
public:
	PointWell();
	PointWell(t_pw pts);
	PointWell(t_pw currP, t_pw maxP);

	bool SetMax(t_pw new_max) noexcept;
	void AddMax(t_pw add_max, bool restore = true) noexcept;
	void SubCur(t_pw damage) noexcept;
	void AddCur(t_pw amount) noexcept;
	void ModCur(t_pw amt) noexcept;
	//getters
	[[nodiscard]] const t_pw GetCurrent() const noexcept;
	[[nodiscard]] const t_pw GetMax() const noexcept;
	[[nodiscard]] const bool IsFull() const noexcept;

private:
	t_pw _current_fullness;
	t_pw _max_well; //max size of uint16 is 65535
};