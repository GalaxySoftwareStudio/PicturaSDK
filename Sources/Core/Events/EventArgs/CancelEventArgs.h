#pragma once
#include "Core/CoreFramework.h"
#include "EventArgs.h"

namespace Pictura::Events
{
	class CancelEventArgs : public EventArgs
	{
	public:
		CancelEventArgs(bool value) : Cancel(value) { }
		~CancelEventArgs() { }

	public:
		bool Cancel;
	};
}