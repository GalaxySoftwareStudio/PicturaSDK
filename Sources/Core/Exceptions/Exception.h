#pragma once
#include "Core/CoreFramework.h"
#include "Core/System/Debug/Log.h"

namespace Pictura
{
	class Exception : public std::exception
	{
	public:
		explicit Exception(String message, String ExceptionName = "Exception", bool logToConsole = true) : msg_(message), ex_name_(ExceptionName)
		{
			if (logToConsole)
			{
				Debug::Log::GetFrameworkLog().Fatal(ex_name_ + " : " + this->GetMessage());
			}
		}

		virtual const String GetMessage() { return msg_; }

	protected:
		std::string msg_;
		std::string ex_name_;
	};
}