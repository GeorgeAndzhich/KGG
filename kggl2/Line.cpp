///*Curve formula
//   p = R*sin(4/7 * t) where t e (0,14PI)
//*/
//
//#define PI 3.1415f
//
//
//#include <Windows.h>
//#include <gdiplus.h>
//#include <cmath>
//#include<vector>
//
//using namespace Gdiplus;
//#pragma comment(lib,"GdiPlus.lib")
//
//#pragma comment(linker,"\"/manifestdependency:type                  = 'win32' \
//                                              name                  = 'Microsoft.Windows.Common-Controls' \
//                                              version               = '6.0.0.0' \
//                                              processorArchitecture = '*' \
//                                              publicKeyToken        = '6595b64144ccf1df' \
//                                              language              = '*'\"")
//#pragma warning(disable : 4996) 
//
//
//
//
//LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
//void draw(HDC);
//
//class WorldWindow
//{
//public:
//    float Left;
//    float Right;
//    float Top;
//    float Bottom;
//
//    inline WorldWindow(float left, float top, float right, float bottom)
//        :Left(left), Top(top), Right(right), Bottom(bottom) {}
//    inline float Width() const
//    {
//        return (Right - Left);
//    }
//    inline float Height() const
//    {
//        return (Top - Bottom);
//    }
//};
//class Viewport : public::Rect
//{
//public:
//    inline Viewport(int left, int top, int right, int bottom) :Rect(left, top, right - left, bottom - top) {}
//    inline Viewport(const RECT& rect) : Rect(rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top) {}
//    inline operator RECT() const
//    {
//        RECT rect = { X,Y, X + Width, Y + Height };
//        return rect;
//    }
//};
//
//
//
//
//
//int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
//
//    const wchar_t windowName[] = L"Window Class";
//
//    GdiplusStartupInput gdiplusStartupInput;
//    ULONG_PTR gdiplusTokens;
//    GdiplusStartup(&gdiplusTokens, &gdiplusStartupInput, NULL);
//
//    WNDCLASS wnd;
//    wnd.cbClsExtra = 0;
//    wnd.cbWndExtra = 0;
//    wnd.hCursor = LoadCursor(0, IDC_ARROW);
//    wnd.hIcon = LoadIcon(0, IDI_WINLOGO);
//    wnd.lpszMenuName = 0;
//    wnd.style = 0;
//    wnd.hbrBackground = 0;
//    wnd.lpfnWndProc = WndProc;
//    wnd.hInstance = hInstance;
//    wnd.lpszClassName = windowName;
//
//    RegisterClass(&wnd);
//
//    HWND hWnd = CreateWindowEx(
//        0,
//        windowName,
//        L"Лабораторная работа №2 задание 2",
//        WS_OVERLAPPEDWINDOW,
//        CW_USEDEFAULT,
//        CW_USEDEFAULT,
//        CW_USEDEFAULT,
//        CW_USEDEFAULT,
//        NULL,
//        NULL,
//        hInstance,
//        NULL
//    );
//
//    LoadLibrary(TEXT("ComCtl32.dll"));
//    if (hWnd == NULL) {
//        //Pause
//        system("PAUSE");
//        return -1;
//    }
//
//    
//
//    ShowWindow(hWnd, nCmdShow);
//
//    MSG msg;
//    while (GetMessage(&msg, NULL, 0, 0)) {
//        TranslateMessage(&msg);
//        DispatchMessage(&msg);
//    }
//
//    GdiplusShutdown(gdiplusTokens);
//}
//
//LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
//{
//    HDC hdc;             
//    PAINTSTRUCT ps;      
//    switch (msg)
//    {
//    case WM_QUIT:
//        PostQuitMessage(0);
//        return 0;
//
//    case WM_PAINT:
//    {
//        PAINTSTRUCT pstruct;
//        HDC hdc = BeginPaint(hWnd, &pstruct);
//
//        draw(hdc);
//
//        EndPaint(hWnd, &ps);
//    }
//    default:
//        return DefWindowProc(hWnd,msg,wParam,lParam);
//        break;
//    }
//}
//
//void draw(HDC hdc)
//{
//    Graphics gf(hdc);
//    gf.Clear(Color::Orange);
//    gf.SetSmoothingMode(SmoothingModeHighQuality);
//
//    WorldWindow w(0.0f, 0.0f, 980.0f, 840.0f);
//    // Viewport vp(-2.0f, 3.90f, 3.0f, -3.0f);
//    Viewport vp(-1.0f,1.0f,1.0f,-1.0f);
//    float A = (w.Right - w.Left) /(float) vp.Width;
//    float B = (w.Bottom - w.Top) /(float) vp.Height;
//    float C = w.Left - A * vp.X;
//    float D = w.Top - B * vp.Y;
//   
//    int m = 14 * PI / 0.05f;//879
//    PointF points[880];
//    float t = 0.0f;
//     for (int i = 0; i < m; i++)
//    {
//        float r = sin((4.0f / 7.0f) * t);
//        float X = r*cos(t);
//        float Y = r*sin(t);
//        // float Y = cos((4.0f / 7.0f) * t);
//        points[i].X = A * X +C;
//        points[i].Y = B * Y + D;
//        t += 0.05f;
//    }
//    Pen curvePen(Color::Black, 0.5f);
//    gf.DrawCurve(&curvePen, points, m);
//
//}
