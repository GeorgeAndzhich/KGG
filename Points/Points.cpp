#include <Windows.h>
#include <WindowsX.h>
#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <gdiplus.h>
#include <gdiplusgraphics.h>

#define PI 3.1415
#pragma comment(lib, "GdiPlus.lib")

using namespace Gdiplus;
using namespace std;
// To do 
//Определить принадлежность через Треугольники
// Определить принадлежность через Барицентрические координаты
class Dot
{
private:
	float x;
	float y;
public:
	//getters
	float X() { return x; }
	float Y() { return y; }
	//setters
	void setX(float value) { x = value; }
	void setY(float value) { y = value; }
	// void setCoordinates(Dot& dot)
	void setCoordinates(float value1, float value2)
	{
		// float value1, value2;
		// cout << "Enter the coordinates: \n";
		// cin >> value1; cout << "\n"; cin >> value2;
		setX(value1);
		setY(value2);
	}
};

class Vector
{
private:
	float x;
	float y;
public:
	float X() { return x; }
	float Y() { return y; }

	void setX(float value) { x = value; }
	void setY(float value) { y = value; }

	void set_coordinats(Dot& dot1, Dot& dot2)
	{
		setX(dot2.X() - dot1.X());
		setY(dot2.Y() - dot1.Y());
	}

	double VectorLength()
	{
		double result = sqrt(pow(X(), 2) + pow(Y(), 2));
		return result;
	}
};

class EqualMethod
{
public:
	bool EqualDot(Dot& first, Dot& second)
	{
		if (first.X() == second.X() && first.Y() == second.Y())
		{
			return true;
			cout << first.X() << first.Y() << "\t" << second.X() << second.Y();
		}
		else
			return false;
	}
	bool EqualDot(PointF& first, PointF& second, float tolerance = 1e-6f)
	{
		if (abs(first.X - second.X) < tolerance && abs(first.Y - second.Y) < tolerance)
		{
			return true;
			cout << first.X << first.Y << "\t" << second.X << second.Y;
		}
		else
			return false;
	}
	inline bool GreaterOrEqual(float a, float b, float tolerance = -1e-3f)
	{
		return !(b - a) > tolerance;
	}
	inline bool Equal(float a, float b, float tolerance = -1e-3f)
	{
		return (abs(a - b) < tolerance);
	}
	inline bool IsZero(float a, float tolerance)
	{
		return (abs(a) == tolerance);
	}
};


class BelongPolygon
{
public:
	/*
		Точка P - ее местоположение нужно определить: внутри, снаружи, на границе
		A, B,C - координаты вершин
		Формула: a*b = |a||b| cos y ,
		где a и b - векторы , y - угол между ними
		Вектора: AB, BC, CA - для треугольника
			|AB| = sqrt((B.x - A.x)^2 + (B.y - A.y)^2 )
		Вычисление:
			cos α = 	(a·b)/ |a|·|b| ~ 0,1 or 0,96 -> arcos a ~ 30`
		у нас для angle APC вектор a = P.x - A.x
			Пример расчета: APB =arcos( (-0.4*0.6 + 4.3*-1.6) / (1.71 * 4.32 ) )= arcos((-7.12 / 7.37)) = 165*93`
		Условия завершения:
		Сумма углов:
			= 360 - точка внутри и на границе
			!= 360 - вне треугольника
		Углы:
			= 180 - точка на границе
		Совпадение координат
			Если P.x = A.x и P.y = A.y, то P - совпадает с A,
			answer = границе треугольника
	*/

