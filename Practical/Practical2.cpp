//
//#include <Windows.h>
//#include <gl/GL.h>
//#include <gl/GLU.h>
//#include "math.h";
//#include <iostream>
//#include <random>
//
//#pragma comment(lib,"GLU32.lib")
//#pragma comment (lib, "OpenGL32.lib")
//
//#define WINDOW_TITLE "OpenGL Window"
//int qNo = 1;
//float radius = 0.2;
//float x = 0, y = 0;
//float angle = 0;
//float angle2 = 0;
//float x2 = 0, y2 = 0;
//float PI = 3.14159;
//int noOfTri = 30;
//
//float screenWidth = 800;
//float screenHeight = 800;
//// Define the screen width and height
//float aspect = (float)screenHeight / (float)screenWidth; // Calculate aspect ratio
//
//float horizontal = 0;
//float vertical = 0;
//float rotate = 0;
//float scale = 1;
//
//float rotationSpeed = 1;
//
//bool automaticRotate = false;
//bool clockwise = true;
//
//float blackMoving = -1;
//float whiteMoving = -1.4;
//
//bool day = true;
//float dayChange = 0;
//
//
//bool heil = false;
//
//float timer = 0.0f;
//
//bool flip = false;
//
//float R = 0, G = 0, B = 0;
//float R1 = 0, G1 = 0, B1 = 0;
//
//double deltaTime = 0.0; // Global variables for high-resolution timing
//LARGE_INTEGER frequency;    // Holds the frequency of the performance counter
//LARGE_INTEGER prevTime;     // Previous frame's time
//LARGE_INTEGER currentTime;  // Current frame's time
//
//LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
//{
//
//	switch (msg)
//	{
//
//	case WM_DESTROY:
//		PostQuitMessage(0);
//		break;
//
//	case WM_KEYDOWN:
//		if (wParam == VK_ESCAPE) PostQuitMessage(0);
//		switch (wParam) {
//		case 0x31:
//			qNo = 1;
//			break;
//		case 0x32:
//			qNo = 2;
//			break;
//		case 0x33:
//			qNo = 3;
//			break;
//		case 0x34:
//			qNo = 4;
//			break;
//		case 0x35:
//			qNo = 5;
//			break;
//		case 0x36:
//			qNo = 6;
//			break;
//		case VK_UP:
//		case 0x57:
//			vertical += 0.2;
//			rotationSpeed += 1;
//			break;
//		case VK_DOWN:
//		case 0x53:
//			vertical -= 0.2;
//			rotationSpeed -= 1;
//			break;
//		case VK_LEFT:
//		case 0x41:
//			horizontal -= 0.05;
//			break;
//		case VK_RIGHT:
//		case 0x44:
//			horizontal += 0.05;
//			break;
//		case 0x52:
//			R = 1;
//			G = 0;
//			B = 0;
//			break;
//		case 0x47:
//			R = 0;
//			G = 1;
//			B = 0;
//			break;
//		case 0x42:
//			R = 0;
//			G = 0;
//			B = 1;
//			break;
//		case 0x51:
//			rotate += 5 * rotationSpeed;
//			break;
//		case 0x45:
//			rotate -= 5 * rotationSpeed;
//			break;
//		case VK_SHIFT:
//			if (automaticRotate == false) {
//				automaticRotate = true;
//			}
//			else {
//				automaticRotate = false;
//			}
//			break;
//		case VK_CONTROL:
//			if (scale == 1) {
//				scale = 2;
//			}
//			else {
//				scale = 1;
//			}
//			break;
//		case 0x43:
//			if (clockwise == true) {
//				clockwise = false;
//			}
//			else {
//				clockwise = true;
//			}
//		case 0x48:
//			if (heil == true) {
//				heil = false;
//			}
//			else {
//				heil = true;
//			}
//			break;
//		case 0x5A:
//			if (day == true) {
//				day = false;
//			}
//			else {
//				day = true;
//			}
//			break;
//		case VK_SPACE:
//			horizontal = 0;
//			vertical = 0;
//			R = 1;
//			G = 1;
//			B = 1;
//			break;
//		default:
//			qNo = 1;
//			break;
//		}
//		break;
//	default:
//		break;
//	}
//
//	return DefWindowProc(hWnd, msg, wParam, lParam);
//}
////--------------------------------------------------------------------
//
//bool initPixelFormat(HDC hdc)
//{
//	PIXELFORMATDESCRIPTOR pfd;
//	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));
//
//	pfd.cAlphaBits = 8;
//	pfd.cColorBits = 32;
//	pfd.cDepthBits = 24;
//	pfd.cStencilBits = 0;
//
//	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
//
//	pfd.iLayerType = PFD_MAIN_PLANE;
//	pfd.iPixelType = PFD_TYPE_RGBA;
//	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
//	pfd.nVersion = 1;
//
//	// choose pixel format returns the number most similar pixel format available
//	int n = ChoosePixelFormat(hdc, &pfd);
//
//	// set pixel format returns whether it sucessfully set the pixel format
//	if (SetPixelFormat(hdc, n, &pfd))
//	{
//		return true;
//	}
//	else
//	{
//		return false;
//	}
//}
////--------------------------------------------------------------------
//// Initialization function to set up the performance counter
//void InitDeltaTime() {
//	if (!QueryPerformanceFrequency(&frequency)) {
//		std::cerr << "QueryPerformanceFrequency failed!" << std::endl;
//		exit(1);
//	}
//	QueryPerformanceCounter(&prevTime); // Initialize the previous time
//}
//
//// Update function to calculate delta time
//void UpdateDeltaTime() {
//	QueryPerformanceCounter(&currentTime); // Get the current time
//	deltaTime = static_cast<double>(currentTime.QuadPart - prevTime.QuadPart) / frequency.QuadPart;
//	prevTime = currentTime; // Update the previous time
//}
//
//float randomBetweenNegativeOneAndThree(float x, float y) {
//	// Ensure valid range (swap if necessary)
//	if (x > y) std::swap(x, y);
//
//	std::random_device rd;  // Random device for non-deterministic seed
//	std::mt19937 gen(rd()); // Mersenne Twister engine
//	std::uniform_real_distribution<float> dist(x, y); // Create distribution
//	return dist(gen); // Generate and return the random number
//}
//
//
//void drawTri(float x1, float y1, float x2, float y2, float x3, float y3, float R, float G, float B) {
//	glBegin(GL_TRIANGLES);
//	glColor3f(R, G, B);
//	glVertex2f(x1, y1);
//	glVertex2f(x2, y2);
//	glVertex2f(x3, y3);
//	glEnd();
//}
//
//void drawRect(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float R, float G, float B) {
//	glBegin(GL_QUADS);
//	glColor3f(R, G, B);
//
//	glVertex2f(x1, y1);
//	glVertex2f(x2, y2);
//
//	glVertex2f(x3, y3);
//	glVertex2f(x4, y4);
//
//	glEnd();
//}
//
//void drawCircle(GLenum glType, boolean startingFromCenter, boolean semiCircle, float centerX, float centerY, float posX, float posY, int totalTriangle, float radiusX, float radiusY, float R, float G, float B) {
//	int divide = 1;
//
//	if (semiCircle == true) {
//		divide = 2;
//	}
//
//	glBegin(glType);
//
//	startingFromCenter = false;
//
//	glColor3f(R, G, B); // Red color for the circle
//	if (startingFromCenter == true) {
//		glVertex2f(centerX, centerY); // Center of the circle
//	}
//
//
//	// Draw vertices around the circle
//	for (int i = 0; i <= totalTriangle / divide; i++) {
//		angle = i * 2.0f * 3.14159265359f / totalTriangle; // Angle for each triangle vertex
//
//		// Adjust x coordinate with aspect ratio to maintain roundness
//		float x2 = posX + radiusX * cos(angle) * aspect;
//		float y2 = posY + radiusY * sin(angle);
//		glVertex2f(x2, y2);
//	}
//	glEnd();
//}
//
//void drawCircle(GLenum glType, bool startingFromCenter, bool semiCircle,
//	float centerX, float centerY, float posX, float posY,
//	int totalTriangle, float outerRadiusX, float outerRadiusY,
//	float innerRadiusX, float innerRadiusY, float R, float G, float B) {
//	int divide = 1;
//
//	if (semiCircle) {
//		divide = 2;
//	}
//
//	glBegin(glType);
//
//	glColor3f(R, G, B); // Color for the circle
//
//	// Draw vertices for the band
//	for (int i = 0; i <= totalTriangle / divide; i++) {
//		float angle = i * 2.0f * 3.14159265359f / totalTriangle; // Angle for each triangle vertex
//
//		// Outer edge of the band
//		float xOuter = posX + outerRadiusX * cos(angle);
//		float yOuter = posY + outerRadiusY * sin(angle);
//
//		// Inner edge of the band
//		float xInner = posX + innerRadiusX * cos(angle);
//		float yInner = posY + innerRadiusY * sin(angle);
//
//		// Add both inner and outer vertices
//		glVertex2f(xOuter, yOuter);
//		glVertex2f(xInner, yInner);
//	}
//
//	glEnd();
//}
//
//void drawStar(float centerX, float centerY, float radiusOuter, float radiusInner, int numPoints, float R, float G, float B) {
//	float angleStep = 2.0f * 3.14159265359f / numPoints; // Angle between points
//	float halfAngleStep = angleStep / 2.0f; // Half-angle step for inner points
//
//	glBegin(GL_TRIANGLES);
//	glColor3f(R, G, B);
//
//	for (int i = 0; i < numPoints; ++i) {
//		// Calculate outer point
//		float angleOuter = i * angleStep;
//		float xOuter = centerX + radiusOuter * cos(angleOuter);
//		float yOuter = centerY + radiusOuter * sin(angleOuter);
//
//		// Calculate inner point
//		float angleInner = angleOuter + halfAngleStep;
//		float xInner = centerX + radiusInner * cos(angleInner);
//		float yInner = centerY + radiusInner * sin(angleInner);
//
//		// Calculate next outer point
//		float angleNextOuter = (i + 1) * angleStep;
//		float xNextOuter = centerX + radiusOuter * cos(angleNextOuter);
//		float yNextOuter = centerY + radiusOuter * sin(angleNextOuter);
//
//		// Draw triangle
//		glVertex2f(centerX, centerY);
//		glVertex2f(xOuter, yOuter);
//		glVertex2f(xInner, yInner);
//
//		// Draw triangle to the next outer point
//		glVertex2f(xInner, yInner);
//		glVertex2f(xNextOuter, yNextOuter);
//		glVertex2f(centerX, centerY);
//	}
//
//	glEnd();
//}
//
//
//void drawLine(float x1, float y1, float x2, float y2, float R, float G, float B, float lineWidth) {
//	glLineWidth(lineWidth);
//	glBegin(GL_LINES);
//	glColor3f(R, G, B);
//	glVertex2f(x1, y1);
//	glVertex2f(x2, y2);
//	glEnd();
//}
//
//
//
//void display()
//{// Clear the screen with a white background
//	glClearColor(0.0f, 0.0f, 0.0f, 1.0);
//	//glEnable(GL_DEPTH_TEST);
//	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	glClear(GL_COLOR_BUFFER_BIT);
//	//--------------------------------
//	//	OpenGL drawing
//	//--------------------------------
//
//
//
//	glPushMatrix();
//	glRotatef(rotate, 0, 0, 1);
//	glTranslatef(horizontal, vertical, 0);
//	glScalef(scale, scale, 0);
//	drawStar(0.0f, 0.0f, 0.5f, 0.2f, 5, R1, G1, B1); // Yellow star
//	glPopMatrix();
//
//	glPushMatrix();
//	glTranslatef(horizontal, vertical, 0);
//	drawRect(0.1, 0, -0.1, 0, -0.1, 0.1, 0.1, 0.1, R,G,B);
//	glPopMatrix();
//
//
//	
//
//
//
//
//		//--------------------------------
//		//	End of OpenGL drawing
//		//--------------------------------
//}
////--------------------------------------------------------------------
//
//
//
//int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow)
//{
//
//	WNDCLASSEX wc;
//	ZeroMemory(&wc, sizeof(WNDCLASSEX));
//
//	wc.cbSize = sizeof(WNDCLASSEX);
//	wc.hInstance = GetModuleHandle(NULL);
//	wc.lpfnWndProc = WindowProcedure;
//	wc.lpszClassName = WINDOW_TITLE;
//	wc.style = CS_HREDRAW | CS_VREDRAW;
//
//	if (!RegisterClassEx(&wc)) return false;
//
//	HWND hWnd = CreateWindow(WINDOW_TITLE, WINDOW_TITLE, WS_OVERLAPPEDWINDOW,
//		CW_USEDEFAULT, CW_USEDEFAULT, screenWidth, screenHeight,
//		NULL, NULL, wc.hInstance, NULL);
//
//	//--------------------------------
//	//	Initialize window for OpenGL
//	//--------------------------------
//
//	HDC hdc = GetDC(hWnd);
//
//	//	initialize pixel format for the window
//	initPixelFormat(hdc);
//
//	//	get an openGL context
//	HGLRC hglrc = wglCreateContext(hdc);
//
//	//	make context current
//	if (!wglMakeCurrent(hdc, hglrc)) return false;
//
//	//--------------------------------
//	//	End initialization
//	//--------------------------------
//
//	ShowWindow(hWnd, nCmdShow);
//
//	MSG msg;
//	ZeroMemory(&msg, sizeof(msg));
//	InitDeltaTime();
//	while (true)
//	{
//		UpdateDeltaTime();
//		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
//		{
//			if (msg.message == WM_QUIT) break;
//
//			TranslateMessage(&msg);
//			DispatchMessage(&msg);
//		}
//		if (automaticRotate == true) {
//			if (clockwise == true) {
//				rotate -= 5 * rotationSpeed * deltaTime;
//			}
//			else {
//				rotate += 5 * rotationSpeed * deltaTime;
//			}
//
//		}
//
//		angle2 += 50 * deltaTime;
//		blackMoving += 0.3 * deltaTime;
//		if (blackMoving > 1.5) {
//			blackMoving = -1.5;
//		}
//
//		whiteMoving += 0.3 * deltaTime;
//		if (whiteMoving > 1.5) {
//			whiteMoving = -1.5;
//		}
//
//		timer += 1.0 * deltaTime;
//		if (timer >= 1) {
//			if (flip == true) {
//				flip = false;
//			}
//			else {
//				flip = true;
//			}
//			timer = 0;
//		}
//
//		if (!day && dayChange >= 0 && dayChange < 2) {
//			dayChange += 1.0f * deltaTime;
//			if (dayChange > 2) {
//				dayChange = 2; // Clamp to upper limit
//			}
//		}
//		else if (day && dayChange > 0 && dayChange <= 2) {
//			dayChange -= 1.0f * deltaTime;
//			if (dayChange < 0) {
//				dayChange = 0; // Clamp to lower limit
//			}
//		}
//
//		R1 += 0.1 * deltaTime;
//		G1 += 0.1 * deltaTime;
//		B1 += 0.2 * deltaTime;
//
//		if (R1 >= 1) {
//			R1 = 0;
//		}
//
//		if (G1 >= 1) {
//			G1 = 0;
//		}
//
//		if (B1 >= 1) {
//			B1 = 0;
//		}
//
//		display();
//
//		SwapBuffers(hdc);
//	}
//
//	UnregisterClass(WINDOW_TITLE, wc.hInstance);
//
//	return true;
//}
////--------------------------------------------------------------------