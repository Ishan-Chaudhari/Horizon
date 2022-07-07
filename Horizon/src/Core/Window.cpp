#include "Window.h"
#include "Input.h"
#include "Logger.h"
#include "KeyCodes.h"

HWND Window::m_Hwnd;

LRESULT WINAPI WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

Window::Window()
{
	height = 0;
	width = 0;
	m_IsOpen = true;
	m_hInst = GetModuleHandle(NULL);
	m_cls = "WNDclass";
}

void Window::Create(int width, int height, const char* title)
{
	this->width = width;
	this->height = height;

	WNDCLASS wc = {};
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = nullptr;
	wc.hCursor = nullptr;
	wc.hIcon = nullptr;
	wc.hInstance = m_hInst;
	wc.lpfnWndProc = WindowProc;
	wc.lpszClassName = m_cls;
	wc.lpszMenuName = nullptr;
	wc.style = CS_OWNDC;
	
	RegisterClass(&wc);

	m_Hwnd = CreateWindowEx(0, m_cls, title, WS_OVERLAPPEDWINDOW, 100, 50, width, height, NULL, NULL, m_hInst, NULL);

	ShowWindow(m_Hwnd, SW_SHOW);
}

void Window::Update()
{
	while (PeekMessage(&m_Msg, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&m_Msg);
		DispatchMessage(&m_Msg);

		if (m_Msg.message == WM_QUIT)
			Close();
	}
}

void Window::Shutdown()
{
	UnregisterClass(m_cls, m_hInst);
}

void Window::Close()
{
	m_IsOpen = false;
}

bool Window::IsOpen()
{
	return m_IsOpen;
}


LRESULT WINAPI WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CLOSE:
	{
		PostQuitMessage(0);
		break;
	}
	case WM_KEYDOWN:
	{
		Input::SetKeyboardState(wParam, true);
		break;
	}
	case WM_KEYUP:
	{
		Input::SetKeyboardState(wParam, false);
		break;
	}
	case WM_LBUTTONDOWN:
	{
		Input::SetMouseState(VK_LBUTTON, true);
		break;
	}
	case WM_LBUTTONUP:
	{
		Input::SetMouseState(VK_LBUTTON, false);
		break;
	}
	case WM_RBUTTONDOWN:
	{
		Input::SetMouseState(VK_RBUTTON, true);
		break;
	}
	case WM_RBUTTONUP:
	{
		Input::SetMouseState(VK_RBUTTON, false);
		break;
	}
	case WM_MBUTTONDOWN:
	{
		Input::SetMouseState(VK_MBUTTON, true);
		break;
	}
	case WM_MBUTTONUP:
	{
		Input::SetMouseState(VK_MBUTTON, false);
		break;
	}
	case WM_SIZE:
	{
		//DirectX11::SetViewPort(0, 0, (float)LOWORD(wParam), (float)HIWORD(wParam), 0, 1);
		break;
	}
	case WM_MOUSEMOVE:
	{
		Input::SetMousePosition((double)LOWORD(lParam), (double)HIWORD(lParam));
		break;
	}
	default:
		break;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}
