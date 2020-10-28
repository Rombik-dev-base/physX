#include <windows.h>
#include <math.h>
#include <string>
#include <iostream>

#define pi 3.14

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL Line(HDC hdc, int x1, int y1, int x2, int y2);

#define edit_id 1

HWND edit_bt;
HWND edit_bt1;
HWND edit_bt2;
HWND edit_bt3;
HWND edit_bt4;
HWND push_bt;
double X0 = 25;
double Y0 = 25;
double omegX = 25;
double omegY = 25;
double delta = 0;

char szProgName[]="Имя программы";

int i, xView, yView;
double y;
char Buf[2];

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
    HWND hWnd;
    MSG lpMsg;
    WNDCLASS w;

    w.lpszClassName=szProgName;
    w.hInstance=hInstance;
    w.lpfnWndProc=WndProc;
    w.hCursor=LoadCursor(NULL, IDC_ARROW);
    w.hIcon=0;
    w.lpszMenuName=0;
    w.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);
    w.style=CS_HREDRAW|CS_VREDRAW;
    w.cbClsExtra=0;
    w.cbWndExtra=0;


    if(!RegisterClass(&w))
        return 0;


    hWnd=CreateWindow(szProgName,
                      "Func",
                      WS_OVERLAPPEDWINDOW,
                      100,
                      100,
                      500,
                      400,
                      (HWND)NULL,
                      (HMENU)NULL,
                      (HINSTANCE)hInstance,
                      (HINSTANCE)NULL);


    ShowWindow(hWnd, nCmdShow);

    UpdateWindow(hWnd);



    while(GetMessage(&lpMsg, NULL, 0, 0)) {
        TranslateMessage(&lpMsg);
        DispatchMessage(&lpMsg);
    }
    return(lpMsg.wParam);
}

//Функция окна
LRESULT CALLBACK WndProc(HWND hWnd, UINT messg,
                         WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;
    HPEN hPen;

    switch(messg)
    {

        case WM_CREATE:{
            CreateWindow("static", "X0 = ",
                         WS_VISIBLE | WS_CHILD , 5, 10, 60, 20, hWnd, NULL, NULL, NULL);
            edit_bt = CreateWindow("edit", "25",
                        WS_VISIBLE | WS_CHILD | WS_BORDER | ES_RIGHT | ES_NUMBER, 50, 10, 60, 20, hWnd, NULL, NULL, NULL);
            CreateWindow("static", "Y0 = ",
                         WS_VISIBLE | WS_CHILD , 5, 30, 60, 20, hWnd, NULL, NULL, NULL);
            edit_bt1 = CreateWindow("edit", "25",
                                   WS_VISIBLE | WS_CHILD | WS_BORDER | ES_RIGHT | ES_NUMBER, 50, 30, 60, 20, hWnd, NULL, NULL, NULL);
            CreateWindow("static", "Wx = ",
                         WS_VISIBLE | WS_CHILD , 5, 50, 60, 20, hWnd, NULL, NULL, NULL);
            edit_bt2 = CreateWindow("edit", "25",
                                    WS_VISIBLE | WS_CHILD | WS_BORDER | ES_RIGHT | ES_NUMBER, 50, 50, 60, 20, hWnd, NULL, NULL, NULL);
            CreateWindow("static", "Wy = ",
                         WS_VISIBLE | WS_CHILD , 5, 70, 60, 20, hWnd, NULL, NULL, NULL);
            edit_bt3 = CreateWindow("edit", "25",
                                    WS_VISIBLE | WS_CHILD | WS_BORDER | ES_RIGHT | ES_NUMBER, 50, 70, 60, 20, hWnd, NULL, NULL, NULL);
            CreateWindow("static", "delta = ",
                         WS_VISIBLE | WS_CHILD , 5, 90, 60, 20, hWnd, NULL, NULL, NULL);
            edit_bt4 = CreateWindow("edit", "0",
                                    WS_VISIBLE | WS_CHILD | WS_BORDER | ES_RIGHT | ES_NUMBER, 50, 90, 60, 20, hWnd, NULL, NULL, NULL);
            push_bt = CreateWindow("button", "Redraw",
                                   WS_VISIBLE | WS_CHILD , 420, 335, 60, 20, hWnd, NULL, NULL, NULL);

        break;
        }

        case WM_COMMAND: {
            if(reinterpret_cast<LPARAM>(edit_bt) == lParam){
                int nc = HIWORD(wParam);
                char num[50];
                GetWindowText(reinterpret_cast<HWND>(lParam), num, 50);
                std :: string str(num);
                if(nc == EN_CHANGE){
                    X0 = stof(str);
                }
            }
            if(reinterpret_cast<LPARAM>(edit_bt1) == lParam){
                int nc = HIWORD(wParam);
                char num[50];
                GetWindowText(reinterpret_cast<HWND>(lParam), num, 50);
                std :: string str(num);
                if(nc == EN_CHANGE){
                    Y0 = stof(str);
                }
            }
            if(reinterpret_cast<LPARAM>(edit_bt2) == lParam){
                int nc = HIWORD(wParam);
                char num[50];
                GetWindowText(reinterpret_cast<HWND>(lParam), num, 50);
                std :: string str(num);
                if(nc == EN_CHANGE){
                    omegX = stof(str);
                }
            }
            if(reinterpret_cast<LPARAM>(edit_bt3) == lParam){
                int nc = HIWORD(wParam);
                char num[50];
                GetWindowText(reinterpret_cast<HWND>(lParam), num, 50);
                std :: string str(num);
                if(nc == EN_CHANGE){
                    omegY = stof(str);
                }
            }
            if(reinterpret_cast<LPARAM>(edit_bt4) == lParam){
                int nc = HIWORD(wParam);
                char num[50];
                GetWindowText(reinterpret_cast<HWND>(lParam), num, 50);
                std :: string str(num);
                if(nc == EN_CHANGE){
                    delta = stof(str);
                }
            }
            if(reinterpret_cast<LPARAM>(push_bt) == lParam){
                InvalidateRect( hWnd, NULL, TRUE );
            }
            break;
        }
        case WM_SIZE:
            xView=LOWORD(lParam);
            yView=HIWORD(lParam);

            break;



        case WM_PAINT:
            hdc = BeginPaint(hWnd, &ps);
            SetMapMode(hdc, MM_ISOTROPIC);
            SetWindowExtEx(hdc, 500,500, NULL);
            SetViewportExtEx(hdc, xView, -yView, NULL);
            SetViewportOrgEx(hdc, xView/6, yView/2, NULL);


            Line(hdc,200, 220,200,-220);
            Line(hdc, -100,0,500,0);
            MoveToEx(hdc, 0,0,NULL);


            float x;
            float y;

                for(float t=0; t < 2*M_PI; t+=0.001 )
                {
                    x = X0*cos(omegX*t)+400/2;
                    y = Y0*cos(omegY*t + delta )+0/2;
                    SetPixel(hdc, x, y,RGB(0,0,0));
                }

            hPen=CreatePen(1,1,RGB(0,0,0));
            SelectObject(hdc, hPen);

            break;

        case WM_DESTROY:
            DeleteObject(hPen);
            PostQuitMessage(0);
            break;

        default:
            return(DefWindowProc(hWnd, messg, wParam, lParam));
    }
    return 0;
}


BOOL Line(HDC hdc, int x1, int y1, int x2, int y2)
{
    MoveToEx(hdc, x1, y1, NULL);
    return LineTo(hdc, x2, y2);
}