
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

float screenWidth = 800;
float screenHeight = 600;
// Define the screen width and height
float aspect = (float)screenHeight / (float)screenWidth; // Calculate aspect ratio

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
		case 0x36:
			qNo = 6;
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
	


	// Clear the screen with a white background
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	// Start drawing the circle
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1.0f, 0.0f, 0.0f); // Red color for the circle
	glVertex2f(x, y); // Center of the circle

	// Draw vertices around the circle
	for (int i = 0; i <= noOfTri; i++) {
		angle = i * 2.0f * 3.14159265359f / noOfTri; // Angle for each triangle vertex

		// Adjust x coordinate with aspect ratio to maintain roundness
		float x2 = x + radius * cos(angle) * aspect;
		float y2 = y + radius * sin(angle);
		glVertex2f(x2, y2);
	}
	glEnd();

	glFlush(); // Ensure rendering is completed
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

void drawTri(float x1, float y1, float x2, float y2, float x3, float y3, float R, float G, float B) {
	glBegin(GL_TRIANGLES);
	glColor3f(R, G, B);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glVertex2f(x3, y3);
	glEnd();
}

void drawRect(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float R, float G, float B) {
	glBegin(GL_QUADS);
	glColor3f(R, G, B);
	
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);

	glVertex2f(x3, y3);
	glVertex2f(x4, y4);

	glEnd();
}

void drawCircle(GLenum glType, boolean startingFromCenter, boolean semiCircle, float centerX, float centerY, float posX, float posY, int totalTriangle, float radiusX, float radiusY, float R, float G, float B) {
	int divide = 1;

	if (semiCircle == true) {
		divide = 2;
	}
	
	glBegin(glType);

	startingFromCenter = false;

	glColor3f(R, G, B); // Red color for the circle
	if (startingFromCenter == true) {
		glVertex2f(centerX, centerY); // Center of the circle
	}
	

	// Draw vertices around the circle
	for (int i = 0; i <= totalTriangle / divide; i++) {
		angle = i * 2.0f * 3.14159265359f / totalTriangle; // Angle for each triangle vertex

		// Adjust x coordinate with aspect ratio to maintain roundness
		float x2 = posX + radiusX * cos(angle) * aspect;
		float y2 = posY + radiusY * sin(angle);
		glVertex2f(x2, y2);
	}
	glEnd();
}

void drawLine(float x1, float y1, float x2, float y2, float R, float G, float B, float lineWidth) {
	glLineWidth(lineWidth);
	glBegin(GL_LINES);
	glColor3f(R, G, B);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glEnd();
}

void hitler() {
	//face
	drawCircle(GL_TRIANGLE_FAN, false, false, 0.0, 0.0, 0.0, 0.0, 30, 0.4, 0.5, 1.0, 0.87, 0.76);
	drawCircle(GL_LINE_LOOP, false, false, 0.0, 0.0, 0.0, 0.0, 30, 0.4, 0.5, 0, 0, 0);

	drawCircle(GL_TRIANGLE_FAN, false, false, 0.0, 0.0, -0.3, 0.1, 30, 0.1, 0.15, 1.0, 0.87, 0.76);

	drawCircle(GL_TRIANGLE_FAN, false, false, 0.0, 0.0, 0.3, 0.1, 30, 0.1, 0.15, 1.0, 0.87, 0.76);

	drawRect(-0.05, 0.13, -0.15, 0.13, -0.15, 0.15, -0.05, 0.15, 0, 0, 0);
	drawCircle(GL_TRIANGLE_FAN, false, false, 0.0, 0.0, -0.1, 0.1, 30, 0.05, 0.05, 0, 0, 0);

	drawRect(0.05, 0.13, 0.15, 0.13, 0.15, 0.15, 0.05, 0.15, 0, 0, 0);
	drawCircle(GL_TRIANGLE_FAN, false, false, 0.0, 0.0, 0.1, 0.1, 30, 0.05, 0.05, 0, 0, 0);

	//nose
	drawRect(0.05, -0.13, -0.05, -0.13, -0.05, -0.05, 0.05, -0.05, 0, 0, 0);

	//hair
	drawCircle(GL_TRIANGLE_FAN, false, true, 0, 0, 0, 0.25, 30, 0.35, 0.25, 0, 0, 0);
	//drawTri(0.27, 0.25, 0.3, 0.1, 0.17, 0.25, 0, 0, 0);
	drawTri(0.26, 0.25, 0.26, 0.1, 0.1, 0.25, 0, 0, 0);

	//mouth
	drawCircle(GL_LINE_STRIP, false, true, 0, 0, 0, -0.3, 30, 0.1, 0.1, 0, 0, 0);

	drawCircle(GL_LINE_LOOP, false, false, 0.0, 0.0, 0.0, 0.0, 30, 0.4, 0.5, 0, 0, 0);
}

void flag() {
	drawCircle(GL_TRIANGLE_FAN, false, false, 0, 0, 0, 0, 30, 0.8, 0.8, 1, 1, 1);
	// Draw central vertical bar
	
	drawRect(0.1, -0.7, -0.1, -0.7, -0.1, 0.7, 0.1, 0.7, 0, 0, 0);
	drawRect(0.3, 0.5, 0, 0.5, 0, 0.7, 0.3, 0.7, 0, 0, 0);
	drawRect(-0.3, -0.5, 0, -0.5, 0, -0.7, -0.3, -0.7, 0, 0, 0);

	drawRect(0.5, -0.1, -0.5, -0.1, -0.5, 0.1, 0.5, 0.1, 0, 0, 0);
	drawRect(-0.3, -0.1, -0.5, -0.1, -0.5, 0.5, -0.3, 0.5, 0, 0, 0);
	drawRect(0.3, 0.1, 0.5, 0.1, 0.5, -0.5, 0.3, -0.5, 0, 0, 0);

}
void display()
{// Clear the screen with a white background
	glClearColor(1.0, 0, 0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	//--------------------------------
	//	OpenGL drawing
	//--------------------------------
	/*switch (qNo) {
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
	case 6:
		flag();
		hitler();
		break;
	default:
		pahangFlag();
		break;
	}*/
	flag();
	hitler();
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
		CW_USEDEFAULT, CW_USEDEFAULT, screenWidth, screenHeight,
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