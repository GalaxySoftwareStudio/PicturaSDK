#pragma once
#include "Core/CoreFramework.h"
#include "Core/Exceptions/Exception.h"
#include "Core/System/Debug/Log.h"

#if !defined(APPLICATION_DEBUG) || !defined(APPLICATION_RELEASE) || defined(PICTURA_DEBUG)
	#include "NTRuntime.h"
#endif

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