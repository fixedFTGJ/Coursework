#include "pch.h"
#include "PlayableCharacter.h"

using namespace CourseWork;

PlayableCharacter::PlayableCharacter(int health, int armor, int damage, int dodge, int strength, int agility, int intellegence, int stamina) :
	Character(health, armor, damage, dodge)
{
	_strength = strength;
	_agility = agility;
	_intellegence = intellegence;
	_stamina = stamina;
}