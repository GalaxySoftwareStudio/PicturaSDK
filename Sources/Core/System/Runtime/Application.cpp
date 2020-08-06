#include "PicturaPCH.h"
#include "Application.h"

namespace Pictura::Runtime
{
	Application* Application::CurrentApplication = nullptr;

	Application::Application()
	{
		Debug::RuntimeDebug::Assert(CurrentApplication, "Application was already initialized !");
		CurrentApplication = this;
	}

	void Application::Run(StartupEventArgs e)
	{
		this->OnApplicationStart(e);
		while (!m_isQuitting)
		{
			Update();
		}
		this->OnApplicationClose(*Events::EmptyEventArgs);
		//delete ApplicationThread.release();
	}

	void Application::Update()
	{
		Debug::Log::GetFrameworkLog().Debug("Update application");
#ifdef PLATFORM_WINDOWS
		if (PeekMessage(&m_ApplicationMessage, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&m_ApplicationMessage);
			DispatchMessage(&m_ApplicationMessage);
		}
#endif
		
	}

	void Application::Exit()
	{
		if (!m_isQuitting)
		{
			m_isQuitting = true;
		}
	}
}