#pragma once
#include "types.h"
#include "playercharacter.h"

//las macros no entienden new lines, de ahí poner los backslashes
#define LEVELUP \
HP->AddMax((t_pw)(BASEHP / 2.f), restore);\
if (MP) {\
  MP->AddMax((t_pw)(BASEMP / 2.f), restore);\
}\
increase_stats((t_stat)((BASESTR + 1u) / 2.f), (t_stat)((BASEINT + 1u) / 2.f), (t_stat)((BASEAGI + 1u) / 2.f));\


#define CHARACTERDEF(basehp, basemp, basestr, baseint, baseagi, rest)\
	static const bool restore = rest;\
	static const t_pw BASEHP = (t_pw)basehp;\
	static const t_pw BASEMP = (t_pw)basemp;\
	static const t_stat BASESTR = (t_stat)basestr;\
	static const t_stat BASEINT = (t_stat)baseint;\
	static const t_stat BASEAGI = (t_stat)baseagi;\


class Warrior : public PlayerCharacterDelegate {
public:
	CHARACTERDEF(18, 0, 5, 2, 2, true)
		Warrior();
private:
	void level_char_up() noexcept override;
};

class Cleric : public PlayerCharacterDelegate {
public:
	CHARACTERDEF(14, 10, 3, 5, 1, true)
		Cleric();
private:
	void level_char_up() noexcept override;
};

class Wizard : public PlayerCharacterDelegate {
public:
	CHARACTERDEF(10, 14, 1, 8, 1, false)
		Wizard();
private:
	void level_char_up() noexcept override;
};

class Rogue : public PlayerCharacterDelegate {
public:
	CHARACTERDEF(12, 0, 3, 3, 5, false)
		Rogue();
private:
	void level_char_up() noexcept override;
};