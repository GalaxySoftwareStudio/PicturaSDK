#include "PicturaPCH.h"
#include "Window.h"

namespace Pictura::UI
{
	Window::Window()
	{
#if defined(PLATFORM_WINDOWS)
		m_WindowInstance = Types::MakeUnique<NTWindow>();
#elif defined(PLATFORM_LINUX)
		m_WindowInstance = Types::MakeUnique<X11Window>());
#elif defined(PLATFORM_MACOS)
		m_WindowInstance = Types::MakeUnique<CocoaWindow>()
#endif
	}

	Window::~Window()
	{
		m_WindowInstance.reset();
	}

	void Window::Show()
	{
		m_WindowInstance->Show();
	}

	void Window::Hide()
	{
		m_WindowInstance->Hide();
	}

	void Window::Close()
	{
		m_WindowInstance->Close();
	}

	void Window::Focus()
	{
		m_WindowInstance->Focus();
	}

}