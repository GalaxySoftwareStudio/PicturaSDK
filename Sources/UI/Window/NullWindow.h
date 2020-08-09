#pragma once
#include "Core/CoreFramework.h"
#include "Core/Threading/Thread.h"
#include "Core/Events/Event.h"
#include "Core/Events/EventArgs/CancelEventArgs.h"
#include "WindowEventArgs.h"
#include "Core/System/Debug/Log.h"
#include "Core/Exceptions/Exceptions.h"

using namespace Pictura::Debug;

namespace Pictura::UI
{
	class NullWindow
	{
	public:
		enum class WindowState {Normal = 0, Minimized = 1, Maximized = 2, Fullscreen = 3};

	public:
		virtual ~NullWindow() { }

	public:
		virtual void Show() = 0;
		virtual void Hide() = 0;

		virtual void Close() = 0;

		virtual void Focus() = 0;
		virtual void Update() = 0;

	public:
		void* OwnerPtr = nullptr;
		NativeHandleType &GetHandle() { return m_Handle; }
		static inline Map<NativeHandleType, UI::NullWindow*> WindowList = { };

	protected:
		NativeHandleType m_Handle = nullptr;
		bool isActive = false;

	public:
		event(PositionEventArgs, PositionChanging);
		event(CancelEventArgs, Closing);
		event(EventArgs, Shown);
		event(EventArgs, StateChanged);

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