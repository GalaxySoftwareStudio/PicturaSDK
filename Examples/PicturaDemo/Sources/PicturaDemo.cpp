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

        MainWindow->Title = "MainWindow [WindowState = " + wndState + "]";
    }

    void DemoApplication_ApplicationClose(EventArgs &e)
    {
        GetApplicationLog().Info("Application closed!");
    }
};
APPLICATION(DemoApplication)