	string Triangle_method(Dot& A, Dot& B, Dot& C, Dot& P)
	{
		string answer;
		EqualMethod Equal = EqualMethod();
		if (Equal.EqualDot(P, B) == true || Equal.EqualDot(P, A) == true || Equal.EqualDot(P, C) == true)
		{
			return "Dot is equal to one of the triangle's heights";
		}
		else
		{
			//координаты векторов
			Vector vector_pa = Vector();
			Vector vector_pb = Vector();
			Vector vector_pc = Vector();

			vector_pa.set_coordinats(P, A);
			vector_pb.set_coordinats(P, B);
			vector_pc.set_coordinats(P, C);
			// углы
			float angle_apb = (acos((vector_pa.X() * vector_pb.X() + vector_pa.Y() * vector_pb.Y()) / (vector_pa.VectorLength() * vector_pb.VectorLength())) * 180) / PI; //в градусах
			float angle_bpc = (acos((vector_pb.X() * vector_pc.X() + vector_pb.Y() * vector_pc.Y()) / (vector_pb.VectorLength() * vector_pc.VectorLength())) * 180) / PI; //в градусах
			float angle_apc = (acos((vector_pa.X() * vector_pc.X() + vector_pa.Y() * vector_pc.Y()) / (vector_pa.VectorLength() * vector_pc.VectorLength())) * 180) / PI; //в градусах
			// сумма углов
			int sum_angle = angle_apb + angle_bpc + angle_apc;
			if (sum_angle != 360)
			{
				return "Dot is out of bounds";
			}
			else
				return "Dot is in the bounds";
		}
	};
	/*
		P = aA + b + cC where  (a,b,c) - барицентрические координаты
		P.y = aA + bB + cC where  (a,b,c) - барицентрические координаты
		(a+b+c=1) and a >=0 and b >=0 and c >=0 (*)
		Выходные данные:
			Если * верно и хотя бы одна координат (a, b,c) = 0, то на границе
			Если * верно и хотя бы одна координат (a, b,c) = 1, то совпадение с вершиной
			Если * не верно, то вне треугольника
		denominate = (By - Cy)(Ax - Cx) + (Cx - Bx)(Ay - Cy)
		a = (By - Cy)(Px-Cx) + (Cx-Bx)(Py-Cy) / denominate;
		b = (Cy - Ay)(Px - Cx) + (Ax - Cx)(Py - Cy)/ denominate;
		c = (Ay - By)(Px - Ax) + (Bx -  Ax)(Py - Ay)/ denominate;
	*/


	string Baricenter_method(Dot& A, Dot& B, Dot& C, Dot& P)
	{
		string answer;

		float denominate = ((B.Y() - C.Y()) * (A.X() - C.X())) + ((C.X() - B.X()) * (A.Y() - C.Y()));

		float a = (((B.Y() - C.Y()) * (P.X() - C.X())) + ((C.X() - B.X()) * (P.Y() - C.Y()))) / denominate;
		float b = (((C.Y() - A.Y()) * (P.X() - C.X())) + ((A.X() - C.X()) * (P.Y() - C.Y()))) / denominate;
		float c = (((A.Y() - B.Y()) * (P.X() - C.X())) + ((B.X() - A.X()) * (P.Y() - A.Y()))) / denominate;


		int check_sum = (abs(a) + abs(b) + abs(c)); //без abs вернет 0, т.к. отрицательные значения в весах

		if (check_sum == 1 && (abs(a) >= 0 && abs(b) >= 0 && abs(c) >= 0))
		{
			answer = "The dot is in the triangle";
			// уточнение, т.е. где именно она в треугольнике
			if (a == 1 || b == 1 || c == 1)
			{
				answer += "\nGiven dot is equal to one of the triangle's heights";
			}
			else
				if (a == 0 || b == 0 || c == 0)
				{
					answer = "\nThe dot is on the border";
				}
				else
					answer = "\nGiven dot in the triangle";
			return answer;
		}
		else
			answer = "\nGiven dot is not in the triangle";
		return answer;
	}

	string Baricenter_method(PointF& A, PointF& B, PointF& C, PointF& P)
	{
		string answer;
		EqualMethod Equal = EqualMethod();
		float denominate = ((B.Y - C.Y) * (A.X - C.X)) + ((C.X - B.X) * (A.Y - C.Y));
		float a = (((B.Y - C.Y) * (P.X - C.X)) + ((C.X - B.X) * (P.Y - C.Y))) / denominate;
		float b = (((C.Y - A.Y) * (P.X - C.X)) + ((A.X - C.X) * (P.Y - C.Y))) / denominate;
		float c = (((A.Y - B.Y) * (P.X - C.X) + ((B.X - A.X) * (P.Y - A.Y)))) / denominate;

		//Не проверять check_summ
		//int check_sum = (abs(a) + abs(b) + abs(c)); //без abs вернет 0, т.к. отрицательные значения в весах
		//float check_sum = ( a+b+c); //без abs вернет 0, т.к. отрицательные значения в весах

		/*if (check_sum == 1 && (abs(a) >= 0 && abs(b) >= 0 && abs(c) >= 0))*/
		if (Equal.GreaterOrEqual(a, 0) && Equal.GreaterOrEqual(b, 0) && Equal.GreaterOrEqual(c, 0))
		{
			answer = "The dot is in the triangle";
			// уточнение, т.е. где именно она в треугольнике
			if (OnBorder(a, b, c))
			{
				return answer = "The dot is on the border";
			}
			return answer;
		}
		else
			answer = "\nGiven dot is not in the triangle";

		return answer;
	}

