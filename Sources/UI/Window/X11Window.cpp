#include "PicturaPCH.h"
#include "Window.h"

#ifdef PLATFORM_LINUX
namespace Pictura::UI
{
	Window::Window()
	{
		Debug::Log::GetFrameworkLog().Info("Creating X11 Window...");
	}

	Window::~Window()
	{
		Debug::Log::GetFrameworkLog().Info("Destroying X11 Window...");
	}
}
#endif