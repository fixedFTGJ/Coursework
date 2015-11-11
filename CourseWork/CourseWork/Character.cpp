#include "pch.h"
#include "Character.h"

using namespace CourseWork;
using namespace std;

Character::Character(int health, int armor, int damage, int dodge)
{
	_health = health;
	_armor = armor;
	_damage = damage;
	_dodge = dodge;
};

void Character::Attack(Character* target)
{
	target->ReceiveDamage(_damage);
};

void Character::ReceiveDamage(int damage)
{
	if (!IsDodge() && ((damage - _armor) > 0))
	{
		_health = _health - (damage - _armor);
	}
};

bool Character::IsDodge()
{
	if ((rand() % 100 + 1) <= _dodge)
		return true;
	else
		return false;
};