#pragma once

#include "Environment.h"
#include "Character.h"

namespace CourseWork
{
	class Monster : Character
	{
	public:
		Monster(Coordinates position, int health, int armor, int damage, int dodge);
	private:
		Coordinates _position;
	};
}