#include "pch.h"
#include "Dungeon.h"

using namespace CourseWork;

Dungeon::Dungeon(vector<Map*> maps)
{
	_maps = maps;
}

vector<Map*> Dungeon::GetMaps()
{
	return _maps;
}

Dungeon::Dungeon() {};