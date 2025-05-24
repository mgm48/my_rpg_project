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

bool PointWell::SetMax(t_pw new_max) noexcept {
	if (new_max < 0)
		return false;

	_max_well = new_max;

	if (_current_fullness > _max_well)
		_current_fullness = _max_well;

	return true;
}
void PointWell::AddMax(t_pw add_max, bool restore) noexcept {
	if (add_max > 0) {
		_max_well += add_max;
	}
	if (restore && _current_fullness < _max_well)
		_current_fullness = _max_well;
}

void PointWell::SubCur(t_pw damage) noexcept {
	if (damage > _current_fullness)
		_current_fullness = 0;
	else
		_current_fullness -= damage;
}
void PointWell::AddCur(t_pw amount) noexcept {
	if (amount + _current_fullness > _max_well)
		_current_fullness = _max_well;
	else
		_current_fullness += amount;
}

//getters
[[nodiscard]] const t_pw PointWell::GetCurrent() const noexcept { return _current_fullness; }
[[nodiscard]] const t_pw PointWell::GetMax() const noexcept { return _max_well; }
[[nodiscard]] const bool PointWell::IsFull() const noexcept { return _max_well == _current_fullness; }
