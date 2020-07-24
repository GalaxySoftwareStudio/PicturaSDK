#pragma once
#include "Exception.h"

namespace Pictura::Exceptions
{
	class NotImplementedException : public Exception
	{
	public:
		explicit NotImplementedException(String Message = "An application exception was thrown without more detail") : Exception(Message, "NotImplementedException") { }
	};
}