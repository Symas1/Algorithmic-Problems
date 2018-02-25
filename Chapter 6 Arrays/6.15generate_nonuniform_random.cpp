// generate nonuniform random numbers
#include <vector>
#include <random>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <numeric>
#include <unordered_map>
#include <assert.h>
#include <string>
using namespace std;

double roll()
{
	mt19937 mt{ random_device{}() };
	return generate_canonical<double,numeric_limits<double>::digits>(mt);
}

int number(const vector<int>& numbers,const vector<double>&probs)
{
	vector<double>part{};
	part.emplace_back(0);
	partial_sum(probs.begin(), probs.end(), back_inserter(part));

	auto p = roll();

	int index = distance(part.cbegin(), upper_bound(part.cbegin(), part.cend(), p))-1;

	return numbers[index];
} // O(n), O(n)

double variant(double lambda)
{
	auto u = roll();
	return -(log(1 - u) / lambda);
}

void number_test();
void exponential_test();

void main()
{
	number_test();

	exponential_test();

	system("pause");
}

void number_test()
{
	mt19937 mt{ random_device{}() };

	uniform_int_distribution<int> random_size{ 1,50 };
	const size_t n = random_size(mt);

	vector<int>numbers(n);
	iota(numbers.begin(), numbers.end(), 0);

	vector<double>probs{};
	double current_prob = 1.0;
	for (size_t i = 0; i < n; ++i)
	{
		uniform_real_distribution<double> random_prob{ 0,current_prob };
		auto new_prob = random_prob(mt);
		current_prob -= new_prob;
		probs.emplace_back(new_prob);
	}
	shuffle(probs.begin(), probs.end(), mt);

	vector<int>count(n, 0);

	const int times = 100000;
	for (int i = 0; i < times; ++i)
	{
		auto num = number(numbers, probs);
		++count[num];
	}

	for (int i = 0; i < n; ++i)
	{
		assert(fabs(static_cast<double>(count[i]) / times - probs[i]) < 0.01);
	}
}

void exponential_test()
{
	const int intervals = 20;
	const int nstars = 100;
	vector<int>interv(intervals);

	const int tests = 100000;
	for (int i = 0; i < tests; ++i)
	{
		auto num = variant(3.5);
		if (num < 1.0)++interv[static_cast<int>(num*intervals)];
	}

	std::cout << "exponential_distribution (3.5):" << std::endl;
	std::cout << std::fixed; std::cout.precision(2);

	for (int i = 0; i<intervals; ++i) {
		std::cout << float(i) / intervals << "-" << float(i + 1) / intervals << ": ";
		std::cout << std::string(interv[i] * nstars / tests, '*') << std::endl;
	}

}
