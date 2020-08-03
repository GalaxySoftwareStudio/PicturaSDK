#pragma once
#include "Exception.h"

namespace Pictura::Exceptions
{
	class RuntimeException : public Exception
	{
	public:
		explicit RuntimeException(String Message) : Exception(Message, "RuntimeException") { }
	};
}