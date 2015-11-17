#pragma once

#include "Environment.h"
#include "Content\ShaderStructures.h"

using namespace DirectX;

namespace CourseWork
{
	class Wall : Environment
	{
	public:
		Wall(bool isObstacle, float width, float height);
	private:
		float _width;
		float _height;
	};
}