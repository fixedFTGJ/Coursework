#pragma once

#include "Dungeon.h"

namespace CourseWork
{
	class DungeonInitializer
	{
	public:
		DungeonInitializer();
		Dungeon* Initialize();
	private:
		static const int MapWidth = 20;
		static const int MapHeight = 20;
		static const int MapsNumber = 5;
	};
}