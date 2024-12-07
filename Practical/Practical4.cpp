
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "math.h";
#include <iostream>
#include <random>

#pragma comment(lib,"GLU32.lib")
#pragma comment (lib, "OpenGL32.lib")

#define WINDOW_TITLE "OpenGL Window"

float radius = 0.2;
float x = 0, y = 0;
float angle = 0;
float angle2 = 0;
float x2 = 0, y2 = 0;
float PI = 3.14159;
int noOfTri = 30;
float screenWidth = 800;
float screenHeight = 800;
// Define the screen width and height
float aspect = (float)screenHeight / (float)screenWidth; // Calculate aspect ratio
float X = 0;
float Y = 0;
float Z = 0;
float rotationSpeed = 0;
float rotationSpeedZ = 0;
float rotationSpeedY = 0;

double deltaTime = 0.0; // Global variables for high-resolution timing
LARGE_INTEGER frequency;    // Holds the frequency of the performance counter
LARGE_INTEGER prevTime;     // Previous frame's time
LARGE_INTEGER currentTime;  // Current frame's time

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
		case VK_LEFT:
			rotationSpeedY += 10;
			break;
		case VK_RIGHT:
			rotationSpeedY -= 10;
			break;
		case VK_UP:
			rotationSpeedZ -= 10;
			break;
		case VK_DOWN:
			rotationSpeedZ += 10;
			break;
		case VK_SPACE:
			rotationSpeedY = 0;
			rotationSpeedZ = 0;
			break;
		case 0x58:
			if (X == 0) {
				X = 1;
				rotationSpeed = 0.05;
			}
			else {
				X = 0;
			}
			
			break;
		case 0x59:
			if (Y == 0) {
				Y = 1;
				rotationSpeed = 0.05;
			}
			else {
				Y = 0;
			}
			break;
		case 0x5A:
			if (Z == 0) {
				Z = 1;
				rotationSpeed = 0.05;
			}
			else {
				Z = 0;
			}
			break;

		default:
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
// Initialization function to set up the performance counter
void InitDeltaTime() {
	if (!QueryPerformanceFrequency(&frequency)) {
		std::cerr << "QueryPerformanceFrequency failed!" << std::endl;
		exit(1);
	}
	QueryPerformanceCounter(&prevTime); // Initialize the previous time
}

// Update function to calculate delta time
void UpdateDeltaTime() {
	QueryPerformanceCounter(&currentTime); // Get the current time
	deltaTime = static_cast<double>(currentTime.QuadPart - prevTime.QuadPart) / frequency.QuadPart;
	prevTime = currentTime; // Update the previous time
}

