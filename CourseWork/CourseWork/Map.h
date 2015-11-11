#pragma once

#include<list>
#include "Environment.h"
#include "Monster.h"

using namespace std;

namespace CourseWork
{
	enum MapElements
	{
		floor = 0,
		wall
	};

	class Map
	{
	public:
		Map(int width, int height, int** pattern, list<Environment*> objects, list<Monster*> monsters);
	private:
		int _width;
		int _height;
		int** _pattern;
		list<Environment*> _objects;
		list<Monster*> _monsters;
	};
}