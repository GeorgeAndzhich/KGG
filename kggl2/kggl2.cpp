#include <Windows.h>
#include <gdiplus.h>
#include <gdiplusheaders.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
using namespace Gdiplus;
void draw(HDC hdc);
void Display(HDC hdc);
void DrawCar(HDC hdc);

#pragma comment(lib,"GdiPlus.lib")
Image* img;
UINT frameIndex;
UINT frameCount;

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
       L"Лабораторная работа №3",
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


LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_CREATE:
    {
        img = Image::FromFile(L"C://Users//SadLoneWolf//source//repos//kggl2//kggl2//car.gif");
        if (NULL == img)return -1;
        frameIndex = 0;
        frameCount = img->GetFrameCount(&FrameDimensionTime);
        SetTimer(hWnd, 1, 40, NULL);
        return 0;
    }
    case WM_TIMER:
    {
        frameIndex = (frameIndex + 1) % frameCount;
        img->SelectActiveFrame(&FrameDimensionTime, frameIndex);
        InvalidateRect(hWnd, NULL, false);
        return 0;
    }
   case WM_PAINT:
   {
       PAINTSTRUCT ps;
       HDC hDc = BeginPaint(hWnd, &ps);
       FillRect(hDc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
       //draw(hDc);
      // Display(hDc);
       DrawCar(hDc);
       EndPaint(hWnd, &ps);
       return 0;
   }
   case WM_DESTROY:
   {
       delete img;
       PostQuitMessage(0);
       return 0;
   }
   }

   return DefWindowProc(hWnd, msg, wParam, lParam);
}

void DrawCar(HDC hdc)
{

    Graphics gf(hdc);

    gf.DrawImage(img, 60, 60, 160, 260);
   gf.SetSmoothingMode(SmoothingModeAntiAlias);
   Pen mainPen(Color::Red);
      Point points[6] =
   {
        Point(350,330), Point(380,240),
        Point(380,240), Point(720,240),
        Point(720,240), Point(780,330)
   };
  
   Matrix mx;

       for (int j = 0; j < frameIndex; j++)
       {
           mx.Translate(10.f, 0.f);
           mx.TransformPoints(points, 6);
           gf.DrawLines(&mainPen, points, 6);
       }
}


//Пример аффиного преобразования
//
//void Display(HDC hdc)
//{
//    Graphics g(hdc);
//    g.Clear(Color::Azure);
//
//    Pen blackPen(Color::Black, 2.f);
//    Pen redPen(Color::Red, 2.f);
//    
//    Point points[3] = {
//        Point(100,100),
//        Point(200, 130),
//        Point(110,200)
//
//    };
//    g.DrawPolygon(&blackPen, points, 3);
//
//    //Создал единичную матрицу
//    Matrix mx;
//    //умножаем на матрицу переноса
//    mx.Translate(50.f, 0.f);
//    //дополняем преобразование - переносим треугольник вправо
//    mx.TransformPoints(points, 3);
//    g.DrawPolygon(&redPen, points, 3);
//
//}

//
// Пример применения преобразования для всего изображения
//void Display(HDC hdc) {
//    Graphics g(hdc);
//    g.Clear(Color::BlueViolet);
//    g.ScaleTransform(2.f, 1.f);
//    Pen blackPen(Color::Black, 3.f);
//    SolidBrush yellowBrush(Color::Yellow);
//    g.FillEllipse(&yellowBrush, 10, 10, 160, 80);
//    g.DrawEllipse(&blackPen, 10, 10, 160, 80);
//
//}