/***************************************************
* Star Cat Engine                                  *
* Open Source, 2021 Stxq stxq_928@163.com          *
*                                                  *
* This file is the main file of SCE                *
*                                                  *
* There is some function about Graphic IO          *
* It is under development                          *
*                                                  *
* @file   StarCatEngine.h                          *
* @brief                                           *
* Datails.                                         *
*                                                  *
* @author  Stxq                                    *
* @email   stxq_928@163.com                        *
* @version 0.1.0.5 Alpha                           *
* @date    stxq_928@163.com                        *
* @license Mozilla Public License 2.0 (MPL)        *
*                                                  *
*--------------------------------------------------*
* Remark  The development phase                    *
*--------------------------------------------------*
* Change history :                                 *
* 2022/5/18 | 0.1.0.0 Alpha | Stxq | Create        *
*--------------------------------------------------*
* 2022/5/18 | 0.1.0.1 Alpha | Stxq | CreateWindow  *
*--------------------------------------------------*
* 2022/5/19 | 0.1.0.2 Alpha | Stxq | Window color  *
*--------------------------------------------------*
* 2022/5/20 | 0.1.0.3.1     | Stxq | drawrectangle *
*           | 0.1.0.3.2     | Stxq | drawline      *
*--------------------------------------------------*
* 2022/5/21 | 0.1.0.4 Alpha | Stxq | Output info   *
*--------------------------------------------------*
* 2022/5/22 | failed        | Stxq | try circle    *
* -------------------------------------------------*
* 2022/5/21 | 0.1.0.5 Alpha | Stxq | event system  *
***************************************************/
#ifndef SCEngine_h
#define SCEngine_h
#include <windows.h>
#include <gl/gl.h>
#include <gl/glext.h>
#include <gl/glu.h>
#include <gl/glaux.h>
#include <vector>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <time.h>
#include <string>
#include <iostream>
#include <gl/wglext.h>
#define version "0.1.0.5 Alpha"
#define glversion glGetString(GL_VERSION)
#define gluversion gluGetString(GLU_VERSION)
#define main() WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)

