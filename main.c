#include "ckit.h"
#include "main.h"

#include <stdio.h>
#include <windows.h>
#include <gl/gl.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void EnableOpenGL(HWND hWnd, HDC * hDC, HGLRC * hRC);
void DisableOpenGL(HWND hWnd, HDC hDC, HGLRC hRC);

BOOL CenterWindow(HWND hwndWindow)
{
     HWND hwndParent;
     RECT rectWindow, rectParent;

     int nScreenWidth = GetSystemMetrics(SM_CXSCREEN);
     int nScreenHeight = GetSystemMetrics(SM_CYSCREEN);

     GetWindowRect(hwndWindow, &rectWindow);
     rectParent.left   = 0;
     rectParent.top    = nScreenHeight;
     rectParent.right  = nScreenWidth;
     rectParent.bottom = 0;

     int nWidth = rectWindow.right - rectWindow.left;
     int nHeight = rectWindow.bottom - rectWindow.top;

     int nX = ((rectParent.right - rectParent.left) - nWidth) / 2 + rectParent.left;
     int nY = ((rectParent.bottom - rectParent.top) - nHeight) / 2 + rectParent.top;

     // make sure that the dialog box never moves outside of the screen
     if (nX < 0) nX = 0;
     if (nY < 0) nY = 0;
     if (nX + nWidth > nScreenWidth) nX = nScreenWidth - nWidth;
     if (nY + nHeight > nScreenHeight) nY = nScreenHeight - nHeight;

     MoveWindow(hwndWindow, nX, nY, nWidth, nHeight, TRUE);

     return TRUE;
}

