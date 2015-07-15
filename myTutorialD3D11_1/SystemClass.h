#pragma once 
//定义该宏能够减少windows头文件的大小，使编译器不编译一些不必要的文件，加快编译时间 
#define WIN32_LEAN_AND_MEAN

#include <windows.h>

#include "InputClass.h" 
#include "GraphicsClass.h"

class SystemClass
{
public:
	SystemClass(void);
	SystemClass(const SystemClass &);
	~SystemClass(void);

	bool Initialize();
	void Shutdown();
	void Run();

	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);
private:
	bool Frame();
	void InitializeWindows(int&, int&);
	void ShutdownWindows();

	LPCWSTR m_applicationName;
	HINSTANCE m_hinstance;
	HWND m_hwnd;

	//InputClass和GraphicsClass是SystemClass的两个成员变量 
	InputClass* m_Input;
	GraphicsClass* m_Graphics;
};

//定义静态的回调函数以及应用程序句柄 
//因为定义窗口类时候，必须指定窗口回调函数，所以我们用静态的回调函数WndProc 
static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

static SystemClass* ApplicationHandle = 0;
