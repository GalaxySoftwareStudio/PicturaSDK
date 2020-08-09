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
		while (!m_isQuitting) { }
		this->OnApplicationClose(*Events::EmptyEventArgs);
		ApplicationThread.reset();
	}

	void Application::Exit()
	{
		if (!m_isQuitting)
		{
			m_isQuitting = true;
		}
	}
}