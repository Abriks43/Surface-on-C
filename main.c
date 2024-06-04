#include <windows.h>
#include <gl/gl.h>
#include <math.h>;

#include "../_OpenGLFitch/camera.h"
#include "Surface.h"

void WndResize(int x, int y){
    glViewport(0,0, x,y);
    float koef = x / (float)y;
    float sz = 0.1;
    glLoadIdentity();
    glFrustum(-koef*sz,koef*sz, -sz,sz, sz*2,100);
}

void PlayerMove(){
    CameraMoveDiraction( GetKeyState('W') < 0 ? 1 : (GetKeyState('S') < 0 ? -1 : 0),
                        GetKeyState('D') < 0 ? 1 : (GetKeyState('A') < 0 ? -1 : 0),
                        0.1);
    CameraHight(GetKeyState(VK_SPACE) < 0 ? 1 : (GetKeyState(VK_SHIFT) < 0 ? -1 : 0), 0.3);
    CameraFollowToCurcor(400, 400, 0.2);


}





LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
void EnableOpenGL(HWND hwnd, HDC*, HGLRC*);
void DisableOpenGL(HWND, HDC, HGLRC);





int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow)
{
    WNDCLASSEX wcex;
    HWND hwnd;
    HDC hDC;
    HGLRC hRC;
    MSG msg;
    BOOL bQuit = FALSE;
    float theta = 0.0f;

    /* register window class */
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_OWNDC;
    wcex.lpfnWndProc = WindowProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = "GLSample";
    wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);;


    if (!RegisterClassEx(&wcex))
        return 0;

    /* create main window */
    hwnd = CreateWindowEx(0,
                          "GLSample",
                          "OpenGL Sample",
                          WS_OVERLAPPEDWINDOW,
                          CW_USEDEFAULT,
                          CW_USEDEFAULT,
                          700,
                          700,
                          NULL,
                          NULL,
                          hInstance,
                          NULL);

    ShowWindow(hwnd, nCmdShow);

    /* enable OpenGL for the window */
    EnableOpenGL(hwnd, &hDC, &hRC);

    RECT rct;
    GetClientRect(hwnd, &rct);
    WndResize(rct.right, rct.bottom);
    /* program main loop */
    while (!bQuit)
    {
        /* check for messages */
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            /* handle or dispatch messages */
            if (msg.message == WM_QUIT)
            {
                bQuit = TRUE;
            }
            else
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            /* OpenGL animation code goes here */

            glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            glPushMatrix();
                if(GetForegroundWindow() == hwnd)
                    CameraApply();
                PlayerMove();

                glLineWidth(10);
                glBegin(GL_LINES);
                    glColor3f(1,0,0);
                    glVertex3f(0,0,0); glVertex3f(20,0,0);
                    glColor3f(0.5,0,0);
                    glVertex3f(0,0,0); glVertex3f(-20,0,0);
                    glColor3f(0,1,0);
                    glVertex3f(0,0,0); glVertex3f(0,20,0);
                    glColor3f(0,0.5,0);
                    glVertex3f(0,0,0); glVertex3f(0,-20,0);
                    glColor3f(0,0,1);
                    glVertex3f(0,0,0); glVertex3f(0,0,20);
                    glColor3f(0,0,0.5);
                    glVertex3f(0,0,0); glVertex3f(0,0,-20);

                glEnd();
                ShowP();
                ShowP22();
                //WhiteLight();
                WhiteLight(60, 4,1,6);
 /*
                for(int k = 0; k < 4; k++){
                    glColor3f(k/4,0.1,0.3);
                    glPushMatrix();
                        glTranslatef(0, 0, 2*k);
                        glColor3f(k/3, 0.2, 0.2);
                        Egg3D(0, 40);
                    glPopMatrix();

                }

                glPushMatrix();
                        glTranslatef(6, 0, 0);
                        glColor3f(1,0 , 0);
                        Egg3D(0, 40);
                    glPopMatrix();
                glPushMatrix();
                        glTranslatef(0, 6, 0);
                        glColor3f(0,1 , 0);
                        Egg3D(0, 40);
                    glPopMatrix();
                glPushMatrix();
                        glTranslatef(0, 0, 6);
                        glColor3f(0,0 , 1);
                        Egg3D(0, 40);
                glPopMatrix();
*/
            glPopMatrix();

            SwapBuffers(hDC);

            theta += 1.0f;
            Sleep (1);
        }
    }

    /* shutdown OpenGL */
    DisableOpenGL(hwnd, hDC, hRC);

    /* destroy the window explicitly */
    DestroyWindow(hwnd);

    return msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_CLOSE:
            PostQuitMessage(0);
        break;

        case WM_DESTROY:
            return 0;

        case WM_KEYDOWN:
        {
            switch (wParam)
            {
                case VK_ESCAPE:
                    PostQuitMessage(0);
                break;
            }
        }
        break;

        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return 0;
}

void EnableOpenGL(HWND hwnd, HDC* hDC, HGLRC* hRC)
{
    PIXELFORMATDESCRIPTOR pfd;

    int iFormat;

    /* get the device context (DC) */
    *hDC = GetDC(hwnd);

    /* set the pixel format for the DC */
    ZeroMemory(&pfd, sizeof(pfd));

    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW |
                  PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;

    iFormat = ChoosePixelFormat(*hDC, &pfd);

    SetPixelFormat(*hDC, iFormat, &pfd);

    /* create and enable the render context (RC) */
    *hRC = wglCreateContext(*hDC);

    wglMakeCurrent(*hDC, *hRC);
}

void DisableOpenGL (HWND hwnd, HDC hDC, HGLRC hRC)
{
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(hRC);
    ReleaseDC(hwnd, hDC);
}

