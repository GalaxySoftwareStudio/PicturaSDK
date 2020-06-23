#include "PicturaDemo.h"
#include <stdlib.h>
#include <crtdbg.h> 

int main()
{
	Log::GetFrameworkLog().Info("Application is running !");
	Log::GetFrameworkLog().Debug("Something happened...");
	Log::GetFrameworkLog().Warning("Tried to parse an invalid data !");
	Log::GetFrameworkLog().Error("Connection failed !");
	Log::GetFrameworkLog().Fatal("FSException: File not found!");

	UniquePtr<Log> AppLog = Log::CreateLog("Application");

	AppLog->Debug("Oui");
	Console::Pause();
}