#pragma once
#include "Exception.h"

namespace Pictura::Exceptions
{
	class InvalidOperationException : public Exception
	{
	public:
		explicit InvalidOperationException(String Message) : Exception(Message, "InvalidOperationException") { }
	};
}