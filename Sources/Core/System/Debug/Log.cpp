#include "PicturaPCH.h"
#include "Log.h"
#include "Core/System/Console.h"
#include "Core/System/DateTime.h"

namespace Pictura::Debug
{
    void Log::Debug(String Message)
    {
        if (m_GlobalLogLevel < LogLevel::Verbose)
        {
            return;
        }
        Console::Print("[DEBUG - " + DateTime::GetCurrentTimeFormat() + "] " + m_LogCategory + ": " + Message);
    }

    void Log::Info(String Message)
    {
        if (m_GlobalLogLevel < LogLevel::Info)
        {
            return;
        }
        Console::Print("[INFO - " + DateTime::GetCurrentTimeFormat() + "] " + m_LogCategory + ": " + Message, Console::ConsoleColor::Blue);
    }

    void Log::Success(String Message)
    {
        if (m_GlobalLogLevel < LogLevel::Success)
        {
            return;
        }
        Console::Print("[SUCCESS - " + DateTime::GetCurrentTimeFormat() + "] " + m_LogCategory + ": " + Message, Console::ConsoleColor::Green);
    }

    void Log::Warning(String Message)
    {
        if (m_GlobalLogLevel < LogLevel::Warning)
        {
            return;
        }
        Console::Print("[WARNING - " + DateTime::GetCurrentTimeFormat() + "] " + m_LogCategory + ": " + Message, Console::ConsoleColor::Yellow);
    }

    void Log::Error(String Message)
    {
        if (m_GlobalLogLevel < LogLevel::Error)
        {
            return;
        }
        Console::Print("[ERROR - " + DateTime::GetCurrentTimeFormat() + "] " + m_LogCategory + ": " + Message, Console::ConsoleColor::Red);
    }
	
    void Log::Fatal(String Message)
    {
        if (m_GlobalLogLevel < LogLevel::Fatal)
        {
            return;
        }
        Console::Print("[FATAL - " + DateTime::GetCurrentTimeFormat() + "] " + m_LogCategory + ": " + Message, Console::ConsoleColor::DarkRed);
    }
}