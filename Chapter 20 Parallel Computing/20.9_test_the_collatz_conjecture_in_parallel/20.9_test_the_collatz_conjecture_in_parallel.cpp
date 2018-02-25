// 
#include <thread>
#include <iostream>
#include <functional>
#include <unordered_set>
#include <assert.h>

#include "Sync_queue.h"
using namespace std;
using ull = unsigned long long;

class Parallel_collatz {
public:
	Parallel_collatz(ull last_number, ull step) {
		fill_queue(last_number, step);
		for (int i = 0; i < thread::hardware_concurrency(); ++i) {
			threads_.emplace_back(&Parallel_collatz::test_collatz, this);
		}
		for (auto& t : threads_) {
			t.join();
		}
	}
private:
	void fill_queue(const ull last_number, const ull step) {
		ull start = 3;
		for (ull i = 0; i < (last_number - 3) / step; ++i) {
			sync_queue_.push(pair<ull, ull>{start, start - 1 + step});
			start += step;
		}
		if (start <= last_number) {
			sync_queue_.push(pair<ull, ull>{start, last_number});
		}
	}
	void test_collatz();
	void test_collatz_helper(const pair<ull, ull>&range);

	Sync_queue < pair<ull, ull>>sync_queue_;
	vector<thread>threads_;

	unordered_set<ull>global_checked_numbers_;

	mutex mx_;
	mutex cout_mutex_;
};

void Parallel_collatz::test_collatz()
{
	pair<ull, ull>range;
	while (sync_queue_.try_pop(range)) {
		{
			lock_guard<mutex>cout_lock{ cout_mutex_ };
			cout << "Testing range: " << range.first << "," << range.second << endl;
		}
		test_collatz_helper(range);
	}
}

void Parallel_collatz::test_collatz_helper(const pair<ull, ull>&range)
{
	unordered_set<ull>currently_seen_numbers;
	ull number = range.first % 2 ? range.first : range.first + 1;
	for (; number <= range.second; number += 2) {
		ull test_number = number;
		while (test_number >= number) {
			if (!currently_seen_numbers.emplace(test_number).second) {
				assert(false);
			}
			if (test_number & 1) {
				{
					lock_guard<mutex>lock{ mx_ };
					if (!global_checked_numbers_.emplace(test_number).second) {
						break;
					}
				}
				ull next_number = test_number * 3 + 1;
				if (next_number <= test_number) {
					throw overflow_error("Overflow in test_collatz_helper()");
				}
				test_number = next_number;
			}
			else {
				test_number >>= 1;
			}
		}
		currently_seen_numbers.clear();
	}
}

void main() {
	Parallel_collatz a{ 10000000,20000 };
	system("pause");
}