int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int iCmdShow)
{
    WNDCLASS wc;
    HWND hWnd;
    HDC hDC;
    HGLRC hRC;
    MSG msg;
    BOOL quit = FALSE;
    float theta = 0.0f;
	
    // register window class
    wc.style = CS_OWNDC;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon( NULL, IDI_APPLICATION );
    wc.hCursor = LoadCursor( NULL, IDC_ARROW );
    wc.hbrBackground = (HBRUSH)GetStockObject( BLACK_BRUSH );
    wc.lpszMenuName = NULL;
    wc.lpszClassName = "GLSample";
    RegisterClass( &wc );
	
    // create main window
    hWnd = CreateWindow("GLSample", "OpenGL Sample", 
                        WS_CAPTION | WS_POPUPWINDOW | WS_VISIBLE,
                        0, 0, 1100, 700,
                        NULL, NULL, hInstance, NULL);

    if (!CenterWindow(hWnd))
    {
        MessageBox(0, "CenterWindow fail", "Caption", 0);
    }
    
    // enable OpenGL for the window
    EnableOpenGL(hWnd, &hDC, &hRC);

    // Create obj array
    AllocConsole();
    freopen( "CONOUT$", "wb", stdout);
    array_obj a;
    array_obj_construct(&a);
    obj o;
    o.radius = 9.9;
    o.location[0] = 3.3;
    array_obj_pushback(&a, o);
    array_obj_print(a.data, a.size);
    
    // program main loop
    while (!quit)
    {
        // check for messages
        if ( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE )  )
        {
            // handle or dispatch messages
            if (msg.message == WM_QUIT) 
            {
                quit = TRUE;
            } 
            else 
            {
                TranslateMessage( &msg );
                DispatchMessage( &msg );
            }
        } 
        else 
        {
            //  Enable Z-buffer depth test
            glEnable(GL_DEPTH_TEST);

            // Rotate when user changes rotate_x and rotate_y
            glRotatef(0.5, 1.0, 0.0, 0.0);
            glRotatef(0.5, 0.0, 1.0, 0.0);
 
            // OpenGL animation code goes here
            glClearColor( 0.3f, 0.3f, 0.3f, 0.0f );
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            //Multi-colored side - FRONT
            glBegin(GL_POLYGON);
            glColor3f( 1.0, 0.0, 0.0 );     glVertex3f(  0.5, -0.5, -0.5 );      // P1 is red
            glColor3f( 0.0, 1.0, 0.0 );     glVertex3f(  0.5,  0.5, -0.5 );      // P2 is green
            glColor3f( 0.0, 0.0, 1.0 );     glVertex3f( -0.5,  0.5, -0.5 );      // P3 is blue
            glColor3f( 1.0, 0.0, 1.0 );     glVertex3f( -0.5, -0.5, -0.5 );      // P4 is purple
            glEnd();

            // White side - BACK
            glBegin(GL_POLYGON);
            glColor3f(   1.0,  1.0, 1.0 );
            glVertex3f(  0.5, -0.5, 0.5 );
            glVertex3f(  0.5,  0.5, 0.5 );
            glVertex3f( -0.5,  0.5, 0.5 );
            glVertex3f( -0.5, -0.5, 0.5 );
            glEnd();
             
            // Purple side - RIGHT
            glBegin(GL_POLYGON);
            glColor3f(  1.0,  0.0,  1.0 );
            glVertex3f( 0.5, -0.5, -0.5 );
            glVertex3f( 0.5,  0.5, -0.5 );
            glVertex3f( 0.5,  0.5,  0.5 );
            glVertex3f( 0.5, -0.5,  0.5 );
            glEnd();
             
            // Green side - LEFT
            glBegin(GL_POLYGON);
            glColor3f(   0.0,  1.0,  0.0 );
            glVertex3f( -0.5, -0.5,  0.5 );
            glVertex3f( -0.5,  0.5,  0.5 );
            glVertex3f( -0.5,  0.5, -0.5 );
            glVertex3f( -0.5, -0.5, -0.5 );
            glEnd();
             
            // Blue side - TOP
            glBegin(GL_POLYGON);
            glColor3f(   0.0,  0.0,  1.0 );
            glVertex3f(  0.5,  0.5,  0.5 );
            glVertex3f(  0.5,  0.5, -0.5 );
            glVertex3f( -0.5,  0.5, -0.5 );
            glVertex3f( -0.5,  0.5,  0.5 );
            glEnd();
             
            // Red side - BOTTOM
            glBegin(GL_POLYGON);
            glColor3f(   1.0,  0.0,  0.0 );
            glVertex3f(  0.5, -0.5, -0.5 );
            glVertex3f(  0.5, -0.5,  0.5 );
            glVertex3f( -0.5, -0.5,  0.5 );
            glVertex3f( -0.5, -0.5, -0.5 );
            glEnd();

            glFlush();

            SwapBuffers( hDC );
                
            theta += 1.0f;

            Sleep(10);
        }
    }
    
    // shutdown OpenGL
    DisableOpenGL(hWnd, hDC, hRC);
    
    // destroy the window explicitly
    DestroyWindow(hWnd);
    
    return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
        return 0;
            
    case WM_CLOSE:
        PostQuitMessage(0);
        return 0;
            
    case WM_DESTROY:
        return 0;
            
    case WM_KEYDOWN:
        switch (wParam)
        {
            case VK_ESCAPE:
                PostQuitMessage(0);
                return 0;
        }
        return 0;
    
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
}

void EnableOpenGL(HWND hWnd, HDC * hDC, HGLRC * hRC)
{
    PIXELFORMATDESCRIPTOR pfd;
    int format;
    
    // get the device context (DC)
    *hDC = GetDC(hWnd);
    
    // set the pixel format for the DC
    ZeroMemory(&pfd, sizeof(pfd));
    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;
    format = ChoosePixelFormat(*hDC, &pfd);
    SetPixelFormat(*hDC, format, &pfd);
    
    // create and enable the render context (RC)
    *hRC = wglCreateContext(*hDC);
    wglMakeCurrent(*hDC, *hRC);
}

void DisableOpenGL(HWND hWnd, HDC hDC, HGLRC hRC)
{
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(hRC);
    ReleaseDC(hWnd, hDC);
}

