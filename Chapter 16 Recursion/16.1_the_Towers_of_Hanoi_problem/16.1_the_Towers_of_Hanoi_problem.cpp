// the Towers of Hanoi problem
#include <iostream>
#include <stack>
#include <array>
#include <cmath>
#include <algorithm>
#include <assert.h>
using namespace std;

//static int steps = 0;
//const int pegs = 3;
//
//void hanoi_helper(int rings, array<stack<int>, pegs>& arr, int from, int to, int use);
//void hanoi(const int rings)
//{
//	array<stack<int>, pegs>arr_pegs{};
//	for (int i = rings; i >= 1; --i)
//		arr_pegs[0].emplace(i);
//	hanoi_helper(rings, arr_pegs, 0, 1, 2);
//} // time O(2^rings); space O(rings)
//void hanoi_helper(int rings, array<stack<int>, pegs>& arr, int from, int to, int use)
//{
//	if (rings > 0)
//	{
//		hanoi_helper(rings - 1, arr, from, use, to);
//
//		arr[to].emplace(arr[from].top());
//		arr[from].pop();
//
//		cout << "Move from " << from << " move to" << to << endl;
//		++steps;
//
//		hanoi_helper(rings - 1, arr, use, to, from);
//	}
//}



bool possible_move(const array<stack<unsigned>, 3>&pegs, const pair<unsigned, unsigned>&move);
void hanoi_iter(unsigned rings) {
	array<stack<unsigned>, 3>pegs;
	for (unsigned i = rings; i > 0; --i) {
		pegs[0].emplace(i);
	}
	array<pair<unsigned, unsigned>, 3>moves{ { { 0,rings & 1 ? 1 : 2 },{ 0,rings & 1 ? 2 : 1 },{ 1,2 } } };
	for (int move = 0; pegs[1].size() != rings; move = (move + 1) % 3) {
		if (possible_move(pegs, moves[move])) {
			cout << "Move from: " << moves[move].first << " -> to: " << moves[move].second << endl;
			pegs[moves[move].second].emplace(pegs[moves[move].first].top());
			pegs[moves[move].first].pop();
		}
		else {

			cout << "Move from: " << moves[move].second << " -> to: " << moves[move].first << endl;
			pegs[moves[move].first].emplace(pegs[moves[move].second].top());
			pegs[moves[move].second].pop();
		}
	}
} // time O(2^n-1); space O(disks)
bool possible_move(const array<stack<unsigned>, 3>&pegs, const pair<unsigned, unsigned>&move) {
	if (pegs[move.first].empty()) {
		return false;
	}
	if (pegs[move.second].empty() || pegs[move.first].top() < pegs[move.second].top()) {
		return true;
	}
	return false;
}


void hanoi_helper(size_t from, size_t to, size_t help, array<unsigned, 3>&pegs, unsigned depth);
void hanoi(unsigned rings) {
	if (rings == 0) {
		return;
	}

	array<unsigned, 3>pegs{ rings,0,0 };
	hanoi_helper(0, 1, 2, pegs, rings);
} // time O(2^n-1); space O(rings)
static unsigned steps = 0;
void hanoi_helper(size_t from, size_t to, size_t help, array<unsigned, 3>&pegs, unsigned depth) {
	if (depth == 0) {
		return;
	}
	hanoi_helper(from, help, to, pegs, depth - 1);
	++steps;
	cout << "Move from: " << from << " -> to: " << to << endl;
	--pegs[from];
	++pegs[to];
	hanoi_helper(help, to, from, pegs, depth - 1);
}

void main()
{
	for (int i = 0; i < 10; ++i)
	{
		/*hanoi(4);
		cout << endl << endl;
		hanoi_iter(4);*/
		//cout << "Steps: " << steps << endl;
	}
	system("pause");
}