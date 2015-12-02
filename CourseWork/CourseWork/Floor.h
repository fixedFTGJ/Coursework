#pragma once

#include "Environment.h"

namespace CourseWork
{
	class Floor : Environment
	{
	public:
		Floor(bool isObstacle, float width);
		float GetWidth() { return _width; };
	private:
		float _width;
	};
}