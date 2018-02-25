// find if rectangles not aligned with the X and Y axes intersect
#include <vector>
#include <utility>
#include <numeric>
#include <iostream>
#include <assert.h>
#include <algorithm>
using namespace std;

struct Point {
	Point(double x_, double y_) :x{ x_ }, y{ y_ } {};
	double x, y;
};

struct Rectangle {
	Rectangle(Point a_, Point b_, Point c_, Point d_) : a{ a_ }, b{ b_ }, c{ c_ }, d{ d_ } {};
	Point a, b, c, d;
};

Point perpendicular(const Point& a)
{
	return Point{ a.y,-a.x };
}

pair<double, double> interval(const Point& perp, const vector<Point>& edges)
{
	double min = numeric_limits<double>::max();
	double max = numeric_limits<double>::lowest();
	for (auto& ed : edges)
	{
		double scal = ed.x*perp.x + ed.y*perp.y;
		if (scal < min)min = scal;
		if (scal > max)max = scal;
	}
	return make_pair(min, max);
}

int intervals_intersect(const pair<double, double>& a, const pair<double, double>& b)
{
	return a.first <= b.second && a.second >= b.first;
}

void normalize(Point& axis)
{
	double length = sqrt(pow(axis.x, 2) + pow(axis.y, 2));
	axis.x /= length;
	axis.y /= length;
}

bool intersect_helper(const vector<Point>& first, const vector<Point>& second)
{
	for (int i = 0; i < first.size(); ++i)
	{
		Point perp = perpendicular(first[i]);
		normalize(perp);
		auto interval_a = interval(perp, first);
		auto interval_b = interval(perp, second);
		if (!intervals_intersect(interval_a, interval_b))return false;
	}
	return true;
}

bool intersect(const Rectangle& a, const Rectangle& b)
{
	vector<Point>edges_a{};
	vector<Point>edges_b{};

	edges_a.insert(edges_a.end(), { a.a,a.b,a.c,a.d });
	edges_b.insert(edges_b.end(), { b.a,b.b,b.c,b.d });

	return intersect_helper(edges_a, edges_b) && intersect_helper(edges_b, edges_a);
}

void main()
{
	Rectangle first{ Point{0,1},Point{ 1,2 }, Point{ 2,1 }, Point{ 1,0 } };
	Rectangle second{ Point{ 1,1 },Point{ 2,2 }, Point{ 3,1 }, Point{ 2,0 } };
	Rectangle third{ Point{ 0,4 },Point{ 1,5 }, Point{ 2,4 }, Point{ 1,3 } };
	assert(intersect(first, second) == true);
	assert(intersect(second, third) == false);
	assert(intersect(first, third) == false);
	system("pause");
}