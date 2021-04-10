//#include <Windows.h>
//#include <gdiplus.h>
//#include <gdiplusheaders.h>
//
//LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
//typedef void(*image)(HDC); 
//HDC Hdc;
//using namespace Gdiplus;
//void draw(HDC hdc);
//void DrawImg(HDC hdc);
//
//#pragma comment(lib,"GdiPlus.lib")
//Image* img;
//
//int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
//
//   const wchar_t windowName[] = L"Window Class";
//
//   GdiplusStartupInput gdiplusStartupInput;
//   ULONG_PTR gdiplusTokens;
//   GdiplusStartup(&gdiplusTokens, &gdiplusStartupInput, NULL);
//
//   WNDCLASS wnd;
//   wnd.cbClsExtra = 0;
//   wnd.cbWndExtra = 0;
//   wnd.hCursor = LoadCursor(0, IDC_ARROW);
//   wnd.hIcon = LoadIcon(0, IDI_WINLOGO);
//   wnd.lpszMenuName = 0;
//   wnd.style = 0;
//   wnd.hbrBackground = 0;
//   wnd.lpfnWndProc = WndProc;
//   wnd.hInstance = hInstance;
//   wnd.lpszClassName = windowName;
//
//   RegisterClass(&wnd);
//
//   HWND hWnd = CreateWindowEx(
//       0,
//       windowName,
//       L"Лабораторная работа №3_3",
//       WS_OVERLAPPEDWINDOW,
//       CW_USEDEFAULT,
//       CW_USEDEFAULT,
//       CW_USEDEFAULT,
//       CW_USEDEFAULT,
//       NULL,
//       NULL,
//       hInstance,
//       NULL
//   );
//
//
//   if (hWnd == NULL) {
//       //Pause
//       system("PAUSE");
//       return -1;
//   }
//
//   img = Image::FromFile(L"car3.jpg"); 
//
//
//   ShowWindow(hWnd, nCmdShow);
//
//   MSG msg;
//   while (GetMessage(&msg, NULL, 0, 0)) {
//       TranslateMessage(&msg);
//       DispatchMessage(&msg);
//   }
//   delete img; 
//   
//   GdiplusShutdown(gdiplusTokens);
//}
//
//
//LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
//   switch (msg) {
//   case WM_RBUTTONDBLCLK:
//
//       return 0;
//   case WM_PAINT:
//   {
//       PAINTSTRUCT ps;
//       HDC hDc = BeginPaint(hWnd, &ps);
//       FillRect(hDc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
//       draw(hDc);
//       DrawImg(hDc);
//       EndPaint(hWnd, &ps);
//       return 0;
//   }
//   case WM_DESTROY:
//   {
//       PostQuitMessage(0);
//       return 0;
//   }
//   }
//
//   return DefWindowProc(hWnd, msg, wParam, lParam);
//}
//
//void draw(HDC hdc)
//{
//    Region tireRegion(Rect(1, 1, 1, 1));
//    Region fontRegion(Rect(0, 0, 0, 0));
//
//    Region infinite;
//
//   Point point;
//   Rect rect(340, 400, 70, 70);
//   Rect rect2(700, 400, 70, 70);
//   RectF MainRect(320, 330, 500, 70);
//   Graphics gf(hdc);
//   gf.SetSmoothingMode(SmoothingModeAntiAlias);
//   Pen pen(Color(255, 0, 0, 0), 10.f); 
//   float comp[6] = {
//       0.0f,0.2f,
//       0.3f,0.7f,
//       0.9f,1.0f
//   };
//   pen.SetCompoundArray(comp, 6);
//   SolidBrush brush(Color(255, 0, 0, 0)); 
//   SolidBrush brush2(Color(255, 0, 191, 255)); 
//   SolidBrush brushLights(Color(255, 255, 215, 0)); 
//   SolidBrush brushLightsBack(Color(255, 255, 140, 0)); 
//   LinearGradientBrush linearBrush(MainRect, Color(255, 178, 34, 34), Color(255, 128, 0, 0), 90, FALSE);
//
//  
//   gf.FillRectangle(&linearBrush, 320, 330, 500, 70);
//   gf.FillEllipse(&brush, rect);
//   gf.FillEllipse(&brush, rect2);
//   gf.FillRectangle(&brushLightsBack, 325, 330, 15, 6); 
//   gf.FillRectangle(&brushLights, 800, 330, 15, 6);
//  
//   gf.SetClip(&tireRegion);
//   gf.DrawRectangle(&pen, 325, 330, 15, 6);
//   gf.DrawEllipse(&pen, rect);
//   gf.DrawRectangle(&pen, MainRect);
//   gf.DrawRectangle(&pen, 800, 330, 15, 6);
//   gf.DrawEllipse(&pen, rect2);
//
//   Point points[6] =
//   {
//        Point(350,330), Point(380,240),
//        Point(380,240), Point(720,240),
//        Point(720,240), Point(780,330)
//   };
//   gf.SetClip(&infinite);
//   gf.DrawLines(&pen, points, 6);
//   gf.DrawLine(&pen, 570, 240, 570, 330);
//
//   /// Font
//   FontFamily fontfamily(L"Arial");
//   Font font(&fontfamily, 16, FontStyleItalic, UnitPixel);
//   gf.FillRectangle(&brushLightsBack, 60, 60, 100, 20);
//   gf.DrawString(L"Автобомиль", 10, &font, PointF(60.f, 60.f), &brush);
//
//}
//void DrawImg(HDC hdc)
//{
//   Graphics g(hdc);
//   Region rectRegion;
//   RectF rectImg;
//   RectF layout(900, 200, 200.f, 150.f);
//   Pen pen(Color(6,62,145));
//   float fRat = (float)img->GetWidth() / (float)img->GetHeight();
//   if (fRat > (layout.Width / layout.Height))
//   {
//       rectImg.Width = layout.Width;
//       rectImg.Height = layout.Width / fRat;
//       rectImg.X = layout.GetLeft();
//       rectImg.Y = layout.GetTop();
//   }
//   else
//   {
//       rectImg.Width = fRat * layout.Height;
//       rectImg.Height = layout.Height;
//       rectImg.X = layout.GetLeft();
//   }
// 
//   g.DrawImage(img, rectImg);
//}