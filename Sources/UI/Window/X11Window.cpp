#include "PicturaPCH.h"
#include "X11Window.h"

namespace Pictura::UI
{
	X11Window::X11Window()
	{
		Debug::Log::GetFrameworkLog().Info("Creating X11 Window...");
	}

	X11Window::~X11Window()
	{
		Debug::Log::GetFrameworkLog().Info("Destroying X11 Window...");
	}

	void* X11Window::SetupWindow()
	{
		return nullptr;
	}

	void X11Window::Show()
	{
		throw NotImplementedException();
	}

	void X11Window::Hide()
	{
		throw NotImplementedException();
	}

	void X11Window::Close()
	{
		throw NotImplementedException();
	}

	void X11Window::Focus()
	{
		throw NotImplementedException();
	}
}