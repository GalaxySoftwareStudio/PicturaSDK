#pragma once
#include "NullWindow.h"

namespace Pictura::UI
{
	class NTWindow : public NullWindow
	{
	public:
		NTWindow();
		~NTWindow();
	
	private:
		DWORD GetWindowStyle()
		{
			DWORD result = WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

			//TODO : If fullscreen
			//result |= WS_POPUP

			result |= WS_SYSMENU | WS_MINIMIZEBOX;

			result |= WS_CAPTION; //TODO : If decorated
			result |= WS_MAXIMIZEBOX | WS_THICKFRAME; //TODO : If resizable

			//TODO : If maximized
			//result = |= WS_MAXIMIZE

			return result;
		}

		DWORD GetWindowExStyle()
		{
			DWORD result = WS_EX_APPWINDOW | WS_EX_ACCEPTFILES;
			//TODO : If fullscreen of topmost
			//result |= WS_EX_TOPMOST;

			return result;
		}

		HWND SetupWindow()
		{
			WCHAR* windowTitle;

			DWORD wndStyle = GetWindowStyle();
			DWORD wndExStyle = GetWindowExStyle();

			int xPos, yPos = CW_USEDEFAULT;

			return nullptr;
		}

	public:
		virtual void Show();
		virtual void Hide();
		virtual void Close();
		virtual void Focus();

	private:
		HWND m_wndHandle;
	};
}