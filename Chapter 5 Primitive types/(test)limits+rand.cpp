#include <limits>
#include <random>
#include <iostream>
#include <functional>

void main()
{

	auto a =  std::numeric_limits<int>::max();
	std::cout << a << std::endl;

	std::mt19937 mt{ std::random_device{}() };
	std::uniform_int_distribution<int> dist{ 1, 10 };
	for (int i = 0; i<16; ++i)
		std::cout << dist(mt) << " ";
	std::cout << std::endl;
	system("pause");
}