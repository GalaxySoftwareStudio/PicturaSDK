#include "FrameworkLoader.h"
#include "PicturaDemo.h"

class DemoApplication : public Application
{
public:
	UI::Window MainWindow;

public:
	DemoApplication()
	{
		Log::SetLogLevel(Log::LogLevel::All);
		ApplicationStart += EventHandler::Bind(&DemoApplication::DemoApplication_ApplicationStart, this);
		ApplicationClose += EventHandler::Bind(&DemoApplication::DemoApplication_ApplicationClose, this);
	}

	~DemoApplication()
	{

	}

	void DemoApplication_ApplicationStart(StartupEventArgs& e)
	{
		GetApplicationLog().Info("ApplicationThreadID = " + Threading::Thread::CurrentThread()->ThreadName);
		GetApplicationLog().Info("Application is running !");

		MainWindow->Closing += EventHandler::Bind(&DemoApplication::MainWindow_Closing, this);
		MainWindow->Title = "MainWindow";
		MainWindow->Show();
	}

	void MainWindow_Closing(CancelEventArgs& e)
	{
		String previousTitle = MainWindow->Title;
		MainWindow->Title = "You are about to quit the application !";
		if (MessageBox(NULL, L"Really quit?", L"My application", MB_OKCANCEL) == IDOK)
		{
			Exit();
			return;
		}
		
		MainWindow->Title = "MainWindow";
		e.Cancel = true;
	}

	void DemoApplication_ApplicationClose(EventArgs& e)
	{
		GetApplicationLog().Info("Application closed!");
	}
};
APPLICATION(DemoApplication)