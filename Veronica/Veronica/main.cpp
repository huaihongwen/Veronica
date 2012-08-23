/*
 * main.cpp
 * TODO: Reconstruct this file later
 */

#include <fcntl.h>
#include <io.h>
#include <stdio.h>

// Windows and OpenGL
#include <windows.h>
#include <GL\glew.h>

// Our stuffs
#include "veEditor.h"
using namespace vee;



// Globals
HDC	hDC = NULL; // Device context, which connects window to GDI
HGLRC hRC = NULL; // Rendering context, which connects OpenGL to DC

HWND hWnd = NULL; // Window handler

HINSTANCE hInstance; // Instance of our application

// TODO: Input system
bool keys[256]; // Array for keyboard

bool active = TRUE; // Is window being minimized?
bool fullscreen = TRUE;	// Fullscreen



// Mouse position
POINT mousePos;
// Editor
Editor* gEditor;
// Terrain editor
//TerrainEditor* gTerrainEditor;


// Declaration For WndProc
LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//---------------------------------------------------------------
// Resize window callback
GLvoid resizeGLScene(GLsizei width, GLsizei height) {
	// Prevent divide by zero
	if (height == 0) {
		height = 1;
	}

	// Resize stuffs
}

//---------------------------------------------------------------
// Initialize
int initGL(GLvoid) {

	// TODO: Rendering system?
	// OpenGL settings
	glShadeModel(GL_SMOOTH);


	// Clear
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);


	// Depth test
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);


	// Perspective calculation?
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	

	// Blend
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	// Initialize glew, for OpenGL extension stuffs
	GLenum error = glewInit();


	// Our stuffs
	// Editor init
	gEditor = new Editor();
	gEditor->init();

	// File system need window handler
	gEditor->mFileSystem->mHWnd = hWnd;

	// Terrain editor
	//gTerrainEditor = new TerrainEditor();
	//gTerrainEditor->init();


	return TRUE;
}

//---------------------------------------------------------------
// Render scene
int drawGLScene(GLvoid) {

	gEditor->update();
	gEditor->render();

	//gTerrainEditor->update();
	//gTerrainEditor->render();


	// FPS
	char fps[20];
	sprintf_s(fps, "%d", (int)gEditor->getTimer()->getFPS());
	//sprintf_s(fps, "%d", (int)gTerrainEditor->getTimer()->getFPS());
	SetWindowText(hWnd, fps);

	return TRUE;
}

//---------------------------------------------------------------
// Destroy
void destroyGL() {
}

