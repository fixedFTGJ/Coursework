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
		Map(int width, int height, int** pattern, list<Monster*> monsters, Coordinates startPosition);
		int GetWidth() { return _width; };
		int GetHeight() { return _height; };
		int** GetPattern() { return _pattern; };
		float GetXCenter() { return XCenter; };
		float GetYCenter() { return YCenter; };
		float GetStep() { return Step; };
		Coordinates GetStartPosition() { return _startPosition; };
	private:
		int _width;
		int _height;
		int** _pattern;
		Coordinates _startPosition;
		const float Step = 1.0;
		const float XCenter = 0.5;
		const float YCenter = 0.5;
		list<Monster*> _monsters;
	};
}