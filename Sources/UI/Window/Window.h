#pragma once
#include "Core/Threading/Thread.h"
#include "NTWindow.h"
#include "X11Window.h"

namespace Pictura::UI
{
	class Window
	{
	public:
		enum class WindowState { Normal = 0, Minimized = 1, Maximized = 2, Fullscreen = 3 };

	public:
		Window();
		virtual ~Window();

	public:
		NullWindow* operator->() const { if (m_WindowInstance == nullptr) { throw InvalidOperationException("The requested window was destroyed!"); } return m_WindowInstance; }

	private:
		void CreateNativeWindow();

	private:
		UniquePtr<Threading::Thread> m_wndThread = nullptr;
		NullWindow* m_WindowInstance = nullptr;
	};
}