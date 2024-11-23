
#include <Windows.h>
#include <gl/GL.h>
#include "math.h";
#pragma comment (lib, "OpenGL32.lib")

#define WINDOW_TITLE "OpenGL Window"

int qNo = 1;
float radius = 0.2;
float x = 0, y = 0;
float angle = 0;
float x2 = 0, y2 = 0;
float PI = 3.14159;
int noOfTri = 30;

LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE) PostQuitMessage(0);
		switch (wParam) {
		case 0x31:
			qNo = 1;
			break;
		case 0x32:
			qNo = 2;
			break;
		case 0x33:
			qNo = 3;
			break;
		case 0x34:
			qNo = 4;
			break;
		case 0x35:
			qNo = 5;
			break;
		default:
			qNo = 1;
			break;
		}
		break;
	default:
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
//--------------------------------------------------------------------

bool initPixelFormat(HDC hdc)
{
	PIXELFORMATDESCRIPTOR pfd;
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.cAlphaBits = 8;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 0;

	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;

	pfd.iLayerType = PFD_MAIN_PLANE;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;

	// choose pixel format returns the number most similar pixel format available
	int n = ChoosePixelFormat(hdc, &pfd);

	// set pixel format returns whether it sucessfully set the pixel format
	if (SetPixelFormat(hdc, n, &pfd))
	{
		return true;
	}
	else
	{
		return false;
	}
}
//--------------------------------------------------------------------
void pahangFlag() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glShadeModel(GL_SMOOTH);
	glLineWidth(5.0f);
	glPointSize(5.0f);
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);

	glVertex2f(1.0, 0.0);
	glVertex2f(-1.0, 0.0);

	glVertex2f(-1.0, 1.0);
	glVertex2f(1.0, 1.0);
	
	glEnd();
}

void negeriSembilan() {
	glClearColor(1.0f, 1.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(-0.1, 0.2);
	glVertex2f(-1.0, 1.0);
	glVertex2f(-0.1, 1.0);
	glEnd();
	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(-0.1, 0.2);
	glVertex2f(-1.0, 0.2);
	glVertex2f(-1.0, 1.0);
	glEnd();
}

void england() {
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glShadeModel(GL_SMOOTH);
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(0.0, 0.0);
	glVertex2f(-1.0, 0.0);
	glColor3f(0.5f, 0.5f, 0.5f);
	glVertex2f(-1.0, -1.0);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(0.0, -1.0);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(0.0, 0.0);
	glVertex2f(-1.0, 0.0);
	glColor3f(0.5f, 0.5f, 0.5f);
	glVertex2f(-1.0, 1.0);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(0.0, 1.0);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(0.0, 0.0);
	glVertex2f(1.0, 0.0);
	glColor3f(0.5f, 0.5f, 0.5f);
	glVertex2f(1.0, 1.0);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(0.0, 1.0);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(0.0, 0.0);
	glVertex2f(1.0, 0.0);
	glColor3f(0.5f, 0.5f, 0.5f);
	glVertex2f(1.0, -1.0);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(0.0, -1.0);
	glEnd();
	glLineWidth(50.0f);
	glBegin(GL_LINES);
	glColor3f(0.7f, 0.0f, 0.0f);
	glVertex2f(0.0, 1.0);
	glVertex2f(0.0, -1.0);
	glVertex2f(-1.0, 0.0);
	glVertex2f(1.0, 0.0);
	glEnd();
}

void japan() {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x, y);
	for (angle = 0; angle < 2 * PI; angle += (2 * PI) / noOfTri) {
		x2 = x + radius * cos(angle);
		y2 = y + radius * sin(angle);
		glColor3f(1.0f, 0.0f, 0.0);
		glVertex2f(x2, y2);
	}
	glEnd();
}

void scotland() {
	glClearColor(0.0f, 0.0f, 0.8f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glShadeModel(GL_SMOOTH);
	glLineWidth(100.0f);
	glBegin(GL_LINES);
	glColor3f(1.0f, 1.0f, 1.0f);

	glVertex2f(-1.0, 1.0);
	glVertex2f(1.0, -1.0);

	glVertex2f(-1.0, -1.0);
	glVertex2f(1.0, 1.0);

	glEnd();
}
void display()
{
	//--------------------------------
	//	OpenGL drawing
	//--------------------------------
	switch (qNo) {
	case 1:
		pahangFlag();
		break;
	case 2:
		negeriSembilan();
		break;
	case 3:
		england();
		break;
	case 4:
		japan();
		break;
	case 5:
		scotland();
		break;
	default:
		pahangFlag();
		break;
	}
	//--------------------------------
	//	End of OpenGL drawing
	//--------------------------------
}
//--------------------------------------------------------------------

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow)
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpfnWndProc = WindowProcedure;
	wc.lpszClassName = WINDOW_TITLE;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&wc)) return false;

	HWND hWnd = CreateWindow(WINDOW_TITLE, WINDOW_TITLE, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
		NULL, NULL, wc.hInstance, NULL);

	//--------------------------------
	//	Initialize window for OpenGL
	//--------------------------------

	HDC hdc = GetDC(hWnd);

	//	initialize pixel format for the window
	initPixelFormat(hdc);

	//	get an openGL context
	HGLRC hglrc = wglCreateContext(hdc);

	//	make context current
	if (!wglMakeCurrent(hdc, hglrc)) return false;

	//--------------------------------
	//	End initialization
	//--------------------------------

	ShowWindow(hWnd, nCmdShow);

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		display();

		SwapBuffers(hdc);
	}

	UnregisterClass(WINDOW_TITLE, wc.hInstance);

	return true;
}
//--------------------------------------------------------------------