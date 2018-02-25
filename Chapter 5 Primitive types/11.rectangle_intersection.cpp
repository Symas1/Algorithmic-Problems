#include <iostream>
#include <algorithm>
#include <random>
#include <assert.h>
using namespace std;

class Rectangle {
public:
	Rectangle(int x, int y, int width, int height) : x_{ x }, y_{ y }, width_{ width }, height_{ height } {};
	int x_;
	int y_;
	int width_;
	int height_;
};

bool is_intersect(const Rectangle& a, const Rectangle& b)
{
	return (a.x_ <= b.x_ + b.width_) && (a.x_ + a.width_ >= b.x_) &&
		(a.y_ <= b.y_ + b.height_) && (a.y_ + a.height_ >= b.y_);
}

Rectangle intersection(const Rectangle& one, const Rectangle& two)
{
	if (!is_intersect(one, two))
	{
		return Rectangle{ 0,0,-1,-1 };
	}
	return Rectangle{ max(one.x_,two.x_),max(one.y_,two.y_),
	min(one.x_ + one.width_,two.x_ + two.width_) - max(one.x_,two.x_),
		min(one.y_ + one.height_,two.y_ + two.height_) - max(one.y_,two.y_) };
} // O(1)

void test()
{
	Rectangle first{ 0,0 , 4, 3 };
	Rectangle second{ 0,4,3,2 };
	Rectangle third{ 3,2,1,2 };
	auto a = intersection(third, first);
	auto b = intersection(second, first);
	assert(a.height_ == 1 && a.width_ == 1 && a.x_ == 3 && a.y_ == 2);
	assert(b.height_ == -1 && b.width_ == -1 && b.x_ == 0 && b.y_ == 0);
}

void main()
{
	test();
	mt19937 mt((random_device())());
	uniform_int_distribution<int> dist{ 1,100 };
	for (int i = 0; i < 10000; ++i)
	{
		auto x1 = dist(mt);
		auto y1 = dist(mt);
		auto width1 = dist(mt);
		auto height1 = dist(mt);
		auto x2 = dist(mt);
		auto y2 = dist(mt);
		auto width2 = dist(mt);
		auto height2 = dist(mt);
		Rectangle test1{ x1,y1,width1,height1 };
		Rectangle test2{ x2,y2,width2,height2 };
		bool is_inter=is_intersect(test1,test2);
		Rectangle result = intersection(test1, test2);
		assert(is_inter == false || (result.height_ >= 0 && result.width_ >= 0));
	}
	system("pause");
}


