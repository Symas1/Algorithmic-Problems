// given foour points say if they form a rectangle
#include <cmath>
#include <assert.h>
#include <iostream>
using namespace std;
struct Point {
	Point(double x_, double y_) :x{ x_ }, y{ y_ } {};
	double x, y;
};


bool is_rectangle_first(const Point& a, const Point& b, const Point& c, const Point& d)
{
	Point mass_center{ (a.x + b.x + c.x + d.x) / 4,(a.y + b.y + c.y + d.y) / 4 };
	double a_to_center = pow(mass_center.x - a.x, 2) + pow(mass_center.y - a.y, 2);
	double b_to_center = pow(mass_center.x - b.x, 2) + pow(mass_center.y - b.y, 2);
	double c_to_center = pow(mass_center.x - c.x, 2) + pow(mass_center.y - c.y, 2);
	double d_to_center = pow(mass_center.x - d.x, 2) + pow(mass_center.y - d.y, 2);


	double diff = (a_to_center - b_to_center) / b_to_center;
	if (diff<-1.0e-9 || diff > 1.0e-9)return false;
	diff= (a_to_center - c_to_center) / c_to_center;
	if (diff<-1.0e-9 || diff > 1.0e-9)return false;
	diff = (a_to_center - d_to_center) / d_to_center;
	if (diff<-1.0e-9 || diff > 1.0e-9)return false;


	return true;
}


namespace second
{
	bool is_orthogonal(const Point& a, const Point& b, const Point& c)
	{
		return ((b.x - a.x)*(b.x - c.x) + (b.y - a.y)*(b.y - c.y)) == 0;
	}

	bool is_r(const Point& a, const Point& b, const Point& c, const Point& d)
	{
		return is_orthogonal(a, b, c) &&
			is_orthogonal(b, c, d) &&
			is_orthogonal(c, d, a);
	}

	bool is_rectangle(const Point& a, const Point& b, const Point& c, const Point& d)
	{
		return is_r(a, b, c, d) ||
			is_r(b, c, a, d) ||
			is_r(c, a, b, d);
	}
}


void main()
{
	{
		{
			Point a{ 0,0 }, b{ 0,3 }, c{ 3,0 }, d{ 3,3 };
			assert(is_rectangle_first(a, b, c, d) == true);
		}
		{
			Point a{ 0,0 }, b{ 0,3 }, c{ 4,0 }, d{ 3,3 };
			assert(is_rectangle_first(a, b, c, d) == false);
		}
	}

	{
		using namespace second;
		{
			Point a{ 0,0 }, b{ 0,3 }, c{ 3,0 }, d{ 3,3 };
			assert(is_rectangle(a, b, c, d) == true);
		}
		{
			Point a{ 0,0 }, b{ 0,3 }, c{ 4,0 }, d{ 3,3 };
			assert(is_rectangle(a, b, c, d) == false);
		}
	}

	system("pause");
}