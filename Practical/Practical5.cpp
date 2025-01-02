#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#pragma comment (lib, "OpenGL32.lib")
#pragma comment (lib, "GLU32.lib")


#define WINDOW_TITLE "Practical 7"

// Window and view settings
float windowWidth = 1000, windowHeight = 800;
bool isOrtho = true;
// Object transformation variables
float cameraAngleX = 0.0f, cameraAngleY = 0.0f, cameraAngleZ = 0.0f;  // Camera rotation angles
//float cameraDistance = -15.0f;  // Camera distance from the object

float rotateX = 0.0f, rotateY = 0.0f, rotateZ = 0.0f;
float translateX = 0.0f, translateY = 0.0f, translateZ = 10.0f;
float scale = 1.0f;

// Ortho and perspective view settings
float ONear = -40.0f, OFar = 40.0f;
float PNear = 0.01f, PFar = 20.0f;
float zoomFactor = 1.7f; // Zoom factor for scaling


// Mouse state
bool mouseLeftPressed = false;
int lastMouseX, lastMouseY;

// Circle drawing variables
const float PI = 3.141592f;
float angle = 0.0f;

// rotate variables
float leftBridgeRotationZ = 0;
float rightBridgeRotationZ = 0;

//Texture variables
BITMAP BMP;					//bitmap structure			

HBITMAP hBMP = NULL;		//handle to a bitmap
GLuint skyboxTextures[6];



LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_LBUTTONDOWN:
		mouseLeftPressed = true;
		lastMouseX = LOWORD(lParam);
		lastMouseY = HIWORD(lParam);
		break;

	case WM_LBUTTONUP:
		mouseLeftPressed = false;
		break;

	case WM_MOUSEMOVE:
		if (mouseLeftPressed)
		{
			int mouseX = LOWORD(lParam);
			int mouseY = HIWORD(lParam);
			cameraAngleY += (mouseX - lastMouseX) * 0.3f;  // Horizontal rotation
			cameraAngleX += (mouseY - lastMouseY) * 0.3f;  // Vertical rotation
			lastMouseX = mouseX;
			lastMouseY = mouseY;
		}
		break;

	case WM_MOUSEWHEEL: // Handle zoom using mouse scroll
		if (GET_WHEEL_DELTA_WPARAM(wParam) > 0) // Scroll up
		{
			if (isOrtho) {
				zoomFactor += 0.1f;
				if (zoomFactor > 2.4f) zoomFactor = 2.4f; // Clamp max zoom
			}

		}
		else // Scroll down
		{
			if (isOrtho) {
				zoomFactor -= 0.1f;
				if (zoomFactor < 1.4f) zoomFactor = 1.4f; // Clamp min zoom
			}
		}
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE: PostQuitMessage(0); break;
		case 'O': // Orthographic view
			isOrtho = true;
			translateZ = 10.0f;
			zoomFactor = 1.4f; // Reset zoom
			break;
		case 'P': // Perspective view
			isOrtho = false;
			translateZ = -(PFar / 2.0f); // Start in the middle of the range
			zoomFactor = 0.3f; // Reset zoom
			break;
		case 'Q': // Move closer to the object
			if (!isOrtho) {
				if (translateZ < -10)
					translateZ += 1.0f;
			}
			break;
		case 'E': // Move farther from the object
			if (!isOrtho) {
				if (translateZ > -(PFar))
					translateZ -= 1.0f;
			}
			break;
		case 'A': translateX += 0.5f; break;
		case 'D': translateX -= 0.5f; break;
		case 'W': translateY -= 0.5f; break;
		case 'S': translateY += 0.5f; break;

		case 0x31: // 1 key
			if (leftBridgeRotationZ < 90)
				leftBridgeRotationZ += 1.0f;
			break;

		case 0x32: // 2 key
			if (leftBridgeRotationZ > 0)
				leftBridgeRotationZ -= 1.0f;
			break;

		case 0x33: // 3 key
			if (rightBridgeRotationZ > -90)
				rightBridgeRotationZ -= 1.0f;
			break;

		case 0x34: // 4 key
			if (rightBridgeRotationZ < 0)
				rightBridgeRotationZ += 1.0f;
			break;
		}

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
GLuint loadTexture(LPCSTR filename) {
	GLuint texture = 0;

	// Initialize texture info
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	HBITMAP hBMP = (HBITMAP)LoadImage(
		GetModuleHandle(NULL),
		filename, IMAGE_BITMAP, 0, 0,
		LR_CREATEDIBSECTION | LR_LOADFROMFILE
	);


	GetObject(hBMP, sizeof(BMP), &BMP);


	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	DeleteObject(hBMP);

	return texture;
}

