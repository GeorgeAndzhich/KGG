/*Curve formula
   p = R*sin(4/7 * t) where t e (0,14PI)
*/

#define PI 3.1415f


#include <Windows.h>
#include <gdiplus.h>
#include <CommCtrl.h>
#include <cmath>
#include<vector>


using namespace Gdiplus;
#pragma comment(lib,"GdiPlus.lib")

#pragma comment(linker,"\"/manifestdependency:type                  = 'win32' \
                                              name                  = 'Microsoft.Windows.Common-Controls' \
                                              version               = '6.0.0.0' \
                                              processorArchitecture = '*' \
                                              publicKeyToken        = '6595b64144ccf1df' \
                                              language              = '*'\"")
#pragma warning(disable : 4996) 
// Defining region codes
const int INSIDE = 0; // 0000
const int LEFT = 1;   // 0001
const int RIGHT = 2;  // 0010
const int BOTTOM = 4; // 0100
const int TOP = 8;    // 1000

const int x_max = 200;
const int y_max = 200;
const int x_min = 10;
const int y_min = 10;

int cohenSutherlandClip(double x1, double y1, double x2, double y2);
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
void draw(HDC);

class WorldWindow
{
public:
    float Left;
    float Right;
    float Top;
    float Bottom;

    inline WorldWindow(float left, float top, float right, float bottom)
        :Left(left), Top(top), Right(right), Bottom(bottom) {}
    inline float Width() const
    {
        return (Right - Left);
    }
    inline float Height() const
    {
        return (Top - Bottom);
    }
};
class Viewport : public::Rect
{
public:
    inline Viewport(int left, int top, int right, int bottom) :Rect(left, top, right - left, bottom - top) {}
    inline Viewport(const RECT& rect) : Rect(rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top) {}
    inline operator RECT() const
    {
        RECT rect = { X,Y, X + Width, Y + Height };
        return rect;
    }
};

inline void WorldToViewPort(const WorldWindow& w, const Viewport& vp, PointF* points, int count);
inline void ViewPortToWorld(const WorldWindow& w, const Viewport& vp, PointF* points, int count);



