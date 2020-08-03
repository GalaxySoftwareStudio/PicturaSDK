#pragma once
#include "Core/CoreFramework.h"
#include "Core/System/Debug/Log.h"
#include "Core/Exceptions/Exceptions.h"

using namespace Pictura::Debug;

namespace Pictura::UI
{
	class NullWindow
	{
	public:
		enum class WindowState {Normal, Minimized, Maximized, Fullscreen};

	public:
		virtual ~NullWindow() {}

	private:
		virtual void UpdateWindow() = 0;

	public:
		virtual void Show() = 0;
		virtual void Hide() = 0;
		virtual void Close() = 0;
		virtual void Focus() = 0;

	public:
		WindowState WindowState = WindowState::Normal;
		bool Topmost = false;
		bool Resizable = true;
		bool Decorated = true;

		int Width, Height = 400;

		String Title = "Untitled window";
	};
}