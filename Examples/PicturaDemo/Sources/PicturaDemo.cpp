#include "FrameworkLoader.h"
#include "PicturaDemo.h"

class DemoApplication : public Application
{
public:
	DemoApplication()
	{
		ApplicationStart += EventHandler::Bind(&DemoApplication::DemoApplication_ApplicationStart, this);
		ApplicationClose += EventHandler::Bind(&DemoApplication::DemoApplication_ApplicationClose, this);
	}

	void DemoApplication_ApplicationStart(StartupEventArgs& e)
	{
		GetApplicationLog().Info("ApplicationThreadID = " + Threading::Thread::CurrentThread()->ThreadName);
		GetApplicationLog().Info("Application is running !");
		GetApplicationLog().Debug("Something happened...");
		GetApplicationLog().Warning("Tried to parse an invalid data !");
		GetApplicationLog().Error("Connection failed !");
		GetApplicationLog().Fatal("FSException: File not found!");

		auto *wnd = new UI::Window();

		Console::Pause();

		Exit();
	}

	void DemoApplication_ApplicationClose(EventArgs& e)
	{
		GetApplicationLog().Info("Application closed!");
	}
};
APPLICATION(DemoApplication)