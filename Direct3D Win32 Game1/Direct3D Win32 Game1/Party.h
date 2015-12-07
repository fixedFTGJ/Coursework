#pragma once

#include "PlayableCharacter.h"

namespace CourseWork
{
	class Party
	{
	public:
		Party(PlayableCharacter* character0, PlayableCharacter* character1, PlayableCharacter* character2, PlayableCharacter* character3);
	private:
		PlayableCharacter* _characters[4];
	};
}
