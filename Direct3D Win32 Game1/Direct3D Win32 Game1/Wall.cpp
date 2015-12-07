#include "pch.h"
#include "Wall.h"

using namespace CourseWork;

Wall::Wall(bool isObstacle, float width, float height) : Environment(isObstacle)
{
	_width = width;
	_height = height;
}