#include "pch.h"
#include "Environment.h"

using namespace CourseWork;

Environment::Environment(XMFLOAT3 position, bool isObstacle)
{
	_position = position;
	_isObstacle = isObstacle;
}

bool Environment::IsObstacle()
{
	return _isObstacle;
}