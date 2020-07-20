#include "PicturaPCH.h"
#include "Window.h"

#ifdef PLATFORM_WINDOWS
namespace Pictura::UI
{
	Window::Window()
	{
		Debug::Log::GetFrameworkLog().Info("Creating Win32 Window...");
	}

	Window::~Window()
	{
		Debug::Log::GetFrameworkLog().Info("Destroyinh Win32 Window...");
	}
}
#endif