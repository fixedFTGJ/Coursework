#pragma once

#include "Environment.h"
#include "Content\ShaderStructures.h"

using namespace DirectX;

namespace CourseWork
{
	class Wall : Environment
	{
	public:
		Wall(XMFLOAT3 position, XMFLOAT3 v1, XMFLOAT3 v2, XMFLOAT3 v3, XMFLOAT3 v4, XMFLOAT3 color);
	private:
		VertexPositionColor _vertices[4];
	};
}