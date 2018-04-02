// cover the 3xn board with tiles 1x2 and 2x1
#include <vector>
#include <iostream>
#include <assert.h>
#include <algorithm>
using namespace std;

unsigned cover_angle(unsigned n);
unsigned cover(unsigned n) {
	if (n % 2) {
		return 0;
	}
	else if (n==0) {
		return 1;
	}
	return cover(n-2) + 2*cover_angle(n-1);
} // time O(exponentional); space O(n) - for recursion
unsigned cover_angle(unsigned n) {
	if (n == 1) {
		return 1;
	}
	else if (n == 2) {
		return 3;
	}
	return cover(n - 1) + cover_angle(n - 2);
}

void cover_mem_helper(vector<unsigned>&hist,unsigned n);
void cover_mem_helper_angle(vector<unsigned>&hist, unsigned n);
unsigned cover_mem(unsigned n) {
	if (n % 2) {
		return 0;
	}
	else if (n == 0) {
		return 1;
	}
	vector<unsigned>hist(n+1, 0);
	hist[0] = 1;
	hist[1] = 1;
	hist[2] = 3;
	cover_mem_helper(hist, n);
	return hist.back();
} // time O(n^2) as to fill array of size n we need O(n)time  ;space O(n) recursion n  + array n
void cover_mem_helper(vector<unsigned>&hist, unsigned n) {
	if (hist[n] != 0 || n%2 || n==0 || n==2) {
		return;
	}
	cover_mem_helper(hist,n - 2);
	cover_mem_helper_angle(hist,n - 1);
	hist[n] = hist[n - 2] + 2 * hist[n - 1];
}
void cover_mem_helper_angle(vector<unsigned>&hist, unsigned n) {
	if (n == 1 || n==2) {
		return;
	}
	cover_mem_helper(hist, n - 1);
	cover_mem_helper_angle(hist,n - 2);
	hist[n] = hist[n - 1] + hist[n - 2];
}

unsigned long long cover_dp(unsigned n) {
	if (n % 2) {
		return 0;
	}
	if (n == 0) {
		return 1;
	}
	if (n == 1) {
		return 0;
	}
	if (n == 2) {
		return 3;
	}
	unsigned long long n_2 = 1;
	unsigned long long n_1 = 3;
	for (int i = 3; i <= n; ++i) {
		unsigned long long n;
		if (i % 2) {
			n = n_2 + n_1;
		}
		else {
			n = 2 * n_1 + n_2;
		}
		n_2 = n_1;
		n_1 = n;
	}
	return n_1;
} // time O(n); space O(1)

long double cover_const(unsigned n) {
	long double mult13 = (sqrt(3) + 3) / 12;
	long double mult24 = (-sqrt(3) + 3) / 12;
	long double first = mult13*pow(sqrt(2 + sqrt(3)), n);
	long double second = mult24*pow(sqrt(2 - sqrt(3)), n);
	long double third = mult13*pow(-sqrt(2 + sqrt(3)), n);
	long double fourth = mult24*pow(-sqrt(2 - sqrt(3)), n);
	return first + second + third + fourth;
}

void golden_test();

void main() {
	golden_test();
	for (int i = 0; i <= 32; ++i) {
		// don't make i too big because of overflow
		//auto res1 = cover(i);
		auto res2 = cover_mem(i);
		auto res3 = cover_dp(i);
		//assert(res1 == res2);
		assert(res2 == res3);
	}
	system("pause");
}

void golden_test() {
	vector<unsigned>answers{ 3,0,11,0,41,0,153,0,2131,299303201 };
	vector<unsigned>numbers{ 2,3,4,5,6,7,8,9,12,30 };
	for (int i = 0; i < numbers.size(); ++i) {
		auto res1 = cover(numbers[i]);
		auto res2 = cover_mem(numbers[i]);
		auto res3 = cover_dp(numbers[i]);
		assert(res1 == res2 && res1 == answers[i] && res2 == answers[i]);
		assert(res2 == res3 && res3 == answers[i]);
	}
}