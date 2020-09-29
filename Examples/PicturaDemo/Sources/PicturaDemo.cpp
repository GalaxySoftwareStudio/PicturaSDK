#include "PicturaDemo.h"
#include "FrameworkLoader.h"

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

    void DemoApplication_ApplicationStart(StartupEventArgs &e)
    {
        GetApplicationLog().Info("Application path = " + e.Arguments[0]);
        GetApplicationLog().Info("ApplicationThreadID = " + Threading::Thread::CurrentThread()->ThreadName);
        GetApplicationLog().Info("Application is running !");

        MainWindow->Closing += EventHandler::Bind(&DemoApplication::MainWindow_Closing, this);
        MainWindow->StateChanged += EventHandler::Bind(&DemoApplication::MainWindow_StateChanged, this);
        MainWindow->Title = "MainWindow";
        MainWindow->Show();

        //AnotherWindow->Show();
    }

    void MainWindow_Closing(CancelEventArgs &e)
    {
        if (MainWindow->ShowMessageBox(L"Really quit?", L"You're about to quit the application", UI::MessageBoxIcon::Info, UI::MessageBoxButtons::OkCancel) == UI::MessageBoxResult::Ok)
        {
            Exit();
            return;
        }

        e.Cancel = true;
    }

    void MainWindow_StateChanged(EventArgs &e)
    {
        MainWindow->Title = "MainWindow [WindowState = " + MainWindow->WindowStateToString(MainWindow->WindowState) + "]";
    }

    void DemoApplication_ApplicationClose(EventArgs &e)
    {
        GetApplicationLog().Info("Application closed!");
    }
};
APPLICATION(DemoApplication)