//---------------------------------------------------------------
// Program quits callback, kills the RC, DC and our window
GLvoid killGLWindow(GLvoid) {

	// Quicks fullscreen mode
	if (fullscreen) {
		// Switch back to desktop
		ChangeDisplaySettings(NULL,0);
		// Show mouse pointer
		ShowCursor(TRUE);
	}

	// If we have RC
	if (hRC) {
		// Detach RC from DC
		if (!wglMakeCurrent(NULL,NULL)) {
			MessageBox(NULL,"Release Of DC And RC Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}
		// Delete RC
		if (!wglDeleteContext(hRC)) {
			MessageBox(NULL,"Release Rendering Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}

		hRC = NULL;
	}

	// Release DC
	if (hDC && !ReleaseDC(hWnd,hDC)) {
		MessageBox(NULL,"Release Device Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);

		hDC = NULL;	
	}

	// Destroy window
	if (hWnd && !DestroyWindow(hWnd)) {
		MessageBox(NULL,"Could Not Release hWnd.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);

		hWnd = NULL;
	}

	// Unregister our window class
	if (!UnregisterClass("OpenGL",hInstance)) {
		MessageBox(NULL,"Could Not Unregister Class.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);

		hInstance=NULL;
	}
}

//---------------------------------------------------------------
/* Create OpenGL window
 * @param title {char*} title on top of the window
 * @param width {int} width of the window
 * @param height {int} height of the window
 * @param bits {int} number of bits for color (8/16/24/32)
 * @param fullscreenflay {book} fullscreen mode
 */
BOOL createGLWindow(char* title, int width, int height, int bits, bool fullscreenflag) {

	// Pixel format
	GLuint PixelFormat;
	// Window class
	WNDCLASS wc;

	// Window extended style
	DWORD dwExStyle;
	// Window style
	DWORD dwStyle;

	// Window rect
	RECT WindowRect;
	WindowRect.left = (long)0;
	WindowRect.right = (long)width;
	WindowRect.top = (long)0;
	WindowRect.bottom = (long)height;

	// Global fullscreen flag
	fullscreen = fullscreenflag;

	// Grab an instance for our window
	hInstance = GetModuleHandle(NULL);


	// Setup window class
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC; // Redraw on resize, own DC for window
	wc.lpfnWndProc = (WNDPROC) WndProc; // WndProc handles messages

	wc.cbClsExtra = 0; // No extra window data
	wc.cbWndExtra = 0; // No extra window data

	wc.hInstance = hInstance; // Setup instance

	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO); // Load default icon
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); // Load arrow cursor

	wc.hbrBackground = NULL; // No back ground
	wc.lpszMenuName	= NULL; // No menu

	wc.lpszClassName = "OpenGL"; // Window class name


	// Try to register the window class
	if (!RegisterClass(&wc)) {
		MessageBox(NULL,"Failed To Register The Window Class.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;
	}
	
	// Try to make fullscreen mode
	if (fullscreen) {

		// Device mode
		DEVMODE dmScreenSettings;
		memset(&dmScreenSettings,0,sizeof(dmScreenSettings));

		// Setup device mode
		dmScreenSettings.dmSize=sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = width;
		dmScreenSettings.dmPelsHeight = height;
		dmScreenSettings.dmBitsPerPel = bits;
		dmScreenSettings.dmFields=DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;

		// Try to setup fullscreen mode
		if (ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL) {
			
			// Back to window mode or quit
			if (MessageBox(NULL,"The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?","NeHe GL",
				MB_YESNO|MB_ICONEXCLAMATION)==IDYES) {
				// Back to window mode
				fullscreen=FALSE;

			} else {
				MessageBox(NULL,"Program Will Now Close.","ERROR",MB_OK|MB_ICONSTOP);
				// Quick
				return FALSE;
			}
		}
	}

	// Setup styles for fullscreen or window mode
	if (fullscreen) {
		// Full screen mode
		dwExStyle=WS_EX_APPWINDOW;
		dwStyle=WS_POPUP;

		// Hide cursor
		ShowCursor(FALSE);

	} else {
		// Window mode
		dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
		dwStyle=WS_OVERLAPPEDWINDOW;
	}

	// Adjust window to requested size
	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);

	// Create window
	if (!(hWnd=CreateWindowEx(	dwExStyle, // Window extended style
								"OpenGL", // Window class name
								title, // Window title
								dwStyle | // Window style
								WS_CLIPSIBLINGS | // Required window style
								WS_CLIPCHILDREN, // Required window style
								0, 0, // Window position
								WindowRect.right-WindowRect.left, // Width
								WindowRect.bottom-WindowRect.top, // Height
								NULL, // No parent window
								NULL, // No menu
								hInstance, // Instance
								NULL))) // Do not pass anything to WM_CREATE
	{
		// We can not create window, kill window and quick
		killGLWindow();
		MessageBox(NULL,"Window Creation Error.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;
	}

	// Setup pixel format descriptor
	static	PIXELFORMATDESCRIPTOR pfd = {

		sizeof(PIXELFORMATDESCRIPTOR), // Size of the pixel format descriptor
		1, // Version number

		PFD_DRAW_TO_WINDOW | // Format must support window
		PFD_SUPPORT_OPENGL | // Format must support OpenGL
		PFD_DOUBLEBUFFER,// Format must support double buffering

		PFD_TYPE_RGBA, // RGBA
		bits, // Color depth
		0, 0, 0, 0, 0, 0, // Color bits ignored

		0, // No alpha buffer
		0, // Shift bit ignored
		0, // No accumulation buffer
		0, 0, 0, 0, // Accumulation bits ignored
		16, // 16 bit z-buffer(depth buffer)
		0, // No stencil buffer
		0, // No auxiliary buffer

		PFD_MAIN_PLANE,	// Main drawing layer
		0, // Reserved
		0, 0, 0 // Layer masks ignored
	};
	
	// Get DC for window
	if (!(hDC=GetDC(hWnd))) {

		// Kill window and quit
		killGLWindow();
		MessageBox(NULL,"Can't Create A GL Device Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;
	}

	// Can we find a matched pixel format?
	if (!(PixelFormat=ChoosePixelFormat(hDC,&pfd))) {

		// Kill window and quit
		killGLWindow();
		MessageBox(NULL,"Can't Find A Suitable PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;
	}

	// Try to set the pixel format for DC
	if(!SetPixelFormat(hDC,PixelFormat,&pfd)) {

		// Kill window and quit
		killGLWindow();
		MessageBox(NULL,"Can't Set The PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;
	}

	// Create the RC from DC
	if (!(hRC=wglCreateContext(hDC))) {

		// Kill window and quit
		killGLWindow();
		MessageBox(NULL,"Can't Create A GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;
	}

	// Make current RC active, I guess after this, we can use OpenGL functionalities
	if(!wglMakeCurrent(hDC,hRC)) {

		// Kill window and quit
		killGLWindow();
		MessageBox(NULL,"Can't Activate The GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;
	}

	// Show window
	ShowWindow(hWnd,SW_SHOW);
	// Give slightly higher priority to our window
	SetForegroundWindow(hWnd);
	// Set keyboard focus to our window
	SetFocus(hWnd);

	// Setup OpenGL modelview and projection matrices
	resizeGLScene(width, height);

	// Initialze our stuffs
	if (!initGL()) {

		// Kill window and quit
		killGLWindow();
		MessageBox(NULL,"Initialization Failed.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;
	}		

	return TRUE;
}

//---------------------------------------------------------------
/* WndProc for handling messages
 * @param hWnd {HWND} handle for the window
 * @param uMsg {UINT} message
 * @param wParam {WPARAM} message param
 * @param lParam {LPARAM} message param
 */
LRESULT CALLBACK WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	// Message
	switch (uMsg) {
	
	// Window active message
	case WM_ACTIVATE: 
		{
			if (!HIWORD(wParam)) {
				active = TRUE;	
			} else {
				active=FALSE;
			}
			return 0;
		}

	// System commands
	case WM_SYSCOMMAND:
		{
			switch (wParam) {
			case SC_SCREENSAVE:
			case SC_MONITORPOWER:
				return 0;
			}
			break;
		}

	// Close message
	case WM_CLOSE:
		{
			// Post quit message
			PostQuitMessage(0);
			return 0;
		}

	// Key pressed down
	case WM_KEYDOWN:
		{
			keys[wParam] = TRUE;


			// Editor key down
			gEditor->keyDown(wParam);

			return 0;
		}

		// Key released
	case WM_KEYUP:
		{
			keys[wParam] = FALSE;


			// Editor key up
			gEditor->keyUp(wParam);

			return 0;
		}

	case WM_CHAR:
		{
			// Editor key pressed
			gEditor->keyPressed(wParam);
			return 0;
		}

	// Mouse move
	case WM_MOUSEMOVE:
		{
			// Get screen mouse position
			GetCursorPos(&mousePos);
			// Get client mouse position
			ScreenToClient(hWnd, &mousePos);

			// Editor mouse move
			gEditor->mouseMove(mousePos.x, mousePos.y);

			return 0;
		}

	// Mouse left button down
	case WM_LBUTTONDOWN:
		{
			// Get screen mouse position
			GetCursorPos(&mousePos);
			// Get client mouse position
			ScreenToClient(hWnd, &mousePos);


			// Editor mouse left button down
			gEditor->mouseLDown(mousePos.x, mousePos.y);

			return 0;
		}

	// Mouse left button up
	case WM_LBUTTONUP:
		{
			// Get screen mouse position
			GetCursorPos(&mousePos);
			// Get client mouse position
			ScreenToClient(hWnd, &mousePos);


			// Editor mouse left button up
			gEditor->mouseLUp(mousePos.x, mousePos.y);

			return 0;
		}

	// Resize window
	case WM_SIZE:
		{
			// Resize the window, probably we don't need to resize?
			resizeGLScene(LOWORD(lParam),HIWORD(lParam));
			return 0;
		}
	}

	// Unhandled messge passed to default wndproc
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}

//---------------------------------------------------------------
/* WndProc for handling messages
 * @param hInstance {HINSTANCE} instance
 * @param hPrevInstance {HINSTANCE} previous instance
 * @param lpCmdLine {LPSTR} command line parameters
 * @param nCmdShow {int} window show state
 */
int WINAPI WinMain(	HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	
	// Create a console for output
	int hCrt;
	int set;
	FILE* hf;

	AllocConsole();			

	// Redirect stardand output
	hCrt = _open_osfhandle((long) GetStdHandle(STD_OUTPUT_HANDLE), _O_TEXT);
	hf = _fdopen( hCrt, "w" );
	*stdout = *hf;
	set = setvbuf( stdout, NULL, _IONBF, 0 );
				

	// Window message
	MSG msg;
	BOOL done = FALSE;
	// Fullscreen?
	fullscreen = FALSE;

	// Create OpenGL window
	if (!createGLWindow("Veronica",EDITWINDOWWIDTH,EDITWINDOTHEIGHT,16,fullscreen)) {
		return 0;
	}

	// Loop
	while(!done)
	{
		// Get message
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE)) {

			// Quit message?
			if (msg.message==WM_QUIT) {
				done=TRUE;
			} else {
				// Translate message
				TranslateMessage(&msg);
				// Dispatch message
				DispatchMessage(&msg);
			}
		} else {
			
			// Window active?
			if (active) {

				// Escape pressed?, TODO: input system
				if (keys[VK_ESCAPE]) {
					done=TRUE;
				} else {

					// Render scene
					drawGLScene();
					// Swap buffers
					SwapBuffers(hDC);
				}
			}

			// Control camera
			if (keys['W']) {
				gEditor->getCamera().onCameraMove(true, true);
			}
			if (keys['S']) {
				gEditor->getCamera().onCameraMove(true, false);
			}
			if (keys['A']) {
				gEditor->getCamera().onCameraMove(false, false);
			}
			if (keys['D']) {
				gEditor->getCamera().onCameraMove(false, true);
			}
		}
	}

	// Destroy all stuffs here
	destroyGL();

	// Kill the window
	killGLWindow();
	return (msg.wParam);
}
