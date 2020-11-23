#pragma once
#include<Windows.h>
#include"GameConfiguration.h"
class WindowGame
{
	
	HWND hWnd;
	
	static WindowGame* instance;
public:
	
	static WindowGame* getInstance();
	
	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
	
	void initHandleWindows(HINSTANCE hInstance, int nCmdShow);
	
	HWND getHandleWindow();
	WindowGame(void);
	~WindowGame(void);
};
