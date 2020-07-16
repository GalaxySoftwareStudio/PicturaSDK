#include "PicturaPCH.h"
#include "Console.h"

namespace Pictura
{
	Mutex Console::m_ConsoleMutex;

	Console::Console()
	{

	}

	Console::~Console()
	{

	}

	void Console::Print(String Message, Console::ConsoleColor Color)
	{
		String code;
		m_ConsoleMutex.lock();
#ifndef PLATFORM_WINDOWS //Unix system code (Use ANSI escape sequence)
		switch (Color)
		{
		case Pictura::Console::ConsoleColor::Black:
			code = "\033[0;30m";
			break;
		case Pictura::Console::ConsoleColor::Grey:
			code = "\033[0;37m";
			break;
		case Pictura::Console::ConsoleColor::White:
			code = "\033[1;37m";
			break;
		case Pictura::Console::ConsoleColor::Red:
			code = "\033[1;31m";
			break;
		case Pictura::Console::ConsoleColor::DarkRed:
			code = "\033[0;31m";
			break;
		case Pictura::Console::ConsoleColor::Green:
			code = "\033[1;32m";
			break;
		case Pictura::Console::ConsoleColor::DarkGreen:
			code = "\033[0;32m";
			break;
		case Pictura::Console::ConsoleColor::Yellow:
			code = "\033[1;33m";
			break;
		case Pictura::Console::ConsoleColor::DarkYellow:
			code = "\033[0;33m";
			break;
		case Pictura::Console::ConsoleColor::Blue:
			code = "\033[1;34m";
			break;
		case Pictura::Console::ConsoleColor::DarkBlue:
			code = "\033[0;34m";
			break;
		case Pictura::Console::ConsoleColor::Magenta:
			code = "\033[1;35m";
			break;
		case Pictura::Console::ConsoleColor::DarkMagenta:
			code = "\033[0;35m";
			break;
		case Pictura::Console::ConsoleColor::Cyan:
			code = "\033[1;36m";
			break;
		case Pictura::Console::ConsoleColor::DarkCyan:
			code = "\033[0;36m";
			break;
		default:
			code = "\033[1;37m";
			break;
		}

		std::cout << code + Message + "\033[0;21m" << std::endl;
#else   //Windows NT system code (Use Console API)
		const auto hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		const auto color = Types::ToUnderlying(Color);

		FlushConsoleInputBuffer(hConsole);
		SetConsoleTextAttribute(hConsole, color);

		std::cout << Message << std::endl;

		SetConsoleTextAttribute(hConsole, 7);
#endif
		m_ConsoleMutex.unlock();
	}

	void Console::Pause(String PauseMessage)
	{
		Console::Print(PauseMessage);
		std::cin.ignore();
	}
}