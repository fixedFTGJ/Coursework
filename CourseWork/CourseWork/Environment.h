#pragma once

#include <DirectXMath.h>

using namespace DirectX;

namespace CourseWork
{
	struct Coordinates
	{
		int X;
		int Y;

		Coordinates(int x, int y)
		{
			X = x;
			Y = y;
		}

		Coordinates()
		{
			X = 0;
			Y = 0;
		}
	};

	class Environment
	{
	public:
		Environment(Coordinates position, bool isObstacle);
		bool IsObstacle();
	private:
		Coordinates _position;
		bool _isObstacle;
	};
}