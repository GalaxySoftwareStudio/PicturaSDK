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
		RECT GetWindowBorderRect()
		{
			WINDOWINFO WindowInfo = {0};
			WindowInfo.cbSize = sizeof(WindowInfo);
			::GetWindowInfo(m_Handle, &WindowInfo);

			const LONG WindowStyle = ::GetWindowLong(m_Handle, GWL_STYLE);
			const LONG WindowExStyle = ::GetWindowLong(m_Handle, GWL_EXSTYLE);

			RECT BorderRect = {0, 0, 0, 0};
			::AdjustWindowRectEx(&BorderRect, WindowStyle, false, WindowExStyle);

			return BorderRect;
		}

		DWORD GetWindowStyle()
		{
			DWORD result = WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

			if (WindowState == WindowState::Fullscreen)
			{
				result |= WS_POPUP;
			}

			result |= WS_SYSMENU | WS_MINIMIZEBOX;

			if (Decorated)
			{
				result |= WS_CAPTION;
			}

			if (Resizable)
			{
				result |= WS_MAXIMIZEBOX | WS_THICKFRAME;
			}

			if (WindowState == WindowState::Maximized)
			{
				result |= WS_MAXIMIZE;
			}

			return result;
		}

		DWORD GetWindowExStyle()
		{
			DWORD result = WS_EX_APPWINDOW | WS_EX_ACCEPTFILES | WS_EX_CLIENTEDGE | WS_EX_TRANSPARENT;

			if (WindowState == WindowState::Fullscreen || Topmost)
			{
				result |= WS_EX_TOPMOST | WS_EX_WINDOWEDGE;
			}

			return result;
		}

		static LRESULT CALLBACK MessageRouter(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
		{
			NTWindow *ntWindow = 0;

			if (uMsg == WM_NCCREATE)
			{
				CREATESTRUCT *pCreate = ReinterpretCastTo<CREATESTRUCT *>(lParam);
				ntWindow = ReinterpretCastTo<NTWindow *>(pCreate->lpCreateParams);
				::SetWindowLongPtr(hWnd, GWLP_USERDATA, ReinterpretCastTo<LONG_PTR>(ntWindow));
				ntWindow->m_Handle = hWnd;
			}
			else
			{
				ntWindow = ReinterpretCastTo<NTWindow *>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
			}

			if (ntWindow)
			{
				return ntWindow->WindowProcedure(hWnd, uMsg, wParam, lParam);
			}
			else
			{
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

				RECT BorderRect = {0, 0, 0, 0};
				BorderRect = GetWindowBorderRect();

				xPos += BorderRect.left;
				yPos += BorderRect.top;

				PositionEventArgs e = PositionEventArgs({CastTo<float>(xPos), CastTo<float>(yPos)});
				this->evtOnPositionChanging(e);
			}
			break;
			case WM_SIZE:
			{
				uint32 width = LOWORD(lParam);
				uint32 height = HIWORD(lParam);

				RECT BorderRect = {0, 0, 0, 0};
				BorderRect = GetWindowBorderRect();

				width += BorderRect.right - BorderRect.left;
				height += BorderRect.bottom - BorderRect.top;

				SizeEventArgs e = SizeEventArgs({CastTo<float>(width), CastTo<float>(height)});
				this->evtOnResized(e);
			}
			break;
			case WM_WINDOWPOSCHANGING:
			{
				RECT BorderRect = {0, 0, 0, 0};
				BorderRect = GetWindowBorderRect();

				WINDOWPOS *wndPosData = (WINDOWPOS *)lParam;
				if ((wndPosData->x != 0 || wndPosData->y != 0) && ((wndPosData->flags & SWP_NOMOVE) == 0))
				{
					Position = {CastTo<float>(wndPosData->x), CastTo<float>(wndPosData->y)};
				}

				if ((wndPosData->cx != 0 || wndPosData->cy != 0) && ((wndPosData->flags & SWP_NOSIZE) == 0))
				{
					Size = {CastTo<float>(wndPosData->cx), CastTo<float>(wndPosData->cy)};
				}
			}
			break;
			case WM_CLOSE:
			{
				CancelEventArgs e = CancelEventArgs(false);
				this->evtOnClosing(e);
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
			String ID = Types::ToString(Types::GetObjectId(this));
			WideString wndId = WideString(ID.begin(), ID.end());

			WideString className = L"NTWindow_" + wndId;

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

				if ((Size->X != screenWidth) && (Size->Y != screenHeight))
				{
					if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
					{
						Log::GetFrameworkLog().Warning("Failed to switch to fullscreen window !");
						WindowState = WindowState::Maximized;
					}
				}
			}

			int wndPosX = CastTo<int>(Position->X);
			int wndPosY = CastTo<int>(Position->Y);
			int wndWidth = CastTo<int>(Size->X);
			int wndHeight = CastTo<int>(Size->Y);

			RECT wndRect = {0, 0, 0, 0};
			AdjustWindowRectEx(&wndRect, GetWindowStyle(), FALSE, GetWindowExStyle());

			wndPosX += wndRect.left;
			wndPosY += wndRect.top;

			wndWidth += wndRect.right - wndRect.left;
			wndHeight += wndRect.bottom - wndRect.top;

			m_Handle = CreateWindowEx(GetWindowExStyle(), WINDOW_CLASS, WideString(Title->begin(), Title->end()).c_str(), GetWindowStyle(),
									  CW_USEDEFAULT, CW_USEDEFAULT, wndWidth, wndHeight,
									  NULL, NULL, GetModuleHandle(0), this);

			RECT rect = {0};
			if (GetWindowRect(m_Handle, &rect))
			{
				Position = {CastTo<float>(rect.left), CastTo<float>(rect.top)};
			}

			::SetWindowLongPtr(m_Handle, GWLP_USERDATA, ReinterpretCastTo<LONG_PTR>(this));

#if WINVER >= 0x0601
			if (RegisterTouchWindow(m_Handle, 0) == false)
			{
				Debug::Log::GetFrameworkLog().Warning("Failed to register touch window !");
			}
#endif

			if (!m_Handle)
			{
				throw RuntimeException("Failed to create a Win32 window !");
			}
		}

	protected:
		virtual void OnTitleChanged(const String &newValue) { SetWindowText(m_Handle, WideString(newValue.begin(), newValue.end()).c_str()); }
		virtual void OnPositionChanged(const Maths::Vector2 &newValue)
		{
			RECT BorderRect = {0, 0, 0, 0};
			BorderRect = GetWindowBorderRect();

			int X = (int)newValue.X + BorderRect.left;
			int Y = (int)newValue.Y + BorderRect.top;

			SetWindowPos(m_Handle, HWND_NOTOPMOST, CastTo<int>(newValue.X), CastTo<int>(newValue.Y), 0, 0, SWP_NOZORDER | SWP_NOACTIVATE | SWP_NOSENDCHANGING | SWP_NOSIZE | SWP_ASYNCWINDOWPOS);
		}

		virtual void OnSizeChanged(const Maths::Vector2 &newValue)
		{
			RECT BorderRect = {0, 0, 0, 0};
			BorderRect = GetWindowBorderRect();

			int width = CastTo<int>(newValue.X);
			int height = CastTo<int>(newValue.Y);

			width += BorderRect.right - BorderRect.left;
			height += BorderRect.bottom - BorderRect.top;

			SetWindowPos(m_Handle, HWND_NOTOPMOST, 0, 0, CastTo<int>(newValue.X), CastTo<int>(newValue.Y), SWP_NOZORDER | SWP_NOACTIVATE | SWP_NOSENDCHANGING | SWP_NOMOVE | SWP_ASYNCWINDOWPOS);
		}

	public:
		virtual void Show();
		virtual void Hide();
		virtual void Close();
		virtual void Focus();
		virtual void Update();

	private:
		MSG m_msgHandler = {0};
	}; // namespace Pictura::UI
} // namespace Pictura::UI