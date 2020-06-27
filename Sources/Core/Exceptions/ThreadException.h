#pragma once
#include "Exception.h"

namespace Pictura::Exceptions
{
	class ThreadException : public Exception
	{
	public:
		explicit ThreadException(String Message) : Exception(Message, "ThreadException") { }
	};
}