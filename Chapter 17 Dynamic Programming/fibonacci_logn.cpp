// fibonacci in logn
#include <array>
#include<iostream>
#include <assert.h>
using namespace std;
using matrix = array<array<unsigned, 2>, 2>;

matrix exponentiate_matrix(unsigned power);
matrix multiply_matrices(const matrix& first, const matrix& second);
unsigned fibonacci_logn(unsigned i) {
	if (i == 0) {
		return 0;
	}
	else if (i == 1 || i == 2) {
		return 1;
	}
	return exponentiate_matrix(i - 1)[0][0];
} // time O(logn); space O(1)
matrix exponentiate_matrix(unsigned power) {
	matrix result{ {{1,0},{0,1}} };
	matrix help{ {{1,1},{1,0}} };
	while (power) {
		if (power & 1) {
			result = multiply_matrices(result, help);
		}
		help = multiply_matrices(help, help);
		power >>= 1;
	}
	return result;
}
matrix multiply_matrices(const matrix& first, const matrix& second) {
	matrix result;
	result[0][0] = first[0][0] * second[0][0] + first[0][1] * second[1][0];
	result[0][1] = first[0][0] * second[0][1] + first[0][1] * second[1][1];
	result[1][0] = first[1][0] * second[0][0] + first[1][1] * second[1][0];
	result[1][1] = first[1][0] * second[0][1] + first[1][1] * second[1][1];
	return result;
}

unsigned fibonacci_linear(unsigned i) {
	if (i == 0) {
		return 0;
	}
	else if (i == 1 || i == 2) {
		return 1;
	}
	unsigned f_minus1 = 1;
	unsigned f_minus2 = 1;
	for (int k = 3; k <= i; ++k) {
		unsigned number = f_minus1 + f_minus2;
		f_minus2 = f_minus1;
		f_minus1 = number;
	}
	return f_minus1;
} // time O(n); space O(1)

double fibonacci_const(unsigned i) {
	return 1 /sqrt(5)*pow((1 + sqrt(5)) / 2, i) - (1 / (sqrt(5))*pow((1 - sqrt(5)) / 2, i));
} // time O(1); space O(1)

void main() {
	for (int i = 0; i < 10000; ++i) {
		cout << i << endl;
		auto res_logn = fibonacci_logn(i);
		auto res_lin = fibonacci_linear(i);
		auto res_const = fibonacci_const(i);
		assert(res_logn == res_lin);
		//assert(res_lin == round(res_const));
	}
	system("pause");
}