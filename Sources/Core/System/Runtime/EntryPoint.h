#pragma once
#include "Core/CoreFramework.h"
#include "Core/System/Runtime/Application.h"

#define APPLICATION(ClassName)\
Pictura::Runtime::Application* Pictura::Runtime::InitApplication()\
{\
	return new ClassName##();\
}

extern Pictura::Runtime::Application* Pictura::Runtime::InitApplication();

void InvalidParameterHandler(const wchar_t* Expression, const wchar_t* Function, const wchar_t* File, uint32 Line, uint64 Reserved)
{
	String ErrorMessage;
	ErrorMessage = "CRT INVALID PARAMETER.\nExpression : " + Pictura::Types::ToString(Expression ? Expression : L"Unknown") + "\nFunction : " + Pictura::Types::ToString(Function ? Function : L"Unknown") + "\nFile : " + Pictura::Types::ToString(File ? File : L"Unknown") + "\nLine : " + Pictura::Types::ToString(Line);
	Pictura::Debug::Log::GetFrameworkLog().Error(ErrorMessage);
	throw Pictura::Exception("FATAL EXCEPTION.");
}

void SetupEnvironment()
{
#ifdef PLATFORM_WINDOWS
	_set_invalid_parameter_handler(InvalidParameterHandler);
	_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE | _CRTDBG_MODE_DEBUG);
	_CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDERR);
	_CrtSetDebugFillThreshold(0);
#else

#endif
}

int main(int argc, char** argv)
{
	SetupEnvironment();
	const Vector<String> args(argv, argv + argc); //Store runtime arguments in a Vector<String>
	auto app = Pictura::Runtime::InitApplication(); //Create new application instance

	app->Arguments = args; //Move args to Application Arguments
	Pictura::Runtime::StartupEventArgs e = Pictura::Runtime::StartupEventArgs(app->Arguments); //Prepare new StartupEventArgs using Application Arguments

	app->Init(e); //Initialize the application thread

	while (app->ApplicationThread) { } //Wait for the application execution to be complete

	delete app; //Free all application ressources
}