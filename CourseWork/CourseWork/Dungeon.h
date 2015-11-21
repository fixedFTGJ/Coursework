#pragma once

#include <list>
#include "Map.h"

using namespace std;

namespace CourseWork
{
	class Dungeon
	{
	public:
		Dungeon(list<Map*> maps);
	private:
		list<Map*> _maps;
	};
}