	bool OnBorder(float a, float b, float c)
	{
		EqualMethod Equal = EqualMethod();
		if (Equal.Equal(a, 1.0f) || Equal.Equal(b, 1.0f) || Equal.Equal(c, 1.0f) || Equal.IsZero(a, 0.0f) || Equal.IsZero(b, 0.0f) || Equal.IsZero(c, 0.0f))
		{
			return true;
		}
		return false;
	}
};

class Method
{
public:
	/**
	* inPolygonTrue = true; для проверки при совпадении на границе
	* Следовательно: если из какой-нибудь вершины многоугольника провести все возможные диагонали,
	* то они разделят многоугольник на треугольники: t=n-2
	* ФОРМУЛА поиска количества треугольников: triangle = n-2 -> n=5 triangle = 3 , n=7 triangle = 5.
	* Входные данные: точки, количество вершин - n
	* В качестве первой точки возьмем первую в списке. Далее по очереди будем брать следующие.
	* Пример:
		n = number_vertex; - количество вершин
		for(i = 1; i<number_vertex++ ; number_vertex++)
			triangle_list(A, i, i+1);
		т.е. для первого  треугольника 0, 1, 2 номера вершин
			 для второго  треугольника 0, 2, 3
			 для третьего треугольника 0, 3, 4
			 ....
			if (answer = "The dot is on the border")
			{
				//продолжить проверку
			}

			Last triangle ADE startDot = 0, dot[3], dot[4]
			startDot = 0, A, dots[0] = B, dots[1]= C : i = 0
			startDot = 0 = A, dots[2] = C, dots[i+1] = D : i = 1
			startDot = 0 = A , dots[3] = D , dots[i+1] = E : i = 2
	*/
	string Polygon_method(vector<Dot> dots, Dot& P)
	{
		string answer;

		EqualMethod Equal = EqualMethod();
		// Проверка на совпадение с вершиной
		for (auto& elem : dots)
		{
			if (Equal.EqualDot(elem, P) == true)
			{
				return answer = "Dot is equal to this height";
				cout << elem.X() << '\t' << elem.Y();
				break;
			}
		}

		BelongPolygon inPolygon = BelongPolygon();
		int check_border = 0;
		Dot startDot = Dot();
		startDot = dots.front();
		dots.erase(dots.begin());
		for (int i = 0; i < dots.size() - 1; ++i)
		{

			cout << "WORK WITH TRINAGLE" << i;
			answer = inPolygon.Baricenter_method(startDot, dots[i], dots[i + 1], P);
			cout << endl << answer << endl;

			if (answer.compare("\nGiven dot in the triangle") == 0)
			{
				return answer;
			}
			else
			{
				if (answer.compare("\nThe dot is on the border") == 0 && check_border < 2)
				{
					check_border++; //если встретили на границе точку
					continue;
				}
				else
					if (answer.compare("\nGiven dot is not in the triangle") == 0 && check_border == 2)
					{
						return answer = "\nGiven dot is on the border of the polygon";
					}
					else
					{
						if (answer.compare("\nGiven dot is not in the triangle") == 0 && check_border == 1)
						{
							return answer = "\nGiven dot is on the outer border";
						}
						else
						{
							if (answer.compare("\nGiven dot is not in the triangle") == 0)
							{
								continue;
							}
						}
					}
			}
		}
		return answer;
	}

