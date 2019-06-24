// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.
#include "TestProgram.h"

#include "FRunnableTestThread.h"

#include "Frame/RootWindowLocation.h"
#include "Framework/Notifications/NotificationManager.h"
#include "Modules/ModuleManager.h"
#include "LaunchEngineLoop.h"
#include "RequiredProgramMainCPPInclude.h"


#define LOCTEXT_NAMESPACE "TestProgram"

IMPLEMENT_APPLICATION(TestProgram, "TestProgram");

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
TSharedRef<SDockTab> SpawnMainTab(const FSpawnTabArgs& Args, FName TabIdentifier)
{
	return SNew(SDockTab)
		.Label(LOCTEXT("MainTabTabLabel", "工程XX"))
		.Clipping(EWidgetClipping::ClipToBounds)
		.TabRole(ETabRole::MajorTab)
		.ToolTip
		(
			SNew(SToolTip)
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.Padding(2.0f)
				[
					SNew(SImage)
					.Image(FCoreStyle::Get().GetBrush(TEXT("DefaultAppIcon")))
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.VAlign(VAlign_Center)
				[
					SNew(STextBlock)
					.Text((LOCTEXT("DockTabTip", "我是STextBlock\n在我前面的是SImage\n我们一起构成了SToolTip作为DockTab的ToolTip!")))
				]
			]
		);
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

INT32_MAIN_INT32_ARGC_TCHAR_ARGV()
{
	FEngineLoop MyEngingLoop;
	MyEngingLoop.PreInit(ArgC, ArgV);
	FSlateApplication::InitializeAsStandaloneApplication(GetStandardStandaloneRenderer());

	FApp::SetProjectName(TEXT("BIM设计系统"));
	FRootWindowLocation DefaultWindowLocation;
	DefaultWindowLocation.InitiallyMaximized = false;
	//UE_LOG(LogTestProgram, Display, TEXT("Hello World\n"));
	//system("pause");

	//线程demo
	//FRunnableThread::Create(new FRunnableTestThread(0),TEXT("TestThread0"));
	//FRunnableThread::Create(new FRunnableTestThread(1), TEXT("TestThread1"));
	//FRunnableThread::Create(new FRunnableTestThread(2), TEXT("TestThread2"));

	//Task Graph
	//TGraphTask<FShowcaseTask>::CreateTask(NULL,ENamedThreads::GameThread).ConstructAndDispatchWhenReady(0);
	//TGraphTask<FShowcaseTask>::CreateTask(NULL, ENamedThreads::GameThread).ConstructAndDispatchWhenReady(1);
	//TGraphTask<FShowcaseTask>::CreateTask(NULL, ENamedThreads::GameThread).ConstructAndDispatchWhenReady(2);

	//slateDemo
	FString str = FString(FApp::GetProjectName());
	FText WindowTitle= FText::FromString(str);
	
	TSharedPtr<SWindow> MainWindow = SNew(SWindow)
		.AutoCenter(EAutoCenter::None)
		.Title(WindowTitle)
		.IsInitiallyMaximized(DefaultWindowLocation.InitiallyMaximized)
		.ScreenPosition(DefaultWindowLocation.ScreenPosition)
		.ClientSize(DefaultWindowLocation.WindowSize)
		.CreateTitleBar(false)
		.SizingRule(ESizingRule::UserSized)
		.SupportsMaximize(true)
		.SupportsMinimize(true);

	FGlobalTabmanager::Get()->RegisterTabSpawner("MainTab", FOnSpawnTab::CreateStatic(&SpawnMainTab,FName("MainTab")));
	TSharedRef<FTabManager::FLayout> LoadedLayout = FTabManager::NewLayout("BIM_Layout")
		->AddArea
		(
			// level editor window
			FTabManager::NewPrimaryArea()
			->Split
			(
				FTabManager::NewStack()
				->SetSizeCoefficient(2.0f)
				->AddTab("MainTab", ETabState::OpenedTab)
			)
		);

	TSharedPtr<SWidget> MainFrameContent = FGlobalTabmanager::Get()->RestoreFrom(LoadedLayout, MainWindow, true);

	FSlateApplication::Get().AddWindow(MainWindow.ToSharedRef()/*, false*/);
	FGlobalTabmanager::Get()->SetRootWindow(MainWindow.ToSharedRef());
	FSlateNotificationManager::Get().SetRootWindow(MainWindow.ToSharedRef());
	MainWindow->SetContent(MainFrameContent.ToSharedRef());
	TSharedPtr<SDockTab> MainTab= FGlobalTabmanager::Get()->InvokeTab(FTabId("MainTab"));
	FGlobalTabmanager::Get()->SetMainTab(MainTab.ToSharedRef());
	FGlobalTabmanager::Get()->SetApplicationTitle(WindowTitle);

	while (!GIsRequestingExit)
	{
		FTaskGraphInterface::Get().ProcessThreadUntilIdle(ENamedThreads::GameThread);
		FStats::AdvanceFrame(false);
		FTicker::GetCoreTicker().Tick(FApp::GetDeltaTime());
		FSlateApplication::Get().PumpMessages();
		FSlateApplication::Get().Tick();
		FPlatformProcess::Sleep(0);
	}

	FModuleManager::Get().UnloadModulesAtShutdown();
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