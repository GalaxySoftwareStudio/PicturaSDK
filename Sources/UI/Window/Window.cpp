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
		NullWindow::WindowList.insert(Pair<NativeHandleType, NullWindow*>(m_WindowInstance->GetHandle(), m_WindowInstance.get()));
	}

	Window::~Window()
	{
		m_WindowInstance.reset();
	}
}