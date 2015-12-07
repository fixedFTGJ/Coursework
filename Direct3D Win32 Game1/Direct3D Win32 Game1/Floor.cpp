#include "pch.h"
#include "Floor.h"

using namespace CourseWork;

Floor::Floor(bool isObstacle, float width) : Environment(isObstacle)
{
	_width = width;
}