using namespace std;
/**
* namespace
* @brief private namespace
* some private function
*/
namespace{
    /**
    * function EnableOpengl
    * @brief Configure Opengl
    * @param hwnd HWND:Windows hwnd
    * @param hDC  HDC :Device Context
    * @param hRC  HRC :Rendering context
    *
    * @return void
    */
    void EnableOpenGL(HWND hwnd, HDC* hDC, HGLRC* hRC){
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
    /**
    * function DisableOpengl
    * @brief delete Context
    * @param hwnd HWND:Windows hwnd
    * @param hDC  HDC :Device Context
    * @param hRC  HRC :Rendering context
    *
    * @return void
    */
    void DisableOpenGL (HWND hwnd, HDC hDC, HGLRC hRC){
        wglMakeCurrent(NULL, NULL);
        wglDeleteContext(hRC);
        ReleaseDC(hwnd, hDC);
    }
}
/**
* namespace SCE
* @brief Main SCE
* there is all function which you need
*/
namespace SCE{
    /**
    *enum SCkey
    * @brief the enum of the keys
    */
    enum SCkey{
         SCkey_Back=0x08,
         SCkey_Tab=0X09,
         SCkey_Enter=0x0d,
         SCkey_Shift=0x10,
         SCkey_Ctrl=0x10,
         SCkey_Alt=0x12,
         SCkey_Pause=0x13,
         SCkey_Capslock=0x14,
         SCkey_Esc=0x1b,
         SCkey_Space=0x20,
         SCkey_Pgup=0x21,
         SCkey_Pgdn=0x22,
         SCkey_End=0x23,
         SCkey_Home=0x24,
         SCkey_Left=0x25,
         SCkey_Up=0x26,
         SCkey_Right=0x27,
         SCkey_Down=0x28,
         SCkey_Delete=0x2E,
         SCkey_0=0x30,
         SCkey_1=0x31,
         SCkey_2=0x32,
         SCkey_3=0x33,
         SCkey_4=0x34,
         SCkey_5=0x35,
         SCkey_6=0x36,
         SCkey_7=0x37,
         SCkey_8=0x38,
         SCkey_9=0x39,
         SCkey_A=0x41,
         SCkey_B=0x42,
         SCkey_C=0x43,
         SCkey_D=0x44,
         SCkey_E=0x45,
         SCkey_F=0x46,
         SCkey_G=0x47,
         SCkey_H=0x48,
         SCkey_I=0x49,
         SCkey_J=0x4a,
         SCkey_K=0x4b,
         SCkey_L=0x4c,
         SCkey_M=0x4d,
         SCkey_N=0x4e,
         SCkey_O=0x4f,
         SCkey_P=0x50,
         SCkey_Q=0x51,
         SCkey_R=0x52,
         SCkey_S=0x53,
         SCkey_T=0x54,
         SCkey_U=0x55,
         SCkey_V=0x56,
         SCkey_W=0x57,
         SCkey_X=0x58,
         SCkey_Y=0x59,
         SCkey_Z=0x5a,
         SCkey_num_0=0x60,
         SCkey_num_1=0x61,
         SCkey_num_2=0x62,
         SCkey_num_3=0x63,
         SCkey_num_4=0x64,
         SCkey_num_5=0x65,
         SCkey_num_6=0x66,
         SCkey_num_7=0x67,
         SCkey_num_8=0x68,
         SCkey_num_9=0x69,
         SCkey_multiple=0x6a,
         SCkey_plus=0x6b,
         SCkey_separator=0x6c,
         SCkey_subtract=0x6d,
         SCkey_divide=0x6f,
         SCkey_F1=0x70,
         SCkey_F2=0x71,
         SCkey_F3=0x72,
         SCkey_F4=0x73,
         SCkey_F5=0x74,
         SCkey_F6=0x75,
         SCkey_F7=0x76,
         SCkey_F8=0x77,
         SCkey_F9=0x78,
         SCkey_F10=0x79,
         SCkey_F11=0x7a,
         SCkey_F12=0x7b,
         SCkey_F13=0x7c,
         SCkey_F14=0x7d,
         SCkey_F15=0x7e,
         SCkey_F16=0x7f,
         SCkey_F17=0x80,
         SCkey_F18=0x81,
         SCkey_F19=0x82,
         SCkey_F20=0x83,
         SCkey_F21=0x84,
         SCkey_F22=0x85,
         SCkey_F23=0x86,
         SCkey_F24=0x87,
         SCkey_Numlock=0x90,
         SCkey_Lshift=0xa0,
         SCkey_Rshift=0xa1,
         SCkey_Lctrl=0xa2,
         SCkey_Rctrl=0xa3,
         SCkey_Lalt=0xa4,
         SCkey_Ralt=0xa5
    };
    /**enum SCmouse
    * @brief the enum of the mouse button
    */
    enum SCmouse{
        SCM_Left=0x01,
        SCM_Right=0x02,
        SCM_Middle=0x04,
        SCM_X1=0x05,
        SCM_X2=0x06
    };
    /**
    * function isKeydown
    * @brief test if key is down
    * @param key SCkey : the key which is tested
    * @return
    *      bool ---if key is down,return true
    *           ---else return false
    */
    bool isKeydown(SCkey key){
        return GetAsyncKeyState(key)&&0x8000;
    }
    /**
    * class sc2d
    * @brief save 2d information
    * an important class , save x,y
    */
    class sc2d{
        public:
            GLfloat x;
            GLfloat y;
            sc2d(GLfloat x,GLfloat y){
                this->x=x;
                this->y=y;
            }
    };
    /**
    * typedef wsize (sc2d)
    * @brief window size
    * save a window size information
    */
    typedef sc2d wsize;
    /**
    * typedef vector2d (sc2d)
    * @brief 2d vector
    * save a position information
    */
    typedef sc2d vector2d;
    /**
    * class SCColor
    * @brief color A R G B
    * save color as Alpha Red Green Blue
    */
    class SCColor{
        public:
            GLclampf R;
            GLclampf G;
            GLclampf B;
            GLclampf A;
            /**
            * construct function SCColor
            * @brief construct a SCColor object
            * @param A GLclampf : alpha
            * @param R GLclampf : red
            * @param G GLclampf : green
            * @param B GLclampf : blue
            *
            * @code
            * SCE::SCColor(255,255,255,255) //means white
            * @endcode
            * @see opengl glColor()
            */
            SCColor(float A,float R,float G,float B){
                this->A=A/255;
                this->R=R/255;
                this->G=G/255;
                this->B=B/255;
            }
    };
    /**
    * class SCEwindow
    * @brief a class of window which can draw
    * save window's infomation and function
    */
    class SCEwindow{
        public:
            ///ifnmax bool
            /**ifnmax =true the max botton is grey,else can be press*/
            bool ifnmax;
            HINSTANCE g_windows_instance= 0;
            /// hwnd HWND : the window's hwnd
            HWND hwnd;
            wstring Cap;
            wsize *Windowsize;
            HDC dc;
            HGLRC cc;
            int id;
            ///run bool,save if the windows running
            bool run=true;
            /**construct function SCEwindowa()
            * pass(No function)
            */
            SCEwindow(){}
            /**
            * function resetsize
            * @brief reset the size of the windows
            * @param y int : window's size's wide
            * @param x int : window's size's wide
            */
            void resetsize(int x,int y){
                Windowsize=new wsize(x,y);
                DestroyWindow(hwnd);
                if (ifnmax)
                    hwnd= CreateWindowW(L"SCEngineWindows",Cap.c_str(),WS_OVERLAPPED|WS_CAPTION|WS_SYSMENU|WS_MINIMIZEBOX,38,20,x,y,NULL,NULL,g_windows_instance,NULL);
                else
                    hwnd= CreateWindowW(L"SCEngineWindows",Cap.c_str(),WS_OVERLAPPEDWINDOW,38,20,x,y,NULL,NULL,g_windows_instance,NULL);
                cout<<"更新句柄:"<<hwnd<<endl;
                cout<<"窗口新大小：("<<x<<","<<y<<")"<<endl;
            }
            /**
            * function setcap
            * @brief set the caption
            * @param c wstring : the new caption(wchar_t)
            */
            void setcap(wstring c){
                Cap=c;
                DestroyWindow(hwnd);
                if (ifnmax)
                    hwnd= CreateWindowW(L"SCEngineWindows",c.c_str(),WS_OVERLAPPED|WS_CAPTION|WS_SYSMENU|WS_MINIMIZEBOX,38,20,Windowsize->x,Windowsize->y,NULL,NULL,g_windows_instance,NULL);
                else
                    hwnd= CreateWindowW(L"SCEngineWindows",c.c_str(),WS_OVERLAPPEDWINDOW,38,20,Windowsize->x,Windowsize->y,NULL,NULL,g_windows_instance,NULL);
                cout<<"更新句柄:"<<hwnd<<endl;
                cout<<"新标题："<<endl;
                wprintf(c.c_str());
            }
            /**
            * function startdraw
            * @brief start rendering
            * @param color SCColor = SCColor(0,0,0,0) : BGcolor @see line 154-179, class SCColor
            * there get the massage and start the rendering ,it is most important function in the main loop
            */
            void startdraw(SCColor color=SCColor(0,0,0,0)){
                MSG msg;
                ShowWindow(hwnd,SW_SHOW|SW_NORMAL);
                if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)&& msg.message!=WM_PAINT){
                /* handle or dispatch messages */
                    if (msg.message == WM_QUIT){
                        cerr<<"更改run状态……"<<endl;
                        run = false;
                    }else{
                        TranslateMessage(&msg);
                        DispatchMessage(&msg);
                    }
                }else{
                    glClearColor(color.R,color.G,color.B,color.A);
                    glClear(GL_COLOR_BUFFER_BIT);
                }
            }
            /**
            * function startdraw
            * @brief end rendering and flush,in main loop
            */
            void enddraw(){
                if (run){
                    SwapBuffers(dc);
                    glFlush();
                }
            }
            /**
            * function drop
            * @brief release the context, drop the window's hwnd
            */
            bool drop(){
                cerr<<"释放上下文……"<<endl;
                DisableOpenGL(hwnd,dc,cc);
                cerr<<"销毁窗口句柄……"<<endl;
                bool ret=DestroyWindow(hwnd);
                cerr<<"程序已结束"<<endl;
                return ret;
            }
            /**
            * function drawline2d
            * @brief draw a 2d line by two point
            * @param point1 vector2d : a position of a point
            * @param point2 vector2d : a position of a point
            * @param color SCColor   : color of the line
            */
            void drawline2d(vector2d point1,vector2d point2,SCColor color){
                if (run){
                    glColor4f(color.R,color.G,color.B,color.A);
                    glBegin(GL_LINE_STRIP);
                        glVertex2f((point1.x-Windowsize/2)*25/(Windowsize->x/2),(point1.y/2)*25/(Windowsize->x/2));
                        glVertex2f(point2.x,point2.y);
                    glEnd();
                }
            }
            /**
            * function drawrect2d
            * @brief draw a 2d rectangle by two angle's vertexes
            * @param point1 vector2d : a position of a vertex
            * @param point2 vector2d : a position of a vertex
            * @param color SCColor   : color of the rectangle
            */
            void drawrect2d(vector2d point1,vector2d  point2,SCColor color,bool isfill=false){
                if (run){
                    glPushMatrix();
                    if (isfill){
                        glColor4f(color.R,color.G,color.B,color.A);
                        glBegin(GL_QUADS);
                            glVertex2f(point1.x,point1.y) ;
                            glVertex2f(point2.x,point1.y) ;
                            glVertex2f(point2.x,point2.y) ;
                            glVertex2f(point1.x,point2.y) ;
                        glEnd();
                    }else{
                        glColor4f(color.R,color.G,color.B,color.A);
                        glBegin(GL_LINE_LOOP);
                            glVertex2f(point1.x,point1.y);
                            glVertex2f(point2.x,point1.y);
                            glVertex2f(point2.x,point2.y);
                            glVertex2f(point1.x,point2.y);
                        glEnd();
                    }
                    glPopMatrix();
                }
            }
            /**
            * function drawcircle2d
            * @brief draw a 2d circle
            * @param o vector2d : circle's center
            * @param r float : radius of the circle
            */
            void drawcircle2d(vector2d o,float r,SCColor color){
                    /// @TODO will realize
            }
            /**
            * function isKeydown
            * @brief test if key is down
            * @param mouse SCmouse : the button which is tested
            * @return
            *      bool ---if key is down,return true
            *           ---else return false
            */
            bool isMousedown(SCmouse button){
                return GetAsyncKeyState(button)&&0x8000;
            }
            /**
            * @brief there is three functions can get the mouse's position
            */
            float getMouseX(){
                POINT mousePos;
                GetCursorPos(&mousePos);
                ScreenToClient(hwnd, &mousePos);
                return mousePos.x;
            }
            float getMouseY(){
                POINT mousePos;
                GetCursorPos(&mousePos);
                ScreenToClient(hwnd, &mousePos);
                return mousePos.y;
            }
            vector2d getMousePos(){
                return vector2d(getMouseX(),getMouseY());
            }
    };
    /// vector <SCEwindow> SCEW_lis : save the SCEW object
    vector<SCEwindow> SCEW_lis;
    /**
    * function WndProc a default massage function
    * It is overhead
    */
    LRESULT CALLBACK WndProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam){
        vector<SCEwindow>::iterator a;
        SCEwindow SWq;
        for (a=SCEW_lis.begin();a!=SCEW_lis.end();a++){
            if ((*a).hwnd==hWnd){
                SWq=*a;
            }
        }
        LRESULT  ret=0;
        switch(msg){
        case WM_CREATE:
            {
            }
            break;
        case WM_PAINT:
            {
            }
            break;
        case WM_DESTROY:
            {cerr<<"关闭窗口……"<<endl;
            ::PostQuitMessage(0);
            }
            break;
        default:
            ret = ::DefWindowProc(hWnd,msg,wParam,lParam);
            break;
        }
        return ret;
    }
    /**
    * function createSCEwindow
    * @brief create a SCEwindows object
    * @param Windowsize = wsize(640,480)  wsize : window's size
    * @param Cap wstring : the caption of the window
    * @param WP function : set the message function
    * @param ifnmax bool : if the .max button can be used
    *
    * @return
    *       SW
    *         --a window object , there is all information about the window
    *
    */
    SCEwindow createSCEwindow(wsize Windowsize=wsize(640,480),wstring Cap=L"",LRESULT CALLBACK (*WP)(HWND,UINT,WPARAM,LPARAM)=WndProc,bool ifnmax=true){
        SetConsoleOutputCP(65001);
        SCEwindow SW;
        WNDCLASS wc;
        SCEW_lis.push_back(SW);
        //set window class
        wc.lpszClassName ="SCEngineWindows";
        wc.lpfnWndProc =*WP;
        wc.style =CS_VREDRAW |CS_HREDRAW;
        wc.hInstance =SW.g_windows_instance;
        wc.hIcon =LoadIcon(0,IDI_APPLICATION);
        wc.hCursor =LoadCursor(0,IDC_ARROW);
        wc.hbrBackground = (HBRUSH)(COLOR_WINDOW);
        wc.lpszMenuName =NULL;
        wc.cbClsExtra = 0;
        wc.cbWndExtra = 0;
        //  Register windows
        if(!RegisterClass(&wc)){
            //if cannot Register Class
            throw L"失败注册窗口";
        }
        //set some information to SCEW
        SW.ifnmax=ifnmax;
        HWND hwnd;
        //create windows
        if (ifnmax)
            hwnd= CreateWindowW(L"SCEngineWindows",Cap.c_str(),WS_OVERLAPPED|WS_CAPTION|WS_SYSMENU|WS_MINIMIZEBOX,38,20,Windowsize.x,Windowsize.y,NULL,NULL,SW.g_windows_instance,NULL);
        else
            hwnd= CreateWindowW(L"SCEngineWindows",Cap.c_str(),WS_OVERLAPPEDWINDOW,38,20,Windowsize.x,Windowsize.y,NULL,NULL,SW.g_windows_instance,NULL);
        if (!hwnd){
            // if cannot create a handle
            throw L"失败创建句柄窗口";
        }
        //set some information to SCEW
        SW.Windowsize=&Windowsize;
        SW.Cap=Cap;
        SW.hwnd=hwnd;
        EnableOpenGL(SW.hwnd,&SW.dc,&SW.cc);
        glMatrixMode(GL_MODELVIEW); //set opengl mod
        SCEW_lis.push_back(SW);
        //print information
        cout<<"StarCatEngine 星喵引擎 版本 "<<version<<endl
        <<"窗口大小 "<<"("<<Windowsize.x<<","<<Windowsize.y<<")"<<endl
        <<"open graphic library版本 "<<glversion<<endl
        <<"GLU版本 "<<gluversion<<endl
        <<"窗口标题 "<<"\"";
        wprintf(Cap.c_str());
        cout<<"\""<<endl
        <<"能否缩放 ";
        if (ifnmax)
            cout<<"false"<<endl;
        else
            cout<<"true"<<endl;
        cout<<"句柄 "<<hwnd<<endl;
        return SW;
    }
}
#endif
