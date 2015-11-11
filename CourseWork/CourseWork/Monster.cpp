#include "pch.h"
#include "Monster.h"

using namespace CourseWork;

Monster::Monster(Coordinates position, int health, int armor, int damage, int dodge) : Character(health, armor, damage, dodge)
{
	_position = position;
}