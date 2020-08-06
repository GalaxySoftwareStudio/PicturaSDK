#pragma once
#include "Core/Threading/Thread.h"
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
		void CreateNativeWindow();

	private:
		UniquePtr<NullWindow> m_WindowInstance = nullptr;
	};
}