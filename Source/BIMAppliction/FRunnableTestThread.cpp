#include "FRunnableTestThread.h"

bool FRunnableTestThread::Init()
{
	UE_LOG(LogTestProgram, Display, TEXT("Thread %d Init"),Index);
	return true;
}

uint32 FRunnableTestThread::Run()
{
	UE_LOG(LogTestProgram, Display, TEXT("Thread %d Run:1"), Index);
	FWindowsPlatformProcess::Sleep(10.0);
	UE_LOG(LogTestProgram, Display, TEXT("Thread %d Run:2"), Index);
	FWindowsPlatformProcess::Sleep(10.0);
	UE_LOG(LogTestProgram, Display, TEXT("Thread %d Run:3"), Index);
	FWindowsPlatformProcess::Sleep(10.0);
	return 0;
}

void FRunnableTestThread::Exit()
{
	UE_LOG(LogTestProgram, Display, TEXT("Thread %d Exit"), Index);
}