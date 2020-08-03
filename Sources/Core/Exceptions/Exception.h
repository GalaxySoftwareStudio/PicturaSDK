#pragma once
#include "Core/CoreFramework.h"
#include "Core/System/Debug/Log.h"

namespace Pictura
{
	class Exception : public std::exception
	{
	public:
		explicit Exception(String message = "An application exception was thrown without more detail", String ExceptionName = "Exception", bool logToConsole = true) : msg_(message), ex_name_(ExceptionName)
		{
			if (logToConsole)
			{
				Debug::Log::GetFrameworkLog().Fatal(ex_name_ + " : " + this->GetMessage());
				fflush(stdout);
			}
		}

		virtual const String GetMessage() { return msg_; }

	protected:
		std::string msg_;
		std::string ex_name_;
	};
}