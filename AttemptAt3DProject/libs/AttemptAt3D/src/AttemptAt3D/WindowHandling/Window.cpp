
#include "AttemptAt3D/WindowHandling/Window.h"

#include <gl/GL.h>
#include <gl/GLU.h>

/* Windows globals, defines, and prototypes */ 
// CHAR szAppName[]="Win OpenGL"; 
// HWND  ghWnd; 
HDC   ghDC; 
HGLRC ghRC; 
#define SWAPBUFFERS SwapBuffers(ghDC) 
#define BLACK_INDEX     0 
#define RED_INDEX       13 
#define GREEN_INDEX     14 
#define BLUE_INDEX      16 
#define WIDTH           300 
#define HEIGHT          200 
BOOL bSetupPixelFormat(HDC); 

/* OpenGL globals, defines, and prototypes */ 
GLfloat latitude, longitude, latinc, longinc; 
GLdouble radius; 
#define GLOBE    1 
#define CYLINDER 2 
#define CONE     3 
GLvoid resize(GLsizei, GLsizei); 
GLvoid initializeGL(GLsizei, GLsizei); 
GLvoid drawScene(GLvoid); 
void polarView( GLdouble, GLdouble, GLdouble, GLdouble);

constexpr wchar_t WINDOW_CLASS_NAME[] = L"AttemptAt3D Window Class";
constexpr wchar_t WINDOW_TITLE[] = L"AttemptAt3D Title Placeholder";
constexpr int WINDOW_HEIGHT = 900;
constexpr int WINDOW_WIDTH = 600;

namespace AttemptAt3D::WindowHandling
{
	LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		PAINTSTRUCT    ps; 
		RECT rect; 

		switch (uMsg)
		{
		case WM_CREATE: 
			ghDC = GetDC(hWnd); 
			if (!bSetupPixelFormat(ghDC)) 
				PostQuitMessage (0); 
	
			ghRC = wglCreateContext(ghDC); 
			wglMakeCurrent(ghDC, ghRC); 
			GetClientRect(hWnd, &rect); 
			initializeGL(rect.right, rect.bottom); 
			break; 
		case WM_PAINT: 
			BeginPaint(hWnd, &ps); 
			EndPaint(hWnd, &ps); 
			break;
		case WM_SIZE: 
			GetClientRect(hWnd, &rect); 
			resize(rect.right, rect.bottom); 
			break;
		case WM_KEYDOWN: 
			switch (wParam)
			{ 
			case VK_LEFT: 
				longinc += 0.5F; 
				break; 
			case VK_RIGHT: 
				longinc -= 0.5F; 
				break; 
			case VK_UP: 
				latinc += 0.5F; 
				break; 
			case VK_DOWN: 
				latinc -= 0.5F; 
				break; 
			} 
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
		wndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW+1); 

		RegisterClass(&wndClass);

		DWORD style = WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU | WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

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
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			rect.right - rect.left,
			rect.bottom - rect.top,
			NULL,
			NULL,
			this->m_hInstance,
			NULL
		);

		ShowWindow(this->m_hWnd, SW_SHOW);

		UpdateWindow(this->m_hWnd);
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

		/////////////////////////////////////

		drawScene();

		/////////////////////////////////////

		return true;
	}
}

BOOL bSetupPixelFormat(HDC hdc) 
{ 
	PIXELFORMATDESCRIPTOR pfd, *ppfd; 
	int pixelformat; 

	ppfd = &pfd; 

	ppfd->nSize = sizeof(PIXELFORMATDESCRIPTOR); 
	ppfd->nVersion = 1; 
	ppfd->dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL |  
						PFD_DOUBLEBUFFER; 
	ppfd->dwLayerMask = PFD_MAIN_PLANE; 
	ppfd->iPixelType = PFD_TYPE_COLORINDEX; 
	ppfd->cColorBits = 8; 
	ppfd->cDepthBits = 16; 
	ppfd->cAccumBits = 0; 
	ppfd->cStencilBits = 0; 

	pixelformat = ChoosePixelFormat(hdc, ppfd); 

	if ( (pixelformat = ChoosePixelFormat(hdc, ppfd)) == 0 ) 
	{ 
		MessageBox(NULL, L"ChoosePixelFormat failed", L"Error", MB_OK); 
		return FALSE; 
	} 

	if (SetPixelFormat(hdc, pixelformat, ppfd) == FALSE) 
	{ 
		MessageBox(NULL, L"SetPixelFormat failed", L"Error", MB_OK); 
		return FALSE; 
	} 

	return TRUE; 
} 

