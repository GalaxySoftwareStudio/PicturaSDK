#pragma once
#include "Core/CoreFramework.h"
#include "Core/System/Runtime/Runtime.h"
#include "Threading/Thread.h"
#include "Core/Events/Event.h"
#include "Core/Events/EventArgs/EventArgs.h"

namespace Pictura::Runtime
{
	class StartupEventArgs : public Events::EventArgs
	{
	public:
		StartupEventArgs(Vector<String> Args) : Arguments(Args) { }
		~StartupEventArgs() { }

	public:
		Vector<String> Arguments;
	};

	class Application
	{
	public:
		enum class CloseBehavior
		{
			OnMainWindowClosed,
			OnAllWindowClosed,
			OnRequestExit
		};

	public:
		Application();
		virtual ~Application() { }

	public:
		void Run(StartupEventArgs e);
		void Exit();

	public:
		Debug::Log& GetApplicationLog() { return *m_ApplicationLog; }
		void Init(StartupEventArgs& e) { this->ApplicationThread.reset(new Threading::Thread(&Application::Run, this, e)); }

	public:
		event(StartupEventArgs, ApplicationStart);
		event(EventArgs, ApplicationClose);

	public:
		UniquePtr<Threading::Thread> ApplicationThread;
		Vector<String> Arguments;
		Application::CloseBehavior ApplicationCloseBehavior;

		static Application* CurrentApplication;

	private:
		UniquePtr<Debug::Log> m_ApplicationLog = Types::MakeUnique<Debug::Log>("Application");
		bool m_isQuitting = false;
	};

	Application* InitApplication();
}

