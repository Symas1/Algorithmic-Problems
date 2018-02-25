// the gasup problem
#include <vector>
#include <iostream>
#include <assert.h>
#include <random>
using namespace std;

size_t ample_city(const vector<int>&distances, const vector<int>&gallons) {
	struct City_and_remaining_gas {
		int city = 0, gas = 0;
	}c;
	int remaining_gallons = 0;
	for (int i = 1; i < gallons.size(); ++i) {
		remaining_gallons += gallons[i - 1] - distances[i - 1] / 20;
		if (remaining_gallons < c.gas) {
			c.city=i;
			c.gas = remaining_gallons;
		}
	}
	return c.city;
} // time O(n); space O(1)

void check_answer(const vector<int>&distances, const vector<int>&gallons, size_t start) {
	int remaining_gallons = 0;
	size_t cc = start;
	do {
		remaining_gallons += gallons[cc] - distances[cc] / 20;
		assert(remaining_gallons >= 0);
		cc = (cc + 1) % distances.size();
	} while (cc != start);
}

void small_test() {
	vector<int>distances{ 10,20,15,40 };
	vector<int>gallons{ 20,20,30,15 };
	auto res = ample_city(distances, gallons);
	assert(res == 0);
	check_answer(distances, gallons, res);
}

void main() {
	small_test();
	mt19937 mt{ random_device{}() };
	for (int i = 0; i < 1000; ++i) {
		int size = uniform_int_distribution<>{ 1,1000 }(mt);
		vector<int>gallons, distances;
		int sum = 0;
		for (int i = 0; i < size; ++i) {
			int gal = uniform_int_distribution<>{ 1,200 }(mt);
			gallons.emplace_back(gal);
			sum += gal;
		}
		sum -= size;
		for (int i = 0; i < size; ++i) {
			int dist = 0;
			if (sum) {
				dist = uniform_int_distribution<>{ 1,sum }(mt);
			}
			distances.emplace_back(dist + 1);
			sum -= dist;
		}
		distances.back() += sum;

		auto res = ample_city(distances, gallons);
		check_answer(distances, gallons, res);
	}
	system("pause");
}