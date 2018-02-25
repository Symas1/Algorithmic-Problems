#include <iostream>
#include <chrono>
using namespace std;

#include "Thread_pool.h"

void func() {
	cout << "123456789\n";
}

void main() {
	Thread_pool thread_pool;
	for (int i = 0; i < 100; ++i) {
		thread_pool.submit(func);
	}
	system("pause");
}