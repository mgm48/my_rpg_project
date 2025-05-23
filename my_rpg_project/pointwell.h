#pragma once
#include "types.h"

class PointWell { //could be health, mana, coins 
public:
	PointWell() { CurrentPW = 1; MaxPW = 1; }
	PointWell(t_pw pts) {
		CurrentPW = pts;
		MaxPW = pts;
	}
	PointWell(t_pw maxP, t_pw currP) {
		if (currP > maxP)
			currP = maxP;

		CurrentPW = currP;
		MaxPW = maxP;	
	}
	//return true if set successfully
	bool setMax(t_pw new_max) {
		if (new_max < 0)
			return false;

		MaxPW = new_max;

		if (CurrentPW > MaxPW)
			CurrentPW = MaxPW;

		return true;
	}
	void newMax(t_pw new_max) { // need to use signed 
		if (new_max > 0 || new_max < MaxPW)
			MaxPW += new_max;
		else
			MaxPW = 1;
		if (CurrentPW != MaxPW)
			CurrentPW = MaxPW;
	}

	void addMax(t_pw add_max, bool restore) {
		if (add_max > 0) {
			MaxPW += add_max;
		}
		if (restore && CurrentPW < MaxPW)
			CurrentPW = MaxPW;
	}
	
	void subMax(t_pw sub_max) {
		if (sub_max >= MaxPW)
			MaxPW = 1;
		else
			MaxPW -= sub_max;

		if (CurrentPW > MaxPW)
			CurrentPW = MaxPW;
	}

	void subCur(t_pw damage) {
		if (damage > CurrentPW)
			CurrentPW = 0;
		else
			CurrentPW -= damage;
	}

	void addCur(t_pw amount) {
		if (amount + CurrentPW > MaxPW)
			CurrentPW = MaxPW;
		else
			CurrentPW += amount;
	}

	//getters
	t_pw getCurrent() { return CurrentPW; }
	t_pw getMax() { return MaxPW; }

private:
	t_pw CurrentPW;
	t_pw MaxPW; //max size of uint16 is 65535
protected:

};