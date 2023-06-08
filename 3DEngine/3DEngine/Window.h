#pragma once
#include <Windows.h>

class Window
{
public:
	Window();
	//Initialize window
	bool Init();
	bool Broadcast();
	//Release the window
	bool Release();
	bool isRunning();
	
	RECT GetClientWindowRect();
	void setHWND(HWND hwnd);
	//EVENTS
	virtual void OnCreate();
	virtual void OnUpdate();
	virtual void OnDestroy();

	~Window();

protected:
	HWND m_hwnd;
	bool m_is_running;
};

