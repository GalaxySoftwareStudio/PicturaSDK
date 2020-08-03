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

		auto* wnd = new UI::Window();
		wnd->Show();

		Exit();
	}

	void DemoApplication_ApplicationClose(EventArgs& e)
	{
		GetApplicationLog().Info("Application closed!");
	}
};
APPLICATION(DemoApplication)