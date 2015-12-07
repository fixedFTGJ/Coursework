#pragma once

#include "Character.h"

namespace CourseWork
{
	class PlayableCharacter : Character
	{
	public:
		PlayableCharacter(int health, int armor, int damage, int dodge, int strength, int agility, int intellegence, int stamina);
	private:
		int _strength;
		int _agility;
		int _intellegence;
		int _stamina;
	};
}