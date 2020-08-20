#pragma once
#include "Core/CoreFramework.h"

namespace Pictura::Maths
{
	struct Vector2
	{
	public:
		Vector2() {
			X = 0;
			Y = 0;
		}

		Vector2(float x, float y) : X(x), Y(y) { }

	public:
		float X = 0;
		float Y = 0;
	};
}