#include <windows.h>
#include <cmath>
#define ROUND(a) ((int) (a + 0.5))
#define LEFT_EDGE 0x1
#define RIGHT_EDGE 0x2
#define BOTTOM_EDGE 0x4
#define TOP_EDGE 0x8
#define INSIDE(a) (!a)
#define REJECT(a,b) (a&b)
#define ACCEPT(a,b) (!(a|b))
/* set window handle */
static HWND sHwnd;
static COLORREF redColor = RGB(255, 0, 0);
static COLORREF blueColor = RGB(0, 0, 255);
static COLORREF greenColor = RGB(0, 255, 0);
typedef struct Point
{
    int x;
    int y;
}pt;
pt winMin = { 100, 100 };
pt winMax = { 800, 400 };
pt p1 = { 200, 200 };
pt p2 = { 900, 300 };
void SetWindowHandle(HWND hwnd) {
    sHwnd = hwnd;
}
/* SetPixel */
void setPixel(int x, int y, COLORREF& color = redColor) {
    if (sHwnd == NULL) {
        MessageBox(NULL, L"sHwnd was not initialized !", L"Error", MB_OK | MB_ICONERROR);
        exit(0);
    }
    HDC hdc = GetDC(sHwnd);
    SetPixel(hdc, x, y, color);
    ReleaseDC(sHwnd, hdc);
    return;
}
void LineBresenham(int xa, int ya, int xb, int yb) {
    int dx = (xb - xa), dy = (yb - ya);
    int x, y, xEnd, yEnd;
    int p = 2 * abs(dy) - abs(dx);
    int twoDy = 2 * abs(dy), twoDyDx = 2 * (abs(dy) - abs(dx));
    int tFactor = dx * dy;
    if (xa > xb) {
        x = xb;
        y = yb;
        xEnd = xa;
    }
    else {
        x = xa;
        y = ya;
        xEnd = xb;
    }
    setPixel(x, y);
    while (x < xEnd) {
        x++;
        if (p < 0)
            p += twoDy;
        else {
            if (tFactor > 0) //for positive slope
                y++;
            else //for negative slope
                y--;
            p += twoDyDx;
        }
        setPixel(x, y);
    }
}
void drawBoundary(pt winMin, pt winMax) {
    int x, y;
    x = winMin.x;
    for (y = winMin.y; y < winMax.y; y++) {
        setPixel(x, y, blueColor);
    }
    y = winMin.y;
    for (x = winMin.x; x < winMax.x; x++) {
        setPixel(x, y, blueColor);
    }
    x = winMax.x;
    for (y = winMin.y; y < winMax.y; y++) {
        setPixel(x, y, blueColor);
    }
    y = winMax.y;
    for (x = winMin.x; x < winMax.x; x++) {
        setPixel(x, y, blueColor);
    }
}
unsigned char encode(pt Point, pt winMin, pt winMax) {
    unsigned char code = 0x00;
    if (Point.x < winMin.x)
        code = code | LEFT_EDGE;
    if (Point.x > winMax.x)
        code = code | RIGHT_EDGE;
    if (Point.y < winMin.y)
        code = code | BOTTOM_EDGE;
    if (Point.y > winMax.y)
        code = code | TOP_EDGE;
    return (code);
}
void swapPts(pt* p1, pt* p2) {
    pt temp;
    temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}
void swapCodes(unsigned char* c1, unsigned char* c2) {
    unsigned char temp;
    temp = *c1;
    *c1 = *c2;
    *c2 = temp;
}
void clipLine(pt winMin, pt winMax, pt p1, pt p2) {
    unsigned char code1, code2;
    int done = FALSE, draw = FALSE;
    float m;
    while (!done) {
        code1 = encode(p1, winMin, winMax);
        code2 = encode(p2, winMin, winMax);
        if (ACCEPT(code1, code2)) {
            done = TRUE;
            draw = TRUE;
        }
        else
            if (REJECT(code1, code2))
                done = TRUE;
            else {
                if (INSIDE(code1)) {
                    swapPts(&p1, &p2);
                    swapCodes(&code1, &code2);
                }
                if (p2.x != p1.x)
                    m = (p2.y - p1.y) / (p2.x - p1.x);
                if (code1 & LEFT_EDGE) {
                    p1.y += (winMin.x - p1.x) * m;
                    p1.x = winMin.x;
                }
                else
                    if (code1 & RIGHT_EDGE) {
                        p1.y += (winMax.x - p1.x) * m;
                        p1.x = winMax.x;
                    }
                    else
                        if (code1 & BOTTOM_EDGE) {
                            if (p2.x != p1.x)
                                p1.x += (winMin.y - p1.y) / m;
                            p1.y = winMin.y;
                        }
                        else
                            if (code1 & TOP_EDGE) {
                                if (p2.x != p1.x)
                                    p1.x += (winMax.y - p1.y) / m;
                                p1.y = winMax.y;
                            }
            }
    }
    if (draw) {
        LineBresenham(ROUND(p1.x), ROUND(p1.y), ROUND(p2.x), ROUND(p2.y));
    }
}
/* Window Procedure WndProc */
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_PAINT:
        SetWindowHandle(hwnd);
        drawBoundary(winMin, winMax);
        clipLine(winMin, winMax, p1, p2);
        break;
    case WM_CLOSE: // FAIL THROUGH to call DefWindowProc
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    default:
        break; // FAIL to call DefWindowProc //
    }
    return DefWindowProc(hwnd, message, wParam, lParam);
}
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int iCmdShow) {
    static TCHAR szAppName[] = TEXT("Line Clipping");
    WNDCLASS wndclass;
    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc = WndProc;
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.hInstance = hInstance;
    wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wndclass.lpszMenuName = NULL;
    wndclass.lpszClassName = szAppName;
    // Register the window //
    if (!RegisterClass(&wndclass)) {
        MessageBox(NULL,L"Registering the class failled", L"Error", MB_OK | MB_ICONERROR);
        exit(0);
    }
    // CreateWindow //
    HWND hwnd = CreateWindow(szAppName, L"Cohen Sutherland Algorithm - Programming Techniques",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        NULL,
        NULL,
        hInstance,
        NULL);
    if (!hwnd) {
        MessageBox(NULL, L"Window Creation Failed!", L"Error", MB_OK);
        exit(0);
    }
    // ShowWindow and UpdateWindow //
    ShowWindow(hwnd, iCmdShow);
    UpdateWindow(hwnd);
    // Message Loop //
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    /* return no error to the operating system */
    return 0;
}