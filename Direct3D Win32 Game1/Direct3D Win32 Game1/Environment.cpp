#include "pch.h"
#include "Environment.h"

using namespace CourseWork;

Environment::Environment(bool isObstacle)
{
	_isObstacle = isObstacle;
}

bool Environment::IsObstacle()
{
	return _isObstacle;
}