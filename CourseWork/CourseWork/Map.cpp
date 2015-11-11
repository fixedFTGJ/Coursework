#include "pch.h"
#include "Map.h"

using namespace CourseWork;

Map::Map(int width, int height, int** pattern, list<Environment*> objects, list<Monster*> monsters)
{
	_width = width;
	_height = height;
	_pattern = pattern;
	_objects = objects;
	_monsters = monsters;
}