float randomBetweenNegativeOneAndThree(float x, float y) {
	// Ensure valid range (swap if necessary)
	if (x > y) std::swap(x, y);

	std::random_device rd;  // Random device for non-deterministic seed
	std::mt19937 gen(rd()); // Mersenne Twister engine
	std::uniform_real_distribution<float> dist(x, y); // Create distribution
	return dist(gen); // Generate and return the random number
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

void drawCircle(GLenum glType, bool startingFromCenter, bool semiCircle,
	float centerX, float centerY, float posX, float posY,
	int totalTriangle, float outerRadiusX, float outerRadiusY,
	float innerRadiusX, float innerRadiusY, float R, float G, float B) {
	int divide = 1;

	if (semiCircle) {
		divide = 2;
	}

	glBegin(glType);

	glColor3f(R, G, B); // Color for the circle

	// Draw vertices for the band
	for (int i = 0; i <= totalTriangle / divide; i++) {
		float angle = i * 2.0f * 3.14159265359f / totalTriangle; // Angle for each triangle vertex

		// Outer edge of the band
		float xOuter = posX + outerRadiusX * cos(angle);
		float yOuter = posY + outerRadiusY * sin(angle);

		// Inner edge of the band
		float xInner = posX + innerRadiusX * cos(angle);
		float yInner = posY + innerRadiusY * sin(angle);

		// Add both inner and outer vertices
		glVertex2f(xOuter, yOuter);
		glVertex2f(xInner, yInner);
	}

	glEnd();
}

void drawStar(float centerX, float centerY, float radiusOuter, float radiusInner, int numPoints, float R, float G, float B) {
	float angleStep = 2.0f * 3.14159265359f / numPoints; // Angle between points
	float halfAngleStep = angleStep / 2.0f; // Half-angle step for inner points

	glBegin(GL_TRIANGLES);
	glColor3f(R, G, B);

	for (int i = 0; i < numPoints; ++i) {
		// Calculate outer point
		float angleOuter = i * angleStep;
		float xOuter = centerX + radiusOuter * cos(angleOuter);
		float yOuter = centerY + radiusOuter * sin(angleOuter);

		// Calculate inner point
		float angleInner = angleOuter + halfAngleStep;
		float xInner = centerX + radiusInner * cos(angleInner);
		float yInner = centerY + radiusInner * sin(angleInner);

		// Calculate next outer point
		float angleNextOuter = (i + 1) * angleStep;
		float xNextOuter = centerX + radiusOuter * cos(angleNextOuter);
		float yNextOuter = centerY + radiusOuter * sin(angleNextOuter);

		// Draw triangle
		glVertex2f(centerX, centerY);
		glVertex2f(xOuter, yOuter);
		glVertex2f(xInner, yInner);

		// Draw triangle to the next outer point
		glVertex2f(xInner, yInner);
		glVertex2f(xNextOuter, yNextOuter);
		glVertex2f(centerX, centerY);
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
	glClearColor(1.0, 0, 0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	drawCircle(GL_TRIANGLE_FAN, false, false, 0, 0, 0, 0, 30, 0.8, 0.8, 1, 1, 1);
	// Draw central vertical bar

	drawRect(0.1, -0.7, -0.1, -0.7, -0.1, 0.7, 0.1, 0.7, 0, 0, 0);
	drawRect(0.3, 0.5, 0, 0.5, 0, 0.7, 0.3, 0.7, 0, 0, 0);
	drawRect(-0.3, -0.5, 0, -0.5, 0, -0.7, -0.3, -0.7, 0, 0, 0);

	drawRect(0.5, -0.1, -0.5, -0.1, -0.5, 0.1, 0.5, 0.1, 0, 0, 0);
	drawRect(-0.3, -0.1, -0.5, -0.1, -0.5, 0.5, -0.3, 0.5, 0, 0, 0);
	drawRect(0.3, 0.1, 0.5, 0.1, 0.5, -0.5, 0.3, -0.5, 0, 0, 0);

}

void drawCuboid(float width, float height, float length, float x, float y, float z) {
	glBegin(GL_LINE_STRIP);

	// Bottom face
	glVertex3f(x, y, z);
	glVertex3f(x + width, y, z);
	glVertex3f(x + width, y, z + length);
	glVertex3f(x, y, z + length);

	// Left face
	glVertex3f(x, y, z);
	glVertex3f(x, y + height, z);
	glVertex3f(x, y + height, z + length);
	glVertex3f(x, y, z + length);

	// Back face
	glVertex3f(x, y, z + length);
	glVertex3f(x, y + height, z + length);
	glVertex3f(x + width, y + height, z + length);
	glVertex3f(x + width, y, z + length);

	// Right face
	glVertex3f(x + width, y, z + length);
	glVertex3f(x + width, y + height, z + length);
	glVertex3f(x + width, y + height, z);
	glVertex3f(x + width, y, z);

	// Front face
	glVertex3f(x + width, y, z);
	glVertex3f(x, y, z);
	glVertex3f(x, y + height, z);
	glVertex3f(x + width, y + height, z);

	// Top face
	glVertex3f(x, y + height, z);
	glVertex3f(x + width, y + height, z);
	glVertex3f(x + width, y + height, z + length);
	glVertex3f(x, y + height, z + length);

	glEnd();
}

void drawPyramid(float size) {
	glLineWidth(5.0);
	glBegin(GL_LINE_LOOP);
	glColor3f(1, 0, 0);
	glVertex3f(0, 0, size);
	glVertex3f(size, 0, size);
	glVertex3f(size, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(size / 2, size, size / 2);
	glVertex3f(0, 0, size);
	glVertex3f(size / 2, size, size / 2);
	glVertex3f(size, 0, size);
	glVertex3f(size / 2, size, size / 2);
	glVertex3f(size, 0, 0);
	glVertex3f(size / 2, size, size / 2);
	glVertex3f(0, 0, 0);
	glEnd();
}

void drawCylinder(float br, float tr, float h) {
	GLUquadricObj* cylinder = NULL;
	cylinder = gluNewQuadric();

	gluQuadricDrawStyle(cylinder, GLU_FILL);
	//gluQuadricDrawStyle(cylinder, GLU_FILL);
	gluCylinder(cylinder, br, tr, h, 50, 50);

	gluDeleteQuadric(cylinder);
}

void drawSphere(float size) {
	GLUquadricObj* sphere = NULL;
	sphere = gluNewQuadric();

	gluQuadricDrawStyle(sphere, GLU_FILL);
	//gluQuadricDrawStyle(sphere, GLU_FILL);
	gluSphere(sphere, size, 30, 30);


	gluDeleteQuadric(sphere);
}

void drawDisk(float r, float inr, float outr) {
	GLUquadricObj* disk = NULL;
	disk = gluNewQuadric();
	gluQuadricDrawStyle(disk, GLU_FILL);
	gluDisk(disk, inr, outr, 30, 30);
	gluDeleteQuadric(disk);
}

void drawSphereWithoutGLU()
{
	const float PI = 3.141592f;
	GLfloat x, y, z, sliceA, stackA;
	GLfloat radius = 0.5;
	int sliceNo = 30, stackNo = 30;

	for (sliceA = 0.0; sliceA < 2 * PI; sliceA += PI / sliceNo)
	{
		glBegin(GL_POLYGON);
		for (stackA = 0.0; stackA < 2 * PI; stackA += PI / stackNo)
		{
			x = radius * cos(stackA) * sin(sliceA);
			y = radius * sin(stackA) * sin(sliceA);
			z = radius * cos(sliceA);
			glVertex3f(x, y, z);
			x = radius * cos(stackA) * sin(sliceA + PI / stackNo);
			y = radius * sin(stackA) * sin(sliceA + PI / sliceNo);
			z = radius * cos(sliceA + PI / sliceNo);
			glVertex3f(x, y, z);
		}
		glEnd();
	}
}

void pyramidExercise() {
	glRotatef(rotationSpeed, X, Y, Z);
	drawPyramid(0.5);
	drawPyramid(-0.5);
}

void iceCream() {
	glRotatef(0.01, 0, 1, 0);
	glPushMatrix();
	glPushMatrix();
	glTranslatef(0, 0.5, 0);
	glRotatef(-120, 1, 0, 0);
	glColor3f(0.34, 0.11, 0);
	drawCylinder(0.05, 0.05, 0.5);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, 0.6, 0.25);
	glColor3f(1, 0.99, 0.83);
	drawDisk(0.5, 0.3, 0.5);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, 0.15, 0);
	glColor3f(0, 0.96, 0.81);
	drawSphere(0.35);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, 0.45, 0);
	glColor3f(1, 0.25, 0.68);
	drawSphere(0.25);
	glPopMatrix();
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	glTranslatef(0, 0, -0.9);
	glColor3f(0.34, 0.11, 0);
	drawCylinder(0, 0.3, 1);
	glPopMatrix();
	glPopMatrix();
}

void armExercise() {
	glPushMatrix();
	glRotatef(rotationSpeedY, 0, 1, 0);
	glColor3f(1, 0, 0);
	drawCuboid(0.4f, 0.1f, 0.1f, 0.0f, 0.0f, 0.0f);
	glPushMatrix();
	glRotatef(rotationSpeedZ, 0, 0, 1);
	glColor3f(1, 1, 0);
	drawCuboid(-0.6f, 0.1f, 0.1f, 0.0f, 0.0f, 0.0f);
	glPopMatrix();
	glPopMatrix();
}
void display()
{// Clear the screen with a white background
	glClearColor(1.0f, 1.0f, 1.0f, 1.0);
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//--------------------------------
	//	OpenGL drawing
	//--------------------------------




	//pyramidExercise();

	//armExercise();

	iceCream();





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
	InitDeltaTime();
	while (true)
	{
		UpdateDeltaTime();
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