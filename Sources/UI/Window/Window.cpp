#include "PicturaPCH.h"
#include "Window.h"

namespace Pictura::UI
{
    Window::Window()
    {
        m_wndThread = Types::MakeUnique<Threading::Thread>(&Window::CreateNativeWindow, this);
        Threading::Thread::LockThread();
    }

    Window::~Window()
    {
        
    }

    void Window::CreateNativeWindow()
    {
#if defined(PLATFORM_WINDOWS)
        m_WindowInstance = new NTWindow();
#elif defined(PLATFORM_LINUX)
        m_WindowInstance = new X11Window();
#elif defined(PLATFORM_MACOS)
        m_WindowInstance = new CocoaWindow();
#endif
        Threading::Thread::UnlockThread();
        NullWindow::WindowList.insert(Pair<NativeHandleType, NullWindow *>(m_WindowInstance->GetHandle(), m_WindowInstance));

        m_WindowInstance->OwnerPtr = this;
        m_WindowInstance->Update();
    }
}