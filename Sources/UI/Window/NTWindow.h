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
			DWORD result = WS_EX_APPWINDOW | WS_EX_ACCEPTFILES;

			if (WindowState == WindowState::Fullscreen || Topmost) {
				result |= WS_EX_TOPMOST | WS_EX_WINDOWEDGE;
			}

			return result;
		}

		static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
		{
			switch (uMsg)
			{
			case WM_MOVE:
				{
					//TODO : Implement Moved event
				}
				break;
			case WM_CLOSE:
				{
					CancelEventArgs e = CancelEventArgs(false);
					NTWindow* ntWnd = (NTWindow*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
					ntWnd->OnClosing(e);
					if (!e.Cancel)
					{
						DestroyWindow(hWnd);
						delete ntWnd;
					}
				}
				break;
			case WM_QUIT:
				{
					Log::GetFrameworkLog().Info("WM_QUIT");
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

		HWND SetupWindow()
		{
			WideString wideTitle = WideString(Title.begin(), Title.end());
			String ID = Types::ToString(Types::GetObjectId(this));
			WideString wndId = WideString(ID.begin(), ID.end());

			WideString className = wideTitle + L"_" + wndId;

			LPCWSTR WINDOW_CLASS = className.c_str();

			WNDCLASSEX wndClass = { };

			wndClass.cbSize = sizeof(WNDCLASSEX);
			wndClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
			wndClass.lpfnWndProc = WndProc;
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
			
			HWND fHandle = CreateWindowEx(GetWindowExStyle(), WINDOW_CLASS, WideString(Title.begin(), Title.end()).c_str(), GetWindowStyle(),
										  CW_USEDEFAULT, CW_USEDEFAULT, Width, Height,
										  NULL, NULL, GetModuleHandle(0), NULL);

			if (!fHandle) {
				throw RuntimeException("Failed to create a Win32 window !");
			}

			return fHandle;
		}

	private:
		virtual void UpdateWindow();

	public:
		virtual void Show();
		virtual void Hide();
		virtual void Close();
		virtual void Focus();

	private:
		//HWND m_wndHandle;
		
	};
}