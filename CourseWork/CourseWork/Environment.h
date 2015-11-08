#pragma once

#include <DirectXMath.h>

using namespace DirectX;

namespace CourseWork
{
	class Environment
	{
	public:
		Environment(XMFLOAT3 position, bool isObstacle);
		bool IsObstacle();
	private:
		XMFLOAT3 _position;
		bool _isObstacle;
	};
}