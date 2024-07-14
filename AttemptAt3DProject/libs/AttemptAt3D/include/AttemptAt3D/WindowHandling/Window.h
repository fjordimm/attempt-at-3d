
#pragma once

#include <Windows.h>

namespace AttemptAt3D::WindowHandling
{
	LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	class Window
	{
	public:
		Window();
		~Window();
		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;
	
	private:
		HINSTANCE hInstance;
		HWND hWnd;
		HDC hDC;
		HGLRC hRC;

		void mainLoop();
		bool processMessages();
		void draw();
	};

	bool setupPixelFormat(HDC hdc);
}
