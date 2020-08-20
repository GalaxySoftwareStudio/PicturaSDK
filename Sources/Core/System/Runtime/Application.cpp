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
		this->evtOnApplicationStart(e);
		while (!m_isQuitting) { }
		this->evtOnApplicationClose(*Events::EmptyEventArgs);
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