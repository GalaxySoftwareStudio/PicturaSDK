#pragma once
#include "Core/CoreFramework.h"
#include "Core/Events/EventArgs/EventArgs.h"
#include "Core/System/Maths/Vector2.h"

namespace Pictura::Events
{
	class PositionEventArgs : public EventArgs
	{
	public:
		PositionEventArgs(Maths::Vector2 position) : Position(position) { }
		~PositionEventArgs() { }

	public:
		Maths::Vector2 Position;
	};

	class SizeEventArgs : public EventArgs
	{
	public:
		SizeEventArgs(Maths::Vector2 size) : Size(size) { }
		~SizeEventArgs() { }

	public:
		Maths::Vector2 Size;
	};
}