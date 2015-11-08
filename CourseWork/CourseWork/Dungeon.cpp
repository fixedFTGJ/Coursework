#include "pch.h"
#include "Dungeon.h"

using namespace CourseWork;

Dungeon::Dungeon(list<Environment> objects)
{
	_objects = objects;
}

list<Environment> Dungeon::GetDungeonObjects()
{
	return _objects;
}