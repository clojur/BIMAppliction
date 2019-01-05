// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.
#include "TestProgram.h"
#include "Modules/ModuleManager.h"
#include "LaunchEngineLoop.h"
#include "FRunnableTestThread.h"
#include "RequiredProgramMainCPPInclude.h"


#define LOCTEXT_NAMESPACE "TestProgram"

IMPLEMENT_APPLICATION(TestProgram, "TestProgram");

INT32_MAIN_INT32_ARGC_TCHAR_ARGV()
{
	FEngineLoop MyEngingLoop;
	MyEngingLoop.PreInit(ArgC, ArgV);
	//UE_LOG(LogTestProgram, Display, TEXT("Hello World\n"));
	//system("pause");

	//线程demo
	FRunnableThread::Create(new FRunnableTestThread(0),TEXT("TestThread0"));
	FRunnableThread::Create(new FRunnableTestThread(1), TEXT("TestThread1"));
	FRunnableThread::Create(new FRunnableTestThread(2), TEXT("TestThread2"));

	//Task Graph
	//TGraphTask<FShowcaseTask>::CreateTask(NULL,ENamedThreads::GameThread).ConstructAndDispatchWhenReady(0);
	//TGraphTask<FShowcaseTask>::CreateTask(NULL, ENamedThreads::GameThread).ConstructAndDispatchWhenReady(1);
	//TGraphTask<FShowcaseTask>::CreateTask(NULL, ENamedThreads::GameThread).ConstructAndDispatchWhenReady(2);

	//slateDemo
	FSlateApplication::InitializeAsStandaloneApplication(GetStandardStandaloneRenderer());
	TSharedPtr<SWindow> MainWindow = SNew(SWindow)
		.Title(LOCTEXT("MainWindow_Title", "UE4，盒盒了！"))
		.ScreenPosition(FVector2D(800, 600))
		.ClientSize(FVector2D(800, 600))
		.AutoCenter(EAutoCenter::None);


	FSlateApplication::Get().AddWindow(MainWindow.ToSharedRef());

	while (!GIsRequestingExit)
	{
		FSlateApplication::Get().Tick();
		FSlateApplication::Get().PumpMessages();
	}

	FSlateApplication::Shutdown();

	return 0;
}


//int WINAPI	WinMain(
//	_In_ HINSTANCE hInInstance,
//	_In_opt_ HINSTANCE hPrevInstance,
//	_In_  LPSTR,
//	_In_ int nCmdShow
//)
//{
//	FEngineLoop MyEngingLoop;
//	MyEngingLoop.PreInit(GetCommandLineW());
//	FSlateApplication::InitializeAsStandaloneApplication(GetStandardStandaloneRenderer());
//	TSharedPtr<SWindow> MainWindow = SNew(SWindow)
//		.Title(LOCTEXT("MainWindow_Title", "UE4，盒盒了！"))
//		.ScreenPosition(FVector2D(800, 600))
//		.ClientSize(FVector2D(800, 600))
//		.AutoCenter(EAutoCenter::None);
//
//
//	FSlateApplication::Get().AddWindow(MainWindow.ToSharedRef());
//
//	while (!GIsRequestingExit)
//	{
//		FSlateApplication::Get().Tick();
//		FSlateApplication::Get().PumpMessages();
//	}
//
//	FSlateApplication::Shutdown();
//
//	return 0;
//}

#undef LOCTEXT_NAMESPACE