void loadTextures() {
	skyboxTextures[0] = loadTexture("background_front.bmp");
	skyboxTextures[1] = loadTexture("background_back.bmp");
	skyboxTextures[2] = loadTexture("background_left.bmp");
	skyboxTextures[3] = loadTexture("background_right.bmp");
	skyboxTextures[4] = loadTexture("background_top.bmp");
	skyboxTextures[5] = loadTexture("background_bottom.bmp");
}


void drawSkybox(GLuint textures[6]) {
	float size = 20.0f; // Size of the cube

	glEnable(GL_TEXTURE_2D);

	// Front face
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glTexCoord2f(0, 0); glVertex3f(-size, -size, size);
	glTexCoord2f(1, 0); glVertex3f(size, -size, size);
	glTexCoord2f(1, 1); glVertex3f(size, size, size);
	glTexCoord2f(0, 1); glVertex3f(-size, size, size);
	glEnd();

	// Back face
	glBindTexture(GL_TEXTURE_2D, textures[1]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(size, -size, -size);
	glTexCoord2f(1, 0); glVertex3f(-size, -size, -size);
	glTexCoord2f(1, 1); glVertex3f(-size, size, -size);
	glTexCoord2f(0, 1); glVertex3f(size, size, -size);
	glEnd();

	// Left face
	glBindTexture(GL_TEXTURE_2D, textures[2]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(-size, -size, -size);
	glTexCoord2f(1, 0); glVertex3f(-size, -size, size);
	glTexCoord2f(1, 1); glVertex3f(-size, size, size);
	glTexCoord2f(0, 1); glVertex3f(-size, size, -size);
	glEnd();

	// Right face
	glBindTexture(GL_TEXTURE_2D, textures[3]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(size, -size, size);
	glTexCoord2f(1, 0); glVertex3f(size, -size, -size);
	glTexCoord2f(1, 1); glVertex3f(size, size, -size);
	glTexCoord2f(0, 1); glVertex3f(size, size, size);
	glEnd();

	// Top face
	glBindTexture(GL_TEXTURE_2D, textures[4]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(-size, size, size);
	glTexCoord2f(1, 0); glVertex3f(size, size, size);
	glTexCoord2f(1, 1); glVertex3f(size, size, -size);
	glTexCoord2f(0, 1); glVertex3f(-size, size, -size);
	glEnd();

	// Bottom face
	glBindTexture(GL_TEXTURE_2D, textures[5]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(-size, -size, -size);
	glTexCoord2f(1, 0); glVertex3f(size, -size, -size);
	glTexCoord2f(1, 1); glVertex3f(size, -size, size);
	glTexCoord2f(0, 1); glVertex3f(-size, -size, size);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}


void drawCube(float expandX, float expandY, float expandZ, bool wireframe, float redValue, float greenValue, float blueValue) {
	if (wireframe) {
		glBegin(GL_LINE_LOOP);
		glLineWidth(5.0);
	}
	else {
		glBegin(GL_QUADS);
	}
	glColor3f(redValue, greenValue, blueValue);
	// Face 1 - front face 
	glTexCoord2f(0.0, 1.0);
	glVertex3f(0.0f, 0.0f, expandZ);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(expandX, 0.0f, expandZ);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(expandX, 0.0f, 0.0f);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(0.0f, 0.0f, 0.0f);

	// Face 2 - left face
	//glColor3f(1, 0, 1);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.0f, expandY, 0.0f);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.0f, expandY, expandZ);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(0.0f, 0.0f, expandZ);

	// Face 3 - top face
	//glColor3f(1, 1, 0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(0.0f, 0.0f, expandZ);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.0f, expandY, expandZ);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(expandX, expandY, expandZ);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(expandX, 0.0f, expandZ);

	// Face 4 - right face
	//glColor3f(0, 1, 0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(expandX, 0.0f, expandZ);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(expandX, expandY, expandZ);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(expandX, expandY, 0.0f);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(expandX, 0.0f, 0.0f);

	// Face 5 - bottom face
	//glColor3f(0, 0, 1);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(expandX, 0.0f, 0.0f);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.0f, expandY, 0.0f);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(expandX, expandY, 0.0f);

	// Face 6 - back face
	//glColor3f(0, 1, 1);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(expandX, expandY, 0.0f);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.0f, expandY, 0.0f);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.0f, expandY, expandZ);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(expandX, expandY, expandZ);
	glEnd();
}


void drawPyramid(float expandX, float expandY, float expandZ) {

	glBegin(GL_QUADS);
	// Base square
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 0, 0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(expandX, 0, 0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(expandX, 0, expandZ);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0, 0, expandZ);
	glEnd();


	glBegin(GL_TRIANGLES);
	// Sides
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 0, 0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(expandX, 0, 0);
	glTexCoord2f(0.5f, 1.0f); glVertex3f(expandX / 2, expandY, expandZ / 2);

	glTexCoord2f(1.0f, 0.0f); glVertex3f(expandX, 0, 0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(expandX, 0, expandZ);
	glTexCoord2f(0.5f, 1.0f); glVertex3f(expandX / 2, expandY, expandZ / 2);

	glTexCoord2f(1.0f, 1.0f); glVertex3f(expandX, 0, expandZ);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0, 0, expandZ);
	glTexCoord2f(0.5f, 1.0f); glVertex3f(expandX / 2, expandY, expandZ / 2);

	glTexCoord2f(0.0f, 1.0f); glVertex3f(0, 0, expandZ);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 0, 0);
	glTexCoord2f(0.5f, 1.0f); glVertex3f(expandX / 2, expandY, expandZ / 2);
	glEnd();
}

void drawRectangleLineLoop(float expandX, float expandY, float expandZ) {
	glLineWidth(5.0f);

	// Front face
	glColor3f(1, 1, 1);
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.0f, 0.0f, expandZ);
	glVertex3f(expandX, 0.0f, expandZ);
	glVertex3f(expandX, expandY, expandZ);
	glVertex3f(0.0f, expandY, expandZ);
	glEnd();

	// Back face
	glColor3f(1, 1, 1);
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(expandX, 0.0f, 0.0f);
	glVertex3f(expandX, expandY, 0.0f);
	glVertex3f(0.0f, expandY, 0.0f);
	glEnd();

	// Connecting edges (4 lines)
	glColor3f(1, 1, 1);
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, expandZ);

	glVertex3f(expandX, 0.0f, 0.0f);
	glVertex3f(expandX, 0.0f, expandZ);

	glVertex3f(expandX, expandY, 0.0f);
	glVertex3f(expandX, expandY, expandZ);

	glVertex3f(0.0f, expandY, 0.0f);
	glVertex3f(0.0f, expandY, expandZ);
	glEnd();
}



void drawSphere(float radius, GLenum style) {
	GLUquadricObj* sphere = NULL;	//create quadric obj pointer
	sphere = gluNewQuadric();		//create new quadric object in the memory
	gluQuadricTexture(sphere, true);
	gluQuadricDrawStyle(sphere, style);	//set the draw style to line
	gluSphere(sphere, radius, 30, 30);
	gluDeleteQuadric(sphere);	//delete the quadric object
}

void drawCylinder(float baseRadius, float topRadius, float height) {
	GLUquadricObj* cylinder = NULL;	//create quadric obj pointer
	cylinder = gluNewQuadric();		//create new quadric object in the memory
	gluQuadricTexture(cylinder, true);
	gluQuadricDrawStyle(cylinder, GLU_FILL);	//set the draw style to line
	gluCylinder(cylinder, baseRadius, topRadius, height, 30, 30);
	gluDeleteQuadric(cylinder);	//delete the quadric object
}

void drawCone(float baseRadius, float height) {
	GLUquadricObj* cone = NULL;	//create quadric obj pointer
	cone = gluNewQuadric();		//create new quadric object in the memory
	gluQuadricTexture(cone, true);
	gluQuadricDrawStyle(cone, GLU_FILL);	//set the draw style to line
	gluCylinder(cone, baseRadius, 0, height, 30, 30);
	gluDeleteQuadric(cone);	//delete the quadric object
}

void drawDisk(float innerRadius, float outerRadius) {
	GLUquadricObj* disk = NULL;	//create quadric obj pointer
	disk = gluNewQuadric();		//create new quadric object in the memory
	gluQuadricTexture(disk, true);
	gluQuadricDrawStyle(disk, GLU_POINT);	//set the draw style to line
	gluDisk(disk, innerRadius, outerRadius, 30, 30);
	gluDeleteQuadric(disk);	//delete the quadric object
}








void projection() {
	glMatrixMode(GL_PROJECTION);	//refer to the projection matrix
	glLoadIdentity();	//reset the projection matrix

	if (isOrtho) {
		//Ortho view
		glOrtho(-10.0, 10.0, -10.0 * (windowHeight / windowWidth), 10.0 * (windowHeight / windowWidth), ONear, OFar);

	}
	else {
		//Perspective view
		gluPerspective(45.0, windowWidth / windowHeight, PNear, PFar);
		//glFrustum(-10.0, 10.0, -10.0, 10.0, PNear, PFar);	//frustum view


	}

}



void exercise() {
	glClearColor(0, 0, 0, 0); // clear background with red
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);			//refer to the model view matrix
	glLoadIdentity();					//reset the model view matrix	


	//camera movement
	glScalef(zoomFactor, zoomFactor, zoomFactor);
	glTranslatef(translateX, translateY, translateZ);
	glRotatef(cameraAngleX, 1.0f, 0.0f, 0.0f);
	glRotatef(cameraAngleY, 0.0f, 1.0f, 0.0f);
	glRotatef(cameraAngleZ, 0.0f, 0.0f, 1.0f);
	glScalef(scale, scale, scale);

	drawSkybox(skyboxTextures);


	//sea
	glPushMatrix();
	glTranslatef(-25, -12.5, -25);
	drawCube(50, 10, 50, false, 0, 0, 0.72);
	glPopMatrix();

	GLuint textureArr[4];
	textureArr[0] = loadTexture("brick.bmp");
	//tower base
	glPushMatrix();
	glTranslatef(-3, -2, 0);
	glTranslatef(-1.1, -0.6, -1.1);
	drawCube(2.2, 1.2, 2.2, false, 0.3, 0.3, 0.3);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(3, -2, 0);
	glTranslatef(-1.1, -0.6, -1.1);
	drawCube(2.2, 1.2, 2.2, false, 0.3, 0.3, 0.3);
	glPopMatrix();
	glDeleteTextures(1, &textureArr[0]);

	textureArr[1] = loadTexture("brick.bmp");
	glPushMatrix();
	glTranslatef(-3, 0.2, 0);
	glTranslatef(-0.75, -2, -0.75);
	drawCube(1.5, 4, 1.5, false, 0.4, 0.4, 0.4);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(3, 0.2, 0);
	glTranslatef(-0.75, -2, -0.75);
	drawCube(1.5, 4, 1.5, false, 0.4, 0.4, 0.4);
	glPopMatrix();


	//cylinder
	glPushMatrix();
	glTranslatef(-3.7, -0.5, 0.7);
	glRotatef(90, 1, 0, 0);
	glColor3f(0.4, 0.4, 0.4);
	drawCylinder(0.2, 0.2, 1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-3.7, -0.5, -0.7);
	glRotatef(90, 1, 0, 0);
	glColor3f(0.4, 0.4, 0.4);
	drawCylinder(0.2, 0.2, 1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-2.3, -0.5, -0.7);
	glRotatef(90, 1, 0, 0);
	glColor3f(0.4, 0.4, 0.4);
	drawCylinder(0.2, 0.2, 1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-2.3, -0.5, 0.7);
	glRotatef(90, 1, 0, 0);
	glColor3f(0.4, 0.4, 0.4);
	drawCylinder(0.2, 0.2, 1);
	glPopMatrix();
	glDeleteTextures(1, &textureArr[1]);


	//cone
	textureArr[2] = loadTexture("soil.bmp");

	glPushMatrix();
	glTranslatef(-2.3, -0.5, 0.7);
	glRotatef(-90, 1, 0, 0);
	glColor3f(0.2, 0.2, 0.2);
	drawCone(0.2, 0.3);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-3.7, -0.5, 0.7);
	glRotatef(-90, 1, 0, 0);
	glColor3f(0.2, 0.2, 0.2);
	drawCone(0.2, 0.3);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-3.7, -0.5, -0.7);
	glRotatef(-90, 1, 0, 0);
	glColor3f(0.2, 0.2, 0.2);
	drawCone(0.2, 0.3);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-2.3, -0.5, -0.7);
	glRotatef(-90, 1, 0, 0);
	glColor3f(0.2, 0.2, 0.2);
	drawCone(0.2, 0.3);
	glPopMatrix();

	//top pyramid
	glPushMatrix();
	glTranslatef(-3.4, 3.2, -0.4);
	glTranslatef(-0.6, -1, -0.6);
	glColor3f(0.5, 0.35, 0.16);
	drawPyramid(2, 2.5, 2);
	glPopMatrix();

	glDeleteTextures(1, &textureArr[2]);




	//right side
	//cylinder
	textureArr[1] = loadTexture("brick.bmp");

	glPushMatrix();
	glTranslatef(3.7, -0.5, 0.7);
	glRotatef(90, 1, 0, 0);
	glColor3f(0.4, 0.4, 0.4);
	drawCylinder(0.2, 0.2, 1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(3.7, -0.5, -0.7);
	glRotatef(90, 1, 0, 0);
	glColor3f(0.4, 0.4, 0.4);
	drawCylinder(0.2, 0.2, 1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(2.3, -0.5, -0.7);
	glRotatef(90, 1, 0, 0);
	glColor3f(0.4, 0.4, 0.4);
	drawCylinder(0.2, 0.2, 1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(2.3, -0.5, 0.7);
	glRotatef(90, 1, 0, 0);
	glColor3f(0.4, 0.4, 0.4);
	drawCylinder(0.2, 0.2, 1);
	glPopMatrix();
	glDeleteTextures(1, &textureArr[1]);

	//cone
	textureArr[2] = loadTexture("soil.bmp");

	glPushMatrix();
	glTranslatef(2.3, -0.5, 0.7);
	glRotatef(-90, 1, 0, 0);
	glColor3f(0.2, 0.2, 0.2);
	drawCone(0.2, 0.3);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(3.7, -0.5, 0.7);
	glRotatef(-90, 1, 0, 0);
	glColor3f(0.2, 0.2, 0.2);
	drawCone(0.2, 0.3);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(3.7, -0.5, -0.7);
	glRotatef(-90, 1, 0, 0);
	glColor3f(0.2, 0.2, 0.2);
	drawCone(0.2, 0.3);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(2.3, -0.5, -0.7);
	glRotatef(-90, 1, 0, 0);
	glColor3f(0.2, 0.2, 0.2);
	drawCone(0.2, 0.3);
	glPopMatrix();

	//top pyramid
	glPushMatrix();
	glTranslatef(2.6, 3.2, -0.4);
	glTranslatef(-0.6, -1, -0.6);
	glColor3f(0.5, 0.35, 0.16);
	drawPyramid(2, 2.5, 2);
	glPopMatrix();
	glDeleteTextures(1, &textureArr[2]);


	//road aside
	textureArr[3] = loadTexture("Road.bmp");
	//road aside
	glPushMatrix();
	glTranslatef(-18, -1.5, 0);
	glTranslatef(-15, -0.15, -0.65);
	drawCube(30, 0.3, 1.3, false, 0.5, 0.5, 0.5);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(18, -1.5, 0);
	glTranslatef(-15, -0.15, -0.65);
	drawCube(30, 0.3, 1.3, false, 0.5, 0.5, 0.5);
	glPopMatrix();

	//bridge (left)
	glPushMatrix();
	glTranslatef(-1.96, -1.45, 0);
	glRotatef(leftBridgeRotationZ, 0, 0, 1);
	glTranslatef(0, -0.05, -0.65);
	drawCube(1.96, 0.1, 1.3, false, 0.36, 0.34, 0.31);

	//sides
	glBegin(GL_POLYGON);
	glColor3f(0.15, 0.75, 0.53);
	glVertex3f(0, -0.3, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(1.96, 0, 0);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.15, 0.75, 0.53);
	glVertex3f(0, -0.3, 1.3);
	glVertex3f(0, 0, 1.3);
	glVertex3f(1.96, 0, 1.3);
	glEnd();
	glPopMatrix();


	//bridge (right)
	glPushMatrix();
	glTranslatef(1.96, -1.45, 0);
	glRotatef(rightBridgeRotationZ, 0, 0, 1);
	glTranslatef(-1.96, -0.05, -0.65);
	drawCube(1.96, 0.1, 1.3, false, 0.36, 0.34, 0.31);

	//sides
	glBegin(GL_POLYGON);
	glColor3f(0.15, 0.75, 0.53);
	glVertex3f(1.96, -0.3, 0);
	glVertex3f(1.96, 0, 0);
	glVertex3f(0, 0, 0);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.15, 0.75, 0.53);
	glVertex3f(1.96, -0.3, 1.3);
	glVertex3f(1.96, 0, 1.3);
	glVertex3f(0, 0, 1.3);
	glEnd();
	glPopMatrix();
	glDeleteTextures(1, &textureArr[3]);

	//upper link
	glPushMatrix();
	glBegin(GL_LINES);
	glColor3f(0, 0, 0);
	glVertex3f(-3.2, 2, 0.4);
	glVertex3f(3.2, 2, 0.4);
	glVertex3f(-3.2, 2, -0.4);
	glVertex3f(3.2, 2, -0.4);
	glVertex3f(-3.2, 1.5, 0.4);
	glVertex3f(3.2, 1.5, 0.4);
	glVertex3f(-3.2, 1.5, -0.4);
	glVertex3f(3.2, 1.5, -0.4);
	glVertex3f(-3.2, 2, 0.4);
	glVertex3f(3.2, 1.5, 0.4);
	glVertex3f(-3.2, 2, -0.4);
	glVertex3f(3.2, 1.5, -0.4);
	glVertex3f(-3.2, 1.5, 0.4);
	glVertex3f(3.2, 2, 0.4);
	glVertex3f(-3.2, 1.5, -0.4);
	glVertex3f(3.2, 2, -0.4);

	//between
	glVertex3f(-2, 2, 0.4);
	glVertex3f(-2, 2, -0.4);
	glVertex3f(2, 2, 0.4);
	glVertex3f(2, 2, -0.4);
	glVertex3f(-2, 1.5, 0.4);
	glVertex3f(-2, 1.5, -0.4);
	glVertex3f(2, 1.5, 0.4);
	glVertex3f(2, 1.5, -0.4);
	glVertex3f(-1, 2, 0.4);
	glVertex3f(-1, 2, -0.4);
	glVertex3f(1, 2, 0.4);
	glVertex3f(1, 2, -0.4);
	glVertex3f(-1, 1.5, 0.4);
	glVertex3f(-1, 1.5, -0.4);
	glVertex3f(0, 1.5, 0.4);
	glVertex3f(0, 1.5, -0.4);
	glVertex3f(0, 2, 0.4);
	glVertex3f(0, 2, -0.4);
	glVertex3f(1, 1.5, 0.4);
	glVertex3f(1, 1.5, -0.4);


	glEnd();
	glPopMatrix();




}

void display()
{
	projection();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	exercise();
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
		700, 10, 800, 600,
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
	loadTextures();
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