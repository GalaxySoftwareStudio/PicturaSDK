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
		AnotherWindow->Resized += EventHandler::Bind(&DemoApplication::AnotherWindow_Resized, this);
		AnotherWindow->Title = "Another Window";
		GetApplicationLog().Info("wnd = " + (String)AnotherWindow->Title);
		AnotherWindow->Show();

		Threading::Thread::Delay(3500);

		AnotherWindow->Position = { 500, 500 };
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

	void AnotherWindow_Resized(SizeEventArgs& e)
	{
		AnotherWindow->Title = "AnotherWindow [X=" + Types::ToString(AnotherWindow->Position->X) + " | Y=" + Types::ToString(AnotherWindow->Position->Y) + "]" + " - [Width=" + Types::ToString(AnotherWindow->Size->X) + " | Height=" + Types::ToString(AnotherWindow->Size->Y) + "]";
	}

	void AnotherWindow_PositionChanged(PositionEventArgs& e)
	{
		AnotherWindow->Title = "AnotherWindow [X=" + Types::ToString(AnotherWindow->Position->X) + " | Y=" + Types::ToString(AnotherWindow->Position->Y) + "]" + " - [Width=" + Types::ToString(AnotherWindow->Size->X) + " | Height=" + Types::ToString(AnotherWindow->Size->Y) + "]";
	}

	void DemoApplication_ApplicationClose(EventArgs& e)
	{
		GetApplicationLog().Info("Application closed!");
	}
};
APPLICATION(DemoApplication)