	string Polygon_method(vector<PointF> dots, PointF& P)
	{
		string answer;
		EqualMethod Equal = EqualMethod();
		// Проверка на совпадение с вершиной
		for (auto& elem : dots)
		{
			if (Equal.EqualDot(elem, P) == true)
			{
				return answer = "Dot is equal to this height";
				cout << elem.X << '\t' << elem.Y;
				break;
			}
		}
		BelongPolygon inPolygon = BelongPolygon();
		int check_border = 0;
		PointF startDot = PointF();
		startDot = dots.front();
		dots.erase(dots.begin());
		for (int i = 0; i < dots.size() - 1; ++i)
		{
			cout << "WORK WITH TRIANGLE: " << i + 1;
			answer = inPolygon.Baricenter_method(startDot, dots[i], dots[i + 1], P);
			cout << endl << answer << endl;
			if (answer.compare("\nGiven dot in the triangle") == 0 && check_border == 1)
			{
				return answer += "Inside ManyAngle";
			}
			else
			{
				if (answer.compare("\nGiven dot in the triangle") == 0)
				{
					return answer;
				}
				else
				{
					if (answer.compare("\nThe dot is on the border") == 0 && check_border < 2)
					{
						check_border++; //если встретили на границе точку
						continue;
					}
					else
						if (answer.compare("\nGiven dot is not in the triangle") == 0 && check_border == 2)
						{
							return answer = "\nGiven dot is on the border of the polygon";
						}
						else
						{
							if (answer.compare("\nGiven dot is not in the triangle") == 0 && check_border == 1)
							{
								return answer = "\nGiven dot is on the outer border previous Trinagle";
							}
							else
							{
								if (answer.compare("\nGiven dot is not in the triangle") == 0)
								{
									continue;
								}
							}
						}
				}

			}
		}
		return answer;
	}
};



int main()
{
	float x, y;
	vector<PointF> points;
	cout << "---------------START--------------------\n";
	cout << "Enter the coordinates for the following dots:\n";
	//int n = 0;
	//int  triangle = n - 2;
	//do
	//{
	//	cout << "Enter the number of vertex:\n";
	//	cin >> n;
	//} while (n < 2);

	//for (int i = 0; i < n; i++)
	//{
	//	cout << "Enter the X and Y:\n";
	//	cin >> x >> y;
	//	PointF point(x, y);
	//	points.push_back(point);
	//}

	/*Инициализаци GDI+*/
	ULONG_PTR gdToken;
	GdiplusStartupInput gdInput;

	LSTATUS retRes = GdiplusStartup(&gdToken, &gdInput, NULL);	/*Создание главного файла и обработка ошибки */

	PointF A(1.0f, 2.0f);
	PointF B(2.0f, 4.0f);
	PointF C(4.0f, 4.5f);
	PointF D(4.0f, 2.0f);
	PointF E(3.0f, 1.0f);

	// Test
	/*A.setCoordinates(1.0,2.0);
	B.setCoordinates(2.0,4.0);
	C.setCoordinates(4.0,4.0);
	D.setCoordinates(4.0,2.0);
	E.setCoordinates(3.0,1.0);*/

	// Формула для расчета координат середины отрезка: 
	// XcenterP = (C.X() + A.X())/2
	// YcenterP = (C.Y() + A.Y())/2

	// TASK: Найти такие координаты точки P, чтобы проверить ее на check_border == 2

	/*float XcenterP = (C.X + A.X) / 2;
	float YcenterP = (C.Y + A.Y) / 2;*/


	//vector<PointF> dots;
	//dots.push_back(A);
	//dots.push_back(B);
	//dots.push_back(C);
	//dots.push_back(D);
	//dots.push_back(E);

	points.push_back(A);
	points.push_back(B);
	points.push_back(C);
	points.push_back(D);
	points.push_back(E);

	float XcenterP = (points[2].X + points[0].X) / 2;
	float YcenterP = (points[2].Y + points[0].Y) / 2;


	PointF P(XcenterP, YcenterP); //проверяемая точка ();

	Method method = Method();
	cout << "-------------Check by Polygon baricentric method----------------------- \n";
	//string result = method.Polygon_method(dots, P);
	string result = method.Polygon_method(points, P);
	cout << result;
	// cout << "-------------Check by triangle method----------------------- \n";
	// string result = Triangle_method(A, B, C, P);
	// cout << "\n";
	// cout << result;

	// cout << "---------------Check by baricentric method---------------------\n";
	// string BarResult = Baricenter_method(A, B, C, P);
	// cout << BarResult;

	GdiplusShutdown(gdToken);
	return 0;
}