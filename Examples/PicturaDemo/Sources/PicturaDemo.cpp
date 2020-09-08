#include "PicturaDemo.h"
#include "FrameworkLoader.h"

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

    void DemoApplication_ApplicationStart(StartupEventArgs &e)
    {
        GetApplicationLog().Info("ApplicationThreadID = " + Threading::Thread::CurrentThread()->ThreadName);
        GetApplicationLog().Info("Application is running !");

        MainWindow->Closing += EventHandler::Bind(&DemoApplication::MainWindow_Closing, this);
        MainWindow->StateChanged += EventHandler::Bind(&DemoApplication::MainWindow_StateChanged, this);
        MainWindow->Title = "MainWindow";
        MainWindow->Show();

        Threading::Thread::Delay(2000);
        MainWindow->WindowState = UI::WindowState::Fullscreen;
        
        Threading::Thread::Delay(4000);
        MainWindow->WindowState = UI::WindowState::Normal;

        GetApplicationLog().Success("WindowState chain state complete !");
    }

    void MainWindow_Closing(CancelEventArgs &e)
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

    void MainWindow_StateChanged(EventArgs &e)
    {
        String wndState = "UnknownState";
        switch (MainWindow->WindowState)
        {
            case UI::WindowState::Normal:
                wndState = "Normal";
                break;
            case UI::WindowState::Minimized:
                wndState = "Minimized";
                break;
            case UI::WindowState::Maximized:
                wndState = "Maximized";
                break;
            case UI::WindowState::Fullscreen:
                wndState = "Fullscreen";
                break;
            default:
                String wndState = "UnknownState";
                break;
        }

        MainWindow->Title = "MainWindow [" + wndState + "]";
    }

    void DemoApplication_ApplicationClose(EventArgs &e)
    {
        GetApplicationLog().Info("Application closed!");
    }
};
APPLICATION(DemoApplication)