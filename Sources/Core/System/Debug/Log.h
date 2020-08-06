#pragma once
#include "Core/CoreFramework.h"

#if defined(PICTURA_DEBUG) || defined(APPLICATION_DEBUG)
	#define DEFAULT_LOGLEVEL LogLevel::All
#endif

#if defined(PICTURA_RELEASE) || defined(APPLICATION_RELEASE)
	#define DEFAULT_LOGLEVEL LogLevel::Fatal
#endif

namespace Pictura::Debug
{
	class Log
	{
	public:
		Log(String LogCategory) : m_LogCategory(LogCategory) { }
		~Log() { }

		enum class LogLevel { Off = 0, Fatal = 1, Error = 2, Warning = 3, Info = 4, Verbose = 5, All = 6 };

	public:
		static Log& GetFrameworkLog()
		{
			static SharedPtr<Log> inst = Types::MakeUnique<Log>("Framework");
			return *inst;
		}

		static void SetLogLevel(LogLevel NewLogLevel) { m_GlobalLogLevel = NewLogLevel; }
		static SharedPtr<Log> CreateLog(String LogCategory)
		{
			return Types::MakeShared<Log>(LogCategory);
		}


		void Debug(String Message);	
		void Info(String Message);
		void Warning(String Message);
		void Error(String Message);
		void Fatal(String Message);

	private:
		inline static LogLevel m_GlobalLogLevel = DEFAULT_LOGLEVEL;

		String m_LogCategory = "NoCategory";
	};
}