#pragma once

#include <list>
#include <vector>
#include "Map.h"

using namespace std;

namespace CourseWork
{
	class Dungeon
	{
	public:
		Dungeon(vector<Map*> maps);
		vector<Map*> GetMaps();
	private:
		vector<Map*> _maps;
	};
}