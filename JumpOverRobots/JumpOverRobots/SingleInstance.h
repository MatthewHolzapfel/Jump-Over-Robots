#pragma once
#define APPLICATION_INSTANCE_MUTEX_NAME "{SpiralEngineTesting}"
HANDLE gameRunning;

bool singleInstance(LPCWSTR spiralEngine)
{
	gameRunning = CreateMutex(NULL, true, spiralEngine);

	HWND window = FindWindow(spiralEngine, NULL);

	if (window)
	{
		return false;
	}
	return true;
}