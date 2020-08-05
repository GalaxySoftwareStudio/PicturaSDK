#pragma once
#include "Core/CoreFramework.h"

namespace Pictura
{
	class Console
	{
	public:
		Console();
		~Console();

		enum class ConsoleColor
		{
			Black = 0, Grey = 7, White = 15,
			Red = 12, DarkRed = 4, Green = 10, DarkGreen = 2,
			Yellow = 14, DarkYellow = 6, Blue = 9, DarkBlue = 1,
			Magenta = 13, DarkMagenta = 5, Cyan = 11, DarkCyan = 3
		};

	public:
		static bool Init();
		static void Print(String Message, Console::ConsoleColor Color = ConsoleColor::Grey);
		static void Pause(String PauseMessage = "Press[ENTER] to continue program execution...");

#ifdef PLATFORM_WINDOWS
	private:
        static bool RedirectConsoleIO()
        {
            bool result = true;
            FILE* fp;

            // Redirect STDIN if the console has an input handle
            if (GetStdHandle(STD_INPUT_HANDLE) != INVALID_HANDLE_VALUE)
                if (freopen_s(&fp, "CONIN$", "r", stdin) != 0)
                    result = false;
                else
                    setvbuf(stdin, NULL, _IONBF, 0);

            // Redirect STDOUT if the console has an output handle
            if (GetStdHandle(STD_OUTPUT_HANDLE) != INVALID_HANDLE_VALUE)
                if (freopen_s(&fp, "CONOUT$", "w", stdout) != 0)
                    result = false;
                else
                    setvbuf(stdout, NULL, _IONBF, 0);

            // Redirect STDERR if the console has an error handle
            if (GetStdHandle(STD_ERROR_HANDLE) != INVALID_HANDLE_VALUE)
                if (freopen_s(&fp, "CONOUT$", "w", stderr) != 0)
                    result = false;
                else
                    setvbuf(stderr, NULL, _IONBF, 0);

            // Make C++ standard streams point to console as well.
            std::ios::sync_with_stdio(true);

            // Clear the error state for each of the C++ standard streams.
            std::wcout.clear();
            std::cout.clear();
            std::wcerr.clear();
            std::cerr.clear();
            std::wcin.clear();
            std::cin.clear();

            return result;
        }

        static bool ReleaseConsole()
        {
            bool result = true;
            FILE* fp;

            // Just to be safe, redirect standard IO to NUL before releasing.

            // Redirect STDIN to NUL
            if (freopen_s(&fp, "NUL:", "r", stdin) != 0)
                result = false;
            else
                setvbuf(stdin, NULL, _IONBF, 0);

            // Redirect STDOUT to NUL
            if (freopen_s(&fp, "NUL:", "w", stdout) != 0)
                result = false;
            else
                setvbuf(stdout, NULL, _IONBF, 0);

            // Redirect STDERR to NUL
            if (freopen_s(&fp, "NUL:", "w", stderr) != 0)
                result = false;
            else
                setvbuf(stderr, NULL, _IONBF, 0);

            // Detach from console
            if (!FreeConsole())
                result = false;

            return result;
        }

        static void AdjustConsoleBuffer(int16_t minLength)
        {
            // Set the screen buffer to be big enough to scroll some text
            CONSOLE_SCREEN_BUFFER_INFO conInfo;
            GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &conInfo);
            if (conInfo.dwSize.Y < minLength)
                conInfo.dwSize.Y = minLength;
            SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), conInfo.dwSize);
        }

        static bool CreateNewConsole(int16_t minLength)
        {
            bool result = false;

            // Release any current console and redirect IO to NUL
            ReleaseConsole();

            // Attempt to create new console
            if (AllocConsole())
            {
                AdjustConsoleBuffer(minLength);
                result = RedirectConsoleIO();
            }

            return result;
        }

        static bool AttachParentConsole(int16_t minLength)
        {
            bool result = false;

            // Release any current console and redirect IO to NUL
            ReleaseConsole();

            // Attempt to attach to parent process's console
            if (AttachConsole(ATTACH_PARENT_PROCESS))
            {
                AdjustConsoleBuffer(minLength);
                result = RedirectConsoleIO();
            }

            return result;
        }
#endif

	private:
		static bool Initialized;
		static Mutex m_ConsoleMutex;
	};
}