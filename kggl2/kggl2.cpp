#include <Windows.h>
#include <gdiplus.h>
#include <gdiplusheaders.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
using namespace Gdiplus;
void draw(HDC hdc);
void Display(HDC hdc);

#pragma comment(lib,"GdiPlus.lib")
Image* img;

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
   delete img; 
   
   GdiplusShutdown(gdiplusTokens);
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
   switch (msg) {
   case WM_RBUTTONDBLCLK:

       return 0;
   case WM_PAINT:
   {
       PAINTSTRUCT ps;
       HDC hDc = BeginPaint(hWnd, &ps);
       FillRect(hDc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
       //draw(hDc);
       Display(hDc);
       EndPaint(hWnd, &ps);
       return 0;
   }
   case WM_DESTROY:
   {
       PostQuitMessage(0);
       return 0;
   }
   }

   return DefWindowProc(hWnd, msg, wParam, lParam);
}

void draw(HDC hdc)
{
    Region tireRegion(Rect(1, 1, 1, 1));
    Region fontRegion(Rect(0, 0, 0, 0));

    Region infinite;

   Point point;
   Rect rect(340, 400, 70, 70);
   Rect rect2(700, 400, 70, 70);
   RectF MainRect(320, 330, 500, 70);
   Graphics gf(hdc);
   gf.SetSmoothingMode(SmoothingModeAntiAlias);
   Pen pen(Color(255, 0, 0, 0), 10.f); 
   float comp[6] = {
       0.0f,0.2f,
       0.3f,0.7f,
       0.9f,1.0f
   };
   pen.SetCompoundArray(comp, 6);
   SolidBrush brush(Color(255, 0, 0, 0)); 
   SolidBrush brush2(Color(255, 0, 191, 255)); 
   SolidBrush brushLights(Color(255, 255, 215, 0)); 
   SolidBrush brushLightsBack(Color(255, 255, 140, 0)); 
   LinearGradientBrush linearBrush(MainRect, Color(255, 178, 34, 34), Color(255, 128, 0, 0), 90, FALSE);

  
   gf.FillRectangle(&linearBrush, 320, 330, 500, 70);
   gf.FillEllipse(&brush, rect);
   gf.FillEllipse(&brush, rect2);
   gf.FillRectangle(&brushLightsBack, 325, 330, 15, 6); 
   gf.FillRectangle(&brushLights, 800, 330, 15, 6);
  
   gf.SetClip(&tireRegion);
   gf.DrawRectangle(&pen, 325, 330, 15, 6);
   gf.DrawEllipse(&pen, rect);
   gf.DrawRectangle(&pen, MainRect);
   gf.DrawRectangle(&pen, 800, 330, 15, 6);
   gf.DrawEllipse(&pen, rect2);

   Point points[6] =
   {
        Point(350,330), Point(380,240),
        Point(380,240), Point(720,240),
        Point(720,240), Point(780,330)
   };
   gf.SetClip(&infinite);
   gf.DrawLines(&pen, points, 6);
   gf.DrawLine(&pen, 570, 240, 570, 330);


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