#pragma once
#include "Core/CoreFramework.h"
#include "Core/Events/EventArgs/EventArgs.h"
#include "Core/System/Maths/Position.h"

namespace Pictura::Events
{
	class PositionEventArgs : public EventArgs
	{
	public:
		PositionEventArgs(Maths::Position position) : Position(position) { }
		~PositionEventArgs() { }

	public:
		Maths::Position Position;
	};
}