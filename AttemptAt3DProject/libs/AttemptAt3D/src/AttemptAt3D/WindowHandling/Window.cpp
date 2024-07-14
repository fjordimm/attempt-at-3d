
#include "AttemptAt3D/WindowHandling/Window.h"

constexpr wchar_t WINDOW_CLASS_NAME[] = L"AttemptAt3D Window Class";
constexpr wchar_t WINDOW_TITLE[] = L"AttemptAt3D Title Placeholder";
constexpr int WINDOW_HEIGHT = 900;
constexpr int WINDOW_WIDTH = 600;

namespace AttemptAt3D::WindowHandling
{
	LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		switch (uMsg)
		{
		case WM_CLOSE:
			DestroyWindow(hWnd);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		}

		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	Window::Window()
		: m_hInstance(GetModuleHandle(nullptr))
	{
		WNDCLASS wndClass = {};
		wndClass.lpszClassName = WINDOW_CLASS_NAME;
		wndClass.hInstance = this->m_hInstance;
		wndClass.hIcon = LoadIcon(NULL, IDI_INFORMATION);
		wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
		wndClass.lpfnWndProc = WindowProc;

		RegisterClass(&wndClass);

		DWORD style = WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU;

		int width = WINDOW_HEIGHT;
		int height = WINDOW_WIDTH;

		RECT rect;
		rect.left = 300;
		rect.top = 100;
		rect.right = rect.left + width;
		rect.bottom = rect.top + height;

		AdjustWindowRect(&rect, style, false);

		this->m_hWnd = CreateWindowEx(
			0,
			WINDOW_CLASS_NAME,
			WINDOW_TITLE,
			style,
			rect.left,
			rect.top,
			rect.right - rect.left,
			rect.bottom - rect.top,
			NULL,
			NULL,
			this->m_hInstance,
			NULL
		);

		ShowWindow(this->m_hWnd, SW_SHOW);
	}

	Window::~Window()
	{
		UnregisterClass(WINDOW_CLASS_NAME, this->m_hInstance);
	}

	bool Window::ProcessMessages()
	{
		MSG msg = {};

		while (PeekMessage(&msg, nullptr, 0u, 0u, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{ return false; }

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		return true;
	}
}