/* OpenGL code */ 

GLvoid resize( GLsizei width, GLsizei height ) 
{ 
	GLfloat aspect; 

	glViewport( 0, 0, width, height ); 

	aspect = (GLfloat) width / height; 

	glMatrixMode( GL_PROJECTION ); 
	glLoadIdentity(); 
	gluPerspective( 45.0, aspect, 3.0, 7.0 ); 
	glMatrixMode( GL_MODELVIEW ); 
}     

GLvoid createObjects() 
{ 
	GLUquadricObj *quadObj; 

	glNewList(GLOBE, GL_COMPILE); 
		quadObj = gluNewQuadric (); 
		gluQuadricDrawStyle (quadObj, GLU_LINE); 
		gluSphere (quadObj, 1.5, 16, 16); 
	glEndList(); 

	glNewList(CONE, GL_COMPILE); 
		quadObj = gluNewQuadric (); 
		gluQuadricDrawStyle (quadObj, GLU_FILL); 
		gluQuadricNormals (quadObj, GLU_SMOOTH); 
		gluCylinder(quadObj, 0.3, 0.0, 0.6, 15, 10); 
	glEndList(); 

	glNewList(CYLINDER, GL_COMPILE); 
		glPushMatrix (); 
		glRotatef ((GLfloat)90.0, (GLfloat)1.0, (GLfloat)0.0, (GLfloat)0.0); 
		glTranslatef ((GLfloat)0.0, (GLfloat)0.0, (GLfloat)-1.0); 
		quadObj = gluNewQuadric (); 
		gluQuadricDrawStyle (quadObj, GLU_FILL); 
		gluQuadricNormals (quadObj, GLU_SMOOTH); 
		gluCylinder (quadObj, 0.3, 0.3, 0.6, 12, 2); 
		glPopMatrix (); 
	glEndList(); 
} 

GLvoid initializeGL(GLsizei width, GLsizei height) 
{ 
	GLfloat     maxObjectSize, aspect; 
	GLdouble    near_plane, far_plane; 

	glClearIndex( (GLfloat)BLACK_INDEX); 
	glClearDepth( 1.0 ); 

	glEnable(GL_DEPTH_TEST); 

	glMatrixMode( GL_PROJECTION ); 
	aspect = (GLfloat) width / height; 
	gluPerspective( 45.0, aspect, 3.0, 7.0 ); 
	glMatrixMode( GL_MODELVIEW ); 

	near_plane = 3.0; 
	far_plane = 7.0; 
	maxObjectSize = 3.0F; 
	radius = near_plane + maxObjectSize/2.0; 

	latitude = 0.0F; 
	longitude = 0.0F; 
	latinc = 6.0F; 
	longinc = 2.5F; 

	createObjects(); 
} 

void polarView(GLdouble radius, GLdouble twist, GLdouble latitude, 
		GLdouble longitude) 
{ 
	glTranslated(0.0, 0.0, -radius); 
	glRotated(-twist, 0.0, 0.0, 1.0); 
	glRotated(-latitude, 1.0, 0.0, 0.0); 
	glRotated(longitude, 0.0, 0.0, 1.0);      

} 

GLvoid drawScene(GLvoid) 
{ 
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); 

	glPushMatrix(); 

		latitude += latinc; 
		longitude += longinc; 

		polarView( radius, 0, latitude, longitude ); 

		glIndexi(RED_INDEX); 
		glCallList(CONE); 

		glIndexi(BLUE_INDEX); 
		glCallList(GLOBE); 

	glIndexi(GREEN_INDEX); 
		glPushMatrix(); 
			glTranslatef(0.8F, -0.65F, 0.0F); 
			glRotatef(30.0F, 1.0F, 0.5F, 1.0F); 
			glCallList(CYLINDER); 
		glPopMatrix(); 

	glPopMatrix(); 

	SWAPBUFFERS; 
}
