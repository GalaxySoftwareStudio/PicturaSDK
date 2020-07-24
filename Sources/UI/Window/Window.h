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
		void Show();
		void Hide();
		void Close();
		void Focus();

	private:
		UniquePtr<NullWindow> m_WindowInstance;
	};
}