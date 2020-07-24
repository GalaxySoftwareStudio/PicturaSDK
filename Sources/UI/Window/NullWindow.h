#pragma once
#include "Core/CoreFramework.h"
#include "Core/System/Debug/Log.h"
#include "Core/Exceptions/Exceptions.h"

namespace Pictura::UI
{
	class NullWindow
	{
	public:
		virtual ~NullWindow() {}

	public:
		virtual void Show() = 0;
		virtual void Hide() = 0;
		virtual void Close() = 0;
		virtual void Focus() = 0;
	};
}