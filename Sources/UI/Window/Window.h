#pragma once
#include "NTWindow.h"
#include "X11Window.h"

namespace Pictura::UI
{
	class Window
	{
	public:
		Window();
		virtual ~Window();

	public:
		NullWindow* operator->() const { return m_WindowInstance.get(); }

	private:
		UniquePtr<NullWindow> m_WindowInstance;
	};
}