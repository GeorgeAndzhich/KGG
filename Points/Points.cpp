//#include <Windows.h>
//#include <WindowsX.h>
//#include <iostream>
//#include <cmath>
//#include <string>
//#include <vector>
//#include <gdiplus.h>
//#include <gdiplusgraphics.h>
//#include <tuple>
//
//#define PI 3.1415
//#pragma comment(lib, "GdiPlus.lib")
//
//using namespace Gdiplus;
//using namespace std;
//// To do 
////Определить принадлежность через Треугольники
//// Определить принадлежность через Барицентрические координаты
//
//
//
//class EqualMethod
//{
//public:
//
//	bool EqualDot(PointF& first, PointF& second, float tolerance = 1e-6f)
//	{
//		if (abs(first.X - second.X) < tolerance && abs(first.Y - second.Y) < tolerance)
//		{
//			return true;
//			cout << first.X << first.Y << "\t" << second.X << second.Y;
//		}
//		else
//			return false;
//	}
//	inline bool GreaterOrEqual(float a, float b, float tolerance = -1e-3f)
//	{
//		return !(b - a) > tolerance;
//	}
//	inline bool Equal(float a, float b, float tolerance = -1e-3f)
//	{
//		return (abs(a - b) < tolerance);
//	}
//	inline bool IsZero(float a, float tolerance)
//	{
//		return (abs(a) == tolerance);
//	}
//
//
//};
//
//
//class BelongPolygon
//{
//public:
//	tuple<const bool, int> Baricenter_method(PointF& A, PointF& B, PointF& C, PointF& P, int check_border)
//	{
//		string answer;
//		EqualMethod Equal = EqualMethod();
//		if (Equal.EqualDot(A, P) || Equal.EqualDot(B, P) || Equal.EqualDot(C, P))
//		{
//			cout << "Dot is equal to this height"; //местоположение в многоугольнике
//			cout << "Dot belong Polygon";
//			tuple <const bool, int> answer = { true, check_border };
//			return answer; // = "Dot belong Polygon"; //вывод - TRUE?
//		}
//
//		float denominate = ((B.Y - C.Y) * (A.X - C.X)) + ((C.X - B.X) * (A.Y - C.Y));
//		float a = (((B.Y - C.Y) * (P.X - C.X)) + ((C.X - B.X) * (P.Y - C.Y))) / denominate;
//		float b = (((C.Y - A.Y) * (P.X - C.X)) + ((A.X - C.X) * (P.Y - C.Y))) / denominate;
//		float c = (((A.Y - B.Y) * (P.X - C.X) + ((B.X - A.X) * (P.Y - A.Y)))) / denominate;
//
//		if (Equal.GreaterOrEqual(a, 0) && Equal.GreaterOrEqual(b, 0) && Equal.GreaterOrEqual(c, 0))
//		{
//			cout << "The dot is in the triangle";
//			// уточнение, т.е. где именно она в треугольнике
//			if (OnBorder(a, b, c))
//			{
//				cout << "The dot is on the border";
//				check_border++;
//				tuple <const bool, int> t = { true, check_border };
//				return t;
//			}
//			else
//			{
//				tuple <const bool, int> answer = { true, check_border };
//				return answer; //принадлежит
//			}
//		}
//		else
//		{
//			tuple <const bool, int> answer = { false, check_border };
//			return answer;//Given dot is not in the triangle";
//		}
//	}
//
//	bool OnBorder(float a, float b, float c)
//	{
//		EqualMethod Equal = EqualMethod();
//		if (Equal.Equal(a, 1.0f) || Equal.Equal(b, 1.0f) || Equal.Equal(c, 1.0f) || Equal.IsZero(a, 0.0f) || Equal.IsZero(b, 0.0f) || Equal.IsZero(c, 0.0f))
//		{
//			return true;
//		}
//		return false;
//	}
//};
//
//class Method
//{
//public:
//	string Polygon_method(vector<PointF> dots, PointF& P)
//	{
//		string answer;
//		EqualMethod Equal = EqualMethod();
//
//		// Проверка на совпадение с вершиной
//		for (auto& elem : dots)
//		{
//			if (Equal.EqualDot(elem, P) == true)
//			{
//				cout << elem.X << '\t' << elem.Y;
//				return answer = "Dot is equal to this height"; //На самом деле - принадлежит многогольнику
//				break;
//			}
//		}
//		BelongPolygon inPolygon = BelongPolygon();
//		int check_border = 0;
//		int check;
//		bool answ;
//		PointF startDot = PointF();
//		startDot = dots.front();
//		dots.erase(dots.begin());
//		for (int i = 0; i < dots.size() - 1; ++i)
//		{
//			cout << "WORK WITH TRIANGLE: " << i + 1;
//			tie(answ, check) = inPolygon.Baricenter_method(startDot, dots[i], dots[i + 1], P, check_border);
//			check_border = check;
//		}
//		answer = "Belongs polygon";
//		if (answ == true)
//		{
//			if (check > 1 || check == 0)
//			{
//				answer = "Inside in polygon";
//			}
//			if (check == 1)
//			{
//				answer = "On border of polygon";
//			}
//		}
//		else
//			if (answ == false)
//			{
//				answer = "Not Inside in polygon";
//			}
//		cout << endl << answer << endl;
//		return answer;
//	}
//};
//
//
//
//int main()
//{
//	float x, y;
//	vector<PointF> points;
//	cout << "---------------START--------------------\n";
//	cout << "Enter the coordinates for the following dots:\n";
//
//	/*Инициализаци GDI+*/
//	ULONG_PTR gdToken;
//	GdiplusStartupInput gdInput;
//
//	LSTATUS retRes = GdiplusStartup(&gdToken, &gdInput, NULL);	/*Создание главного файла и обработка ошибки */
//	// Test
//	PointF A(1.0f, 2.0f);
//	PointF B(2.0f, 4.0f);
//	PointF C(4.0f, 4.5f);
//	PointF D(4.5f, 2.0f);
//	PointF E(3.0f, 1.0f);
//
//
//	points.push_back(A);
//	points.push_back(B);
//	points.push_back(C);
//	points.push_back(D);
//	points.push_back(E);
//
//	float XcenterP = (points[1].X + points[0].X) / 2;
//	float YcenterP = (points[1].Y + points[0].Y) / 2;
//
//	PointF P(XcenterP, YcenterP); //проверяемая точка 
//
//	Method method = Method();
//	cout << "-------------Check by Polygon baricentric method----------------------- \n";
//
//	string result = method.Polygon_method(points, P);
//	cout << result;
//
//	GdiplusShutdown(gdToken);
//	return 0;
//}