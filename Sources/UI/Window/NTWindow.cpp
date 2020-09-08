#include "PicturaPCH.h"
#include "NTWindow.h"
#include "Core/System/Runtime/Runtime.h"

#ifdef PLATFORM_WINDOWS
extern "C"
{
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
        SetWindowText(m_Handle, WideString(Title->begin(), Title->end()).c_str());

        RECT rect = {0};
        if (GetWindowRect(m_Handle, &rect))
        {
            Position = {CastTo<float>(rect.left), CastTo<float>(rect.top)};
        }

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

    MessageBoxResult NTWindow::ShowMessageBox(WideString Message, WideString Title, MessageBoxIcon Icons, MessageBoxButtons Buttons)
    {
        return CastTo<MessageBoxResult>(Runtime::NTRuntime::NTMessageBox(m_Handle, Message.c_str(), Title.c_str(), ((long)Icons | (long)Buttons)));
    }

    void NTWindow::SetFullscreen(bool value)
    {
        int scrWidth = GetSystemMetrics(SM_CXSCREEN);
        int scrHeight = GetSystemMetrics(SM_CYSCREEN);

        DEVMODE fullscreenSettings;
        memset(&fullscreenSettings, 0, sizeof(fullscreenSettings));
        fullscreenSettings.dmSize = sizeof(fullscreenSettings);
        fullscreenSettings.dmPelsWidth = scrWidth;
        fullscreenSettings.dmPelsHeight = scrHeight;
        fullscreenSettings.dmBitsPerPel = 32;
        fullscreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY;

        if (EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &fullscreenSettings) == 0)
        {
            Debug::Log::GetFrameworkLog().Warning("Failed to change fullscreen state of [" + (String)this->Title + "] !");
            return;
        }

        if (value)
        {
            SetWindowLongPtr(m_Handle, GWL_EXSTYLE, WS_EX_APPWINDOW | WS_EX_TOPMOST);
            SetWindowLongPtr(m_Handle, GWL_STYLE, WS_POPUP | WS_VISIBLE);
            SetWindowPos(m_Handle, HWND_TOP, 0, 0, scrWidth, scrHeight, SWP_SHOWWINDOW);
            if (ChangeDisplaySettings(&fullscreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
            {
                Debug::Log::GetFrameworkLog().Warning("Failed to change fullscreen state of [" + (String)this->Title + "] !");
                return;
            }

            ShowWindow(m_Handle, SW_MAXIMIZE);
            this->WindowState.Set(WindowState::Fullscreen);
        }
        else
        {
            SetWindowLongPtr(m_Handle, GWL_EXSTYLE, WS_EX_LEFT);
            SetWindowLongPtr(m_Handle, GWL_STYLE, WS_OVERLAPPEDWINDOW | WS_VISIBLE);
            if (ChangeDisplaySettings(NULL, CDS_RESET) != DISP_CHANGE_SUCCESSFUL)
            {
                Debug::Log::GetFrameworkLog().Warning("Failed to change fullscreen state of [" + (String)this->Title + "] !");
                return;
            }

            SetWindowPos(m_Handle, HWND_NOTOPMOST, 32, 16, CastTo<int>(Size->X - 64), CastTo<int>(Size->Y - 64), SWP_SHOWWINDOW);
            ShowWindow(m_Handle, SW_MAXIMIZE);
        }
    }
} // namespace Pictura::UI