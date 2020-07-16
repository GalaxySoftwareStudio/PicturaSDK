#pragma once
#include "Core/CoreFramework.h"
#include "Core/Exceptions/Exception.h"
#include "Core/System/Debug/Log.h"

namespace Pictura::Debug
{
	class RuntimeDebug
	{
	public:
		RuntimeDebug() { }
		~RuntimeDebug() { }

	public:
		static void Assert(bool Condition, const String& Message = "Unknown reason")
		{
			if (Condition)
			{
				throw Exception("Assertion failed : " + Message);
			}
		}
	};
}