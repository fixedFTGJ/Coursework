#include "pch.h"
#include "Party.h"

using namespace CourseWork;

Party::Party(PlayableCharacter* character0, PlayableCharacter* character1, PlayableCharacter* character2, PlayableCharacter* character3)
{
	_characters[0] = character0;
	_characters[1] = character1;
	_characters[2] = character2;
	_characters[3] = character3;
}