#include "FrameworkLoader.h"
#include "PicturaDemo.h"

class DemoApplication : public Application
{
public:
	UI::Window MainWindow;
	UI::Window AnotherWindow;

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

		AnotherWindow->PositionChanging += EventHandler::Bind(&DemoApplication::AnotherWindow_PositionChanged, this);
		AnotherWindow->Title = "Another Window";
		AnotherWindow->Show();
	}

	void MainWindow_Closing(CancelEventArgs& e)
	{
		if (MessageBox(NULL, L"Really quit?", L"My application", MB_OKCANCEL) == IDOK)
		{
			Exit();
			return;
		}
		
		e.Cancel = true;
	}

	void AnotherWindow_PositionChanged(PositionEventArgs& e)
	{
		GetApplicationLog().Info("AnotherWindow is moving [X=" + Types::ToString(e.Position.X) + " Y=" + Types::ToString(e.Position.Y) + "]");
	}

	void DemoApplication_ApplicationClose(EventArgs& e)
	{
		GetApplicationLog().Info("Application closed!");
	}
};
APPLICATION(DemoApplication)