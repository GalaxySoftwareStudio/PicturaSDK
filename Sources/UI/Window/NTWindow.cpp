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
		//TODO : [IMPORTANT] Create each window in a separate thread
		Debug::Log::GetFrameworkLog().Info("Creating Win32 Window...");
		m_Handle = SetupWindow();
		SetWindowLongPtr((HWND)m_Handle, GWLP_USERDATA, (LONG_PTR)this);
	}

	NTWindow::~NTWindow()
	{
		Debug::Log::GetFrameworkLog().Info("Destroying Win32 Window...");
	}

	void NTWindow::Show()
	{
		ShowWindow((HWND)m_Handle, SW_SHOW);
		SetForegroundWindow((HWND)m_Handle);
		SetFocus((HWND)m_Handle);
		SetWindowText((HWND)m_Handle, WideString(Title.begin(), Title.end()).c_str());
	}

	void NTWindow::Hide()
	{
		ShowWindow((HWND)m_Handle, SW_HIDE);
		throw NotImplementedException();
	}

	void NTWindow::Close()
	{
		NullWindow::Close();
		SendMessage((HWND)m_Handle, WM_SYSCOMMAND, SC_CLOSE, 0);
	}

	void NTWindow::Focus()
	{
		throw NotImplementedException();
	}
}