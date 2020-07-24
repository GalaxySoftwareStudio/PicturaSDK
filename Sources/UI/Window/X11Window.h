#pragma once
#include "NullWindow.h"

namespace Pictura::UI
{
	class X11Window : public NullWindow
	{
	public:
		X11Window();
		~X11Window();

	private:
		void* SetupWindow();

	public:
		virtual void Show();
		virtual void Hide();
		virtual void Close();
		virtual void Focus();
	};
}