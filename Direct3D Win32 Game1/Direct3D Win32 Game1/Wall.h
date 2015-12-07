#pragma once

#include "Environment.h"

using namespace DirectX;

namespace CourseWork
{
	class Wall : Environment
	{
	public:
		Wall(bool isObstacle, float width, float height);
		float GetWidth() { return _width; };
		float GetHeight() { return _height; };
	private:
		float _width;
		float _height;
	};
}