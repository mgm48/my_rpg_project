#include "pointwell.h"

PointWell::PointWell() { _current_fullness = 1; _max_well = 1; }
PointWell::PointWell(t_pw pts) {
	_current_fullness = pts;
	_max_well = pts;
}
PointWell::PointWell(t_pw currP, t_pw maxP) {
	if (currP > maxP)
		currP = maxP;

	_current_fullness = currP;
	_max_well = maxP;
}

bool PointWell::SetMax(t_pw new_max) noexcept { //sets a new max and current becomes max as well
	if (new_max < 0)
		return false;

	_max_well = new_max;

	if (_current_fullness != _max_well)
		_current_fullness = _max_well;

	return true;
}
void PointWell::AddMax(t_pw add_max, bool restore) noexcept {
	_max_well += add_max;
	if ((restore && _current_fullness < _max_well) || (_current_fullness > _max_well))
		_current_fullness = _max_well;
}

void PointWell::SubCur(t_pw amount) noexcept { 
	_current_fullness -= amount;
	if (_current_fullness > _max_well) { _current_fullness = _max_well; }
	if (_current_fullness < 0) { _current_fullness = 0; }
}
void PointWell::AddCur(t_pw amount) noexcept { 
	_current_fullness += amount;
	if (_current_fullness > _max_well) { _current_fullness = _max_well; }
	if (_current_fullness < 0) { _current_fullness = 0; }
}
void PointWell::ModCur(t_pw amt) noexcept { //never becomes 0
	_current_fullness += amt;
	if (_current_fullness < 1) { _current_fullness = 1; }
	if (_current_fullness > _max_well) { _current_fullness = _max_well; }
}

//getters
[[nodiscard]] const t_pw PointWell::GetCurrent() const noexcept { return _current_fullness; }
[[nodiscard]] const t_pw PointWell::GetMax() const noexcept { return _max_well; }
[[nodiscard]] const bool PointWell::IsFull() const noexcept { return _max_well == _current_fullness; }
