#pragma once
#include "Core/CoreFramework.h"

namespace Pictura::Events
{
	class EventArgs
	{
	public:
		EventArgs() { }
		~EventArgs() { }
	};

	inline static Pictura::Events::EventArgs* EmptyEventArgs = new Pictura::Events::EventArgs();
}