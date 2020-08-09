#include "PicturaPCH.h"
#include "NTWindow.h"
#include "Core/System/Runtime/Runtime.h"

#ifdef PLATFORM_WINDOWS
extern "C" {
	__declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
	__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}
#endif

namespace Pictura::UI
{
	NTWindow::NTWindow()
	{
		Debug::Log::GetFrameworkLog().Info("Creating Win32 Window...");
		SetupWindow();
	}

	NTWindow::~NTWindow()
	{
		Debug::Log::GetFrameworkLog().Info("Destroying Win32 Window...");
		isActive = false;
	}

	void NTWindow::Show()
	{
		ShowWindow(m_Handle, SW_SHOW);
		SetForegroundWindow(m_Handle);
		SetFocus(m_Handle);
		SetWindowText(m_Handle, WideString(Title.begin(), Title.end()).c_str());
		Shown(*EmptyEventArgs);
	}

	void NTWindow::Update()
	{
		isActive = true;
		while (isActive)
		{
			if (PeekMessage(&m_msgHandler, m_Handle, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&m_msgHandler);
				DispatchMessage(&m_msgHandler);
			}
		}
	}

	void NTWindow::Hide()
	{
		ShowWindow(m_Handle, SW_HIDE);
	}

	void NTWindow::Close()
	{
		SendMessage(m_Handle, WM_SYSCOMMAND, SC_CLOSE, 0);
	}

	void NTWindow::Focus()
	{
		throw NotImplementedException();
	}
}