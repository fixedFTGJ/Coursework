#include "pch.h"
#include "Wall.h"

using namespace CourseWork;

Wall::Wall(XMFLOAT3 position, XMFLOAT3 v1, XMFLOAT3 v2, XMFLOAT3 v3, XMFLOAT3 v4, XMFLOAT3 color) : Environment(position, true)
{
	_vertices[0] = { v1, color };
	_vertices[1] = { v2, color };
	_vertices[2] = { v3, color };
	_vertices[3] = { v4, color };
}