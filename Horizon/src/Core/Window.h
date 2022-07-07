#pragma once
#include <Windows.h>

class Window
{
public:
	Window();
	void Create(int width, int height, const char* title);
	void Update();
	void Shutdown();
	void Close();
	bool IsOpen();
	static HWND& GetHandle() { return m_Hwnd; }
private:
	int width, height;
	bool m_IsOpen;
private:
	MSG m_Msg;
	HINSTANCE m_hInst;
	static HWND m_Hwnd;
	const char* m_cls;
};

