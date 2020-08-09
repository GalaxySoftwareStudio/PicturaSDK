#pragma once
#include "NullWindow.h"
#include "Core/System/Runtime/Runtime.h"

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

			if (WindowState == WindowState::Fullscreen) {
				result |= WS_POPUP;
			}

			result |= WS_SYSMENU | WS_MINIMIZEBOX;

			if (Decorated) {
				result |= WS_CAPTION;
			}

			if (Resizable) {
				result |= WS_MAXIMIZEBOX | WS_THICKFRAME;
			}

			if (WindowState == WindowState::Maximized) {
				result |= WS_MAXIMIZE;
			}

			return result;
		}

		DWORD GetWindowExStyle()
		{
			DWORD result = WS_EX_APPWINDOW | WS_EX_ACCEPTFILES | WS_EX_CLIENTEDGE | WS_EX_TRANSPARENT;

			if (WindowState == WindowState::Fullscreen || Topmost) {
				result |= WS_EX_TOPMOST | WS_EX_WINDOWEDGE;
			}

			return result;
		}

		static LRESULT CALLBACK MessageRouter(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
		{
			NTWindow* ntWindow = 0;

			if (uMsg == WM_NCCREATE)
			{
				CREATESTRUCT* pCreate = ReinterpretCastTo<CREATESTRUCT*>(lParam);
				ntWindow = ReinterpretCastTo<NTWindow*>(pCreate->lpCreateParams);
				::SetWindowLongPtr(hWnd, GWLP_USERDATA, ReinterpretCastTo<LONG_PTR>(ntWindow));
				ntWindow->m_Handle = hWnd;
			}
			else
			{
				ntWindow = ReinterpretCastTo<NTWindow*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
			}
			
			if (ntWindow) {
				return ntWindow->WindowProcedure(hWnd, uMsg, wParam, lParam);
			}
			else {
				return DefWindowProc(hWnd, uMsg, wParam, lParam);
			}
		}

		LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
		{
			switch (uMsg)
			{
			case WM_MOVE:
			{
				int xPos = (int)(short)LOWORD(lParam);
				int yPos = (int)(short)HIWORD(lParam);
				PositionEventArgs e = PositionEventArgs(Maths::Position(xPos, yPos));
				PositionChanging(e);
			}
			break;
			case WM_CLOSE:
			{
				CancelEventArgs e = CancelEventArgs(false);
				this->OnClosing(e);
				if (!e.Cancel)
				{
					auto it = WindowList.find(m_Handle);
					if (it != WindowList.end())
					{
						WindowList.erase(it);
					}

					DestroyWindow(hWnd);
					delete this;
				}
			}
			break;
			case WM_QUIT:
			{
				Log::GetFrameworkLog().Info("WM_QUIT from Window");
			}
			break;
			case WM_DESTROY:
			{

			}
			break;
			default:
				return DefWindowProc(hWnd, uMsg, wParam, lParam);
				break;
			}

			return 0;
		}

		void SetupWindow()
		{
			WideString wideTitle = WideString(Title.begin(), Title.end());
			String ID = Types::ToString(Types::GetObjectId(this));
			WideString wndId = WideString(ID.begin(), ID.end());

			WideString className = wideTitle + L"_" + wndId;

			LPCWSTR WINDOW_CLASS = className.c_str();

			WNDCLASSEX wndClass = {0};

			wndClass.cbSize = sizeof(WNDCLASSEX);
			wndClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
			wndClass.lpfnWndProc = &NTWindow::MessageRouter;
			wndClass.cbClsExtra = 0;
			wndClass.cbWndExtra = 0;
			wndClass.hInstance = GetModuleHandle(NULL);
			wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
			wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
			wndClass.hbrBackground = (HBRUSH)GetStockObject(DKGRAY_BRUSH);
			wndClass.lpszMenuName = NULL;
			wndClass.lpszClassName = WINDOW_CLASS;
			wndClass.hIconSm = LoadIcon(NULL, IDI_WINLOGO);
			
			if (!RegisterClassEx(&wndClass))
			{
				throw RuntimeException("Failed to register Win32 window class !");
			}

			Log::GetFrameworkLog().Debug("Registered window class '" + String(className.begin(), className.end()) + "'");

			int screenWidth = GetSystemMetrics(SM_CXSCREEN);
			int screenHeight = GetSystemMetrics(SM_CYSCREEN);

			if (WindowState == WindowState::Fullscreen)
			{
				DEVMODE dmScreenSettings;
				memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
				dmScreenSettings.dmSize = sizeof(dmScreenSettings);
				dmScreenSettings.dmPelsWidth = screenWidth;
				dmScreenSettings.dmPelsHeight = screenHeight;
				dmScreenSettings.dmBitsPerPel = 32;
				dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

				if ((Width != screenWidth) && (Height != screenHeight))
				{
					if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
					{
						Log::GetFrameworkLog().Warning("Failed to switch to fullscreen window !");
						WindowState = WindowState::Maximized;
					}
				}
			}

			RECT wndRect;
			
			wndRect.left = 0;
			wndRect.top = 0;
			wndRect.right = WindowState == WindowState::Fullscreen ? (long)screenWidth : (long)Width;
			wndRect.bottom = WindowState == WindowState::Fullscreen ? (long)screenHeight : (long)Height;

			AdjustWindowRectEx(&wndRect, GetWindowStyle(), FALSE, GetWindowExStyle());
			
			m_Handle = CreateWindowEx(GetWindowExStyle(), WINDOW_CLASS, WideString(Title.begin(), Title.end()).c_str(), GetWindowStyle(),
										  CW_USEDEFAULT, CW_USEDEFAULT, Width, Height,
										  NULL, NULL, GetModuleHandle(0), this);

			::SetWindowLongPtr(m_Handle, GWLP_USERDATA, ReinterpretCastTo<LONG_PTR>(this));

			if (!m_Handle) {
				throw RuntimeException("Failed to create a Win32 window !");
			}
		}

	public:
		virtual void Show();
		virtual void Hide();
		virtual void Close();
		virtual void Focus();
		virtual void Update();

	private:
		MSG m_msgHandler = { 0 };
		
	};
}