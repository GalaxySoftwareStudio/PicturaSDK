#include "PicturaPCH.h"
#include "Application.h"

namespace Pictura::Runtime
{
	Application* Application::CurrentApplication = nullptr;

	Application::Application()
	{
		Debug::RuntimeDebug::Assert(CurrentApplication, "Application was already initialized !");

		CurrentApplication = this;
		ApplicationCloseBehavior = CloseBehavior::OnRequestExit;
	}

	void Application::Run(StartupEventArgs e)
	{
		this->OnApplicationStart(e);
		while (!m_isQuitting) {}
		this->OnApplicationClose(*EmptyEventArgs);
		delete ApplicationThread.release();
	}

	void Application::Exit()
	{
		if (!m_isQuitting)
		{
			ApplicationCloseBehavior = CloseBehavior::OnRequestExit;

			m_isQuitting = true;
		}
	}
}