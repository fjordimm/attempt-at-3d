
#include "AttemptAt3D/WindowHandling/Window.h"

#define GLEW_STATIC
#include <glew.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <cstdio>
#include <cstdlib>

const char* vertexShaderSource = R"glsl(
	#version 150 core

	in vec2 position;
	in vec3 color;

	out vec3 Color;

	void main()
	{
		Color = color;
		gl_Position = vec4(position, 0.0, 1.0);
	}
)glsl";

const char* fragmentShaderSource = R"glsl(
	#version 150 core

	in vec3 Color;

	out vec4 outColor;

	void main()
	{
		outColor = vec4(Color, 1.0);
	}
)glsl";

void checkShaderCompilation(GLuint shader)
{
	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

	if ((bool)status == true)
	{ return; }
	else
	{
		static char buf[512];
		glGetShaderInfoLog(shader, 512, nullptr, buf);
		std::fprintf(stderr, "=== Shader did not compile ===\n");
		std::fprintf(stderr, "%s\n", buf);
		std::exit(EXIT_FAILURE);
	}
}

constexpr wchar_t WINDOW_CLASS_NAME[] = L"AttemptAt3D Window Class";
constexpr wchar_t WINDOW_TITLE[] = L"AttemptAt3D Title Placeholder";
constexpr int WINDOW_HEIGHT = 900;
constexpr int WINDOW_WIDTH = 600;

namespace AttemptAt3D::WindowHandling
{
	LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		PAINTSTRUCT paintstruct;
		RECT viewRect;

		switch (uMsg)
		{
		// case WM_CREATE:
		// 	HDC ghDC = GetDC(hWnd);
		// 	if (!setupPixelFormat(ghDC))
		// 	{ PostQuitMessage (0); }
	
		// 	HGLRC ghRC = wglCreateContext(ghDC);
		// 	wglMakeCurrent(ghDC, ghRC);
		// 	GetClientRect(hWnd, &viewRect);
		// 	// initializeGL(viewRect.right, viewRect.bottom);
		// 	break;
		// case WM_SIZE:
		// 	GetClientRect(hWnd, &viewRect);
		// 	// resize(viewRect.right, viewRect.bottom);
		// 	break;
		case WM_PAINT:
			BeginPaint(hWnd, &paintstruct);
			EndPaint(hWnd, &paintstruct);
			break;
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
		: hInstance(GetModuleHandle(nullptr))
	{
		WNDCLASS wndClass = {};
		wndClass.lpszClassName = WINDOW_CLASS_NAME;
		wndClass.hInstance = this->hInstance;
		wndClass.hIcon = LoadIcon(NULL, IDI_INFORMATION);
		wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
		wndClass.lpfnWndProc = WindowProc;
		// wndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW+1); 

		RegisterClass(&wndClass);

		// TODO: the flags
		DWORD style = WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU | WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

		int width = WINDOW_HEIGHT;
		int height = WINDOW_WIDTH;

		RECT rect;
		rect.left = 300;
		rect.top = 100;
		rect.right = rect.left + width;
		rect.bottom = rect.top + height;

		AdjustWindowRect(&rect, style, false);

		this->hWnd = CreateWindowEx(
			0,
			WINDOW_CLASS_NAME,
			WINDOW_TITLE,
			style,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			rect.right - rect.left,
			rect.bottom - rect.top,
			NULL,
			NULL,
			this->hInstance,
			NULL
		);

		ShowWindow(this->hWnd, SW_SHOW);

		UpdateWindow(this->hWnd);

		this->mainLoop();
	}

	Window::~Window()
	{
		UnregisterClass(WINDOW_CLASS_NAME, this->hInstance);
	}

	void Window::mainLoop()
	{
		glewExperimental = GL_TRUE;
		glewInit();

		////////////////////////////////////////
			GLuint vao;
			glGenVertexArrays(1, &vao);
			glBindVertexArray(vao);

			float verts1[] =
			{
				0.0f,  0.5f,      1.0f,0.0f,0.0f,
				0.5f, -0.5f,      0.0f,1.0f,0.0f,
				-0.5f, -0.5f,      0.0f,0.0f,1.0f
			};

			GLuint vbo;
			glGenBuffers(1, &vbo);

			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferData(GL_ARRAY_BUFFER, sizeof(verts1), verts1, GL_STATIC_DRAW);

			GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
			glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
			glCompileShader(vertexShader);
			checkShaderCompilation(vertexShader);

			GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
			glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
			glCompileShader(fragmentShader);
			checkShaderCompilation(fragmentShader);

			GLuint shaderProgram = glCreateProgram();
			glAttachShader(shaderProgram, vertexShader);
			glAttachShader(shaderProgram, fragmentShader);

			glLinkProgram(shaderProgram);
			glUseProgram(shaderProgram);

			GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
			glEnableVertexAttribArray(posAttrib);
			glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);

			GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
			glEnableVertexAttribArray(colAttrib);
			glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
		////////////////////////////////////////

		bool running = true;
		while (running)
		{
			if (!this->processMessages())
			{ running = false; }

			this->draw();
			

			Sleep(10);
		}
	}

	bool Window::processMessages()
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

	void Window::draw()
	{

	}

	bool setupPixelFormat(HDC hdc)
	{ 
		PIXELFORMATDESCRIPTOR pfd, *ppfd;
		int pixelformat;

		ppfd = &pfd;

		ppfd->nSize = sizeof(PIXELFORMATDESCRIPTOR);
		ppfd->nVersion = 1;
		ppfd->dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
		ppfd->dwLayerMask = PFD_MAIN_PLANE;
		ppfd->iPixelType = PFD_TYPE_COLORINDEX;
		ppfd->cColorBits = 8;
		ppfd->cDepthBits = 16;
		ppfd->cAccumBits = 0;
		ppfd->cStencilBits = 0;

		pixelformat = ChoosePixelFormat(hdc, ppfd);

		if ((pixelformat = ChoosePixelFormat(hdc, ppfd)) == 0)
		{ 
			MessageBox(NULL, L"ChoosePixelFormat failed", L"Error", MB_OK);
			return false;
		} 

		if (SetPixelFormat(hdc, pixelformat, ppfd) == false)
		{ 
			MessageBox(NULL, L"SetPixelFormat failed", L"Error", MB_OK);
			return false;
		} 

		return true;
	} 
}