int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {

    const wchar_t windowName[] = L"Window Class";

    GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusTokens;
    GdiplusStartup(&gdiplusTokens, &gdiplusStartupInput, NULL);

    WNDCLASS wnd;
    wnd.cbClsExtra = 0;
    wnd.cbWndExtra = 0;
    wnd.hCursor = LoadCursor(0, IDC_ARROW);
    wnd.hIcon = LoadIcon(0, IDI_WINLOGO);
    wnd.lpszMenuName = 0;
    wnd.style = 0;
    wnd.hbrBackground = 0;
    wnd.lpfnWndProc = WndProc;
    wnd.hInstance = hInstance;
    wnd.lpszClassName = windowName;

    RegisterClass(&wnd);

    HWND hWnd = CreateWindowEx(
        0,
        windowName,
        L"Лабораторная работа №2 задание 2",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    LoadLibrary(TEXT("ComCtl32.dll"));
    if (hWnd == NULL) {
        //Pause
        system("PAUSE");
        return -1;
    }



    ShowWindow(hWnd, nCmdShow);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    GdiplusShutdown(gdiplusTokens);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;
    switch (msg)
    {
    case WM_QUIT:
        PostQuitMessage(0);
        return 0;

    case WM_PAINT:
    {
        PAINTSTRUCT pstruct;
        HDC hdc = BeginPaint(hWnd, &pstruct);
        draw(hdc);

        EndPaint(hWnd, &ps);
    }
    default:
        return DefWindowProc(hWnd, msg, wParam, lParam);
        break;
    }
}

inline void WorldToViewPort(const WorldWindow& w, const Viewport& vp, PointF* points, int count)
{
    //Из мирового окна в окно просмотра
    float A = (float)vp.Width / (w.Right - w.Left);
    float B = (float)vp.Height / (w.Bottom - w.Top);
    float C = vp.X - A * w.Left;
    float D = vp.Y - B * w.Top;

    for (unsigned int i = 0; i < count; ++i)
    {
        points[i].X = A * points[i].X + C;
        points[i].Y = B * points[i].Y + D;
    }
}

inline void ViewPortToWorld(const WorldWindow& w, const Viewport& vp, PointF* points, int count)
{
    //Из мирового окна в окно просмотра
    float A = (w.Right - w.Left) / (float)vp.Width;
    float B = (w.Bottom - w.Top) / (float)vp.Height;
    float C = w.Left - A * vp.X;
    float D = w.Top - B * vp.Y;
    for (unsigned int i = 0; i < count; ++i)
    {
        points[i].X = A * points[i].X + C;
        points[i].Y = B * points[i].Y + D;
    }

}

void draw(HDC hdc)
{
    Graphics gf(hdc);
    gf.Clear(Color::Orange);
    gf.SetSmoothingMode(SmoothingModeHighQuality);
    Pen curvePen(Color::Black);

    WorldWindow w(0.0f, 0.0f, 980.0f, 840.0f);
    Viewport vp(-2.0f, 1.90f, 2.0f, -1.2f);
    float A = (w.Right - w.Left) / (float)vp.Width;
    float B = (w.Bottom - w.Top) / (float)vp.Height;
    float C = w.Left - A * vp.X;
    float D = w.Top - B * vp.Y;

    int m = 14 * PI / 0.05f;//879


    PointF points[889];
    float t = 0.0f;
    for (int i = 0; i < m; i++)
    {
        float r = sin((4.0f / 7.0f) * t);
        float X = r * cos(t);
        float Y = r * sin(t);
        // float Y = cos((4.0f / 7.0f) * t);
        points[i].X = A * X + C;
        points[i].Y = B * Y + D;
        t += 0.05f;
    }

    gf.DrawCurve(&curvePen,points,m);
}

#pragma region Coen-Sunderland algorithm

int ComputeCode(float x, float y)
{
    int code = INSIDE; 
    if (x < x_min)
    {
        code = LEFT;
    }
    else if (x>x_max)
    {
        code = RIGHT;
    }
    else if (y<y_min)
    {
        code = BOTTOM;
    }
    else if(y > y_max)
    {
        code = TOP;
    }
    return code;
}

int ConeSunderlandClip(float x1, float y1, float x2, float y2)
{
    // computing codes for P1 (x1,y1) and P2 (x2,y2)
    int code1 = ComputeCode(x1, y1);
    int code2 = ComputeCode(x2, y2);
    bool accept = false;
    while (true)
    {
        if (code1 == INSIDE && code2 == INSIDE)
        {
            accept = true;
            return INSIDE;
        }
        else if (code1 & code2)
        {
            // line is completely off bounds
            return -1;
        }

        //Some segments of the line are in bounds
        int code_out;
        float x, y;


        if (code1 != 0)
            code_out = code1;
        else
            code_out = code2;

        // Find intersection point; using formulas y = y1 + slope * (x - x1),
        // x = x1 + (1 / slope) * (y - y1)
        if (code_out & TOP)
        {
            // point is above the clip rectangle
            x = x1 + (x2 - x1) * (y_max - y1) / (y2 - y1);
            y = y_max;
        }
        else if (code_out & BOTTOM)
        {
            // point is below the rectangle
            x = x1 + (x2 - x1) * (y_min - y1) / (y2 - y1);
            y = y_min;
        }
        else if (code_out & RIGHT)
        {
            // point is to the right of rectangle
            y = y1 + (y2 - y1) * (x_max - x1) / (x2 - x1);
            x = x_max;
        }
        else if (code_out & LEFT)
        {
            // point is to the left of rectangle
            y = y1 + (y2 - y1) * (x_min - x1) / (x2 - x1);
            x = x_min;
        }

        // Now intersection point x,y is found We replace point outside rectangle by intersection point
        if (code_out == code1)
        {
            x1 = x;
            y1 = y;
            code1 = ComputeCode(x1, y1);
            return code1;
        }
        else
        {
            x2 = x;
            y2 = y;
            code2 = ComputeCode(x2, y2);
            return code2;
        }

    }
}


#pragma endregion 