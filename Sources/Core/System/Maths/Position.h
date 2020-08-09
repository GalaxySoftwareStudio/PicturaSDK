#pragma once
#include "Core/CoreFramework.h"

namespace Pictura::Maths
{
	struct Position
	{
	public:
		Position()
		{
			X = 0;
			Y = 0;
		}

		Position(float x, float y)
		{
			X = x;
			Y = y;
		}

	public:
		float X = 0;
		float Y = 0;
	};
}