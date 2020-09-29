#pragma once
#include "Core/CoreFramework.h"
#include "Core/System/Runtime/Runtime.h"
#include "Core/Threading/Thread.h"
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
		Application();
		virtual ~Application()
		{
			Threading::Thread::StopAllThread();
		}

	public:
		void Init(StartupEventArgs& e)
		{
			this->ApplicationThread.reset(new Threading::Thread(&Application::Run, this, e));
		}
		void Run(StartupEventArgs e);
		void Exit();
		bool ShouldQuit() { return m_isQuitting; }
		Debug::Log& GetApplicationLog() { return *m_ApplicationLog; }

	public:
		static String GetFrameworkConfiguration()
		{
#ifdef PICTURA_DEBUG
			return "DEBUG";
#else
			return "RELEASE";
#endif
		}

		static String GetFrameworkVersion()
		{
			return "0.1";
		}

		static String GetWorkingDirectory()
		{
			return std::filesystem::current_path().string();
		}

	public:
		event(StartupEventArgs, ApplicationStart);
		event(EventArgs, ApplicationClose);

	public:
		Vector<String> Arguments;
		UniquePtr<Threading::Thread> ApplicationThread;

		static Application* CurrentApplication;

	private:
		#ifdef PLATFORM_WINDOWS
			MSG m_ApplicationMessage = { 0 };
		#endif

		SharedPtr<Debug::Log> m_ApplicationLog = Types::MakeShared<Debug::Log>("Application");
		bool m_isQuitting = false;
	};

	Application* InitApplication();
}

