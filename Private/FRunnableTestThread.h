#pragma once
#include "TestProgram.h"
#include "HAL/Runnable.h"
#include "Async/TaskGraphInterfaces.h"
#include "RequiredProgramMainCPPInclude.h"

#define LOCTEXT_NAMESPACE "TestProgram"
//线程DEMO
class FRunnableTestThread :public FRunnable
{
public:
	FRunnableTestThread(int16 _Index) :Index(_Index) {}
	virtual bool Init()override;
	virtual uint32 Run()override;
	virtual void Exit()override;
private:
	int16 Index;
};

//Task Graph
class FShowcaseTask
{
public:
	FShowcaseTask(int16 _Index) :Index(_Index) {}
	static const TCHAR* GetTaskName()
	{
		return TEXT("FShowcaseTask");
	}
	FORCEINLINE static TStatId GetStatId()
	{
		RETURN_QUICK_DECLARE_CYCLE_STAT(FShowcaseTask,STATGROUP_TaskGraphTasks);
	}

	static ENamedThreads::Type GetDesiredThread()
	{
		return ENamedThreads::AnyThread;
	}

	static ESubsequentsMode::Type GetSubsequentsMode()
	{
		return ESubsequentsMode::TrackSubsequents;
	}

	void DoTask(ENamedThreads::Type CurrentThread, const FGraphEventRef& MyCompletionGraphEvent)
	{
		UE_LOG(LogTestProgram, Display, TEXT("Thread %d Run:1"), Index);
		FWindowsPlatformProcess::Sleep(10.0);
		UE_LOG(LogTestProgram, Display, TEXT("Thread %d Run:2"), Index);
		FWindowsPlatformProcess::Sleep(10.0);
		UE_LOG(LogTestProgram, Display, TEXT("Thread %d Run:3"), Index);
		FWindowsPlatformProcess::Sleep(10.0);
	}
private:
	int16 Index;
};

#undef LOCTEXT_NAMESPACE