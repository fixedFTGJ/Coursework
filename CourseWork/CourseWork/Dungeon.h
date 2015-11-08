#pragma once

#include <list>
#include "Environment.h"

using namespace std;

namespace CourseWork
{
	class Dungeon
	{
	public:
		Dungeon(list<Environment> objects);
		list<Environment> GetDungeonObjects();
	private:
		list<Environment> _objects;
	};
}