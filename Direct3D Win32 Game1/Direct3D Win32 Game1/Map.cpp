#include "pch.h"
#include "Map.h"

using namespace CourseWork;

Map::Map(int width, int height, int** pattern, list<Monster*> monsters, Coordinates startPosition)
{
	_width = width;
	_height = height;
	_pattern = pattern;
	_monsters = monsters;
	_startPosition = startPosition;
}