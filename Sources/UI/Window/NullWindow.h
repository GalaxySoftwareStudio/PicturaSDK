#pragma once
#include "Core/CoreFramework.h"
#include "Core/Events/Event.h"
#include "Core/Events/EventArgs/CancelEventArgs.h"
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

	public:
		virtual void Show() = 0;
		virtual void Hide() = 0;

		virtual void Close()
		{
			auto it = WindowList.find(m_Handle);
			if (it != WindowList.end())
			{
				WindowList.erase(it);
			}
		}

		virtual void Focus() = 0;

	public:
		NativeHandleType GetHandle() { return m_Handle; }
		static inline Map<NativeHandleType, UI::NullWindow*> WindowList = { };

	protected:
		NativeHandleType m_Handle = nullptr;

	public:
		event(CancelEventArgs, Closing);

	public:
		WindowState WindowState = WindowState::Normal;
		bool Topmost = false;
		bool Resizable = true;
		bool Decorated = true;

		int Width = 800;
		int Height = 450;

		String Title = "Untitled window";
	};
}