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
		const float Step = 20.0;
		const float XCenter = 10.0;
		const float YCenter = 10.0;
		list<Environment*> _objects;
		list<Monster*> _monsters;
	};
}