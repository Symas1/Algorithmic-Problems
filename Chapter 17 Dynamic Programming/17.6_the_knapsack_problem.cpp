// the knapsack problem
#include <vector>
#include <iostream>
#include <assert.h>
#include <algorithm>
#include <list>
#include <unordered_map>
#include <functional>
#include <iterator>
using namespace std;

int knapsack(const vector<int>& values, const vector<int>&weights, const int w) {
	vector<int>arr(w + 1, 0);
	for (int i = 0; i < values.size(); ++i) {
		for (int j = w; j >= weights[i]; --j) {
			arr[j] = max(arr[j], values[i] + arr[j - weights[i]]);
		}
	}
	return arr.back();
} // time O(n*w) n - number of objects, w - max weight; space O(w)

int knapsack2(const vector<int>&values, const vector<int>&weights, const int w) {
	list<pair<int, int>>used_weights{ {0,0} }; // weight and value
	unordered_map<int, list<pair<int, int>>::iterator>previous_weights{ {0,used_weights.begin()} };
	int result = 0;
	for (int i = 0; i < values.size(); ++i) {
		for (auto j = used_weights.rbegin(); j!=used_weights.rend(); ++j) {
			if (!previous_weights.count(weights[i])) {
				for (auto k = used_weights.begin(); ; ++k) {
					if (k!=used_weights.end()&&k->first < weights[i]) {
						continue;
					}
					else {
						auto iter = used_weights.emplace(k, weights[i], values[i]);
						previous_weights.emplace(weights[i], iter);
						break;
					}
				}
			}

			int without_current = j->second;
			int with_current = (previous_weights.count(j->first - weights[i])) ?
				values[i] + previous_weights[j->first - weights[i]]->second:values[i];
			j->second = max(without_current, with_current);
			result = max(result, j->second);
		}
	}
	return result;
} // doesnt work

void small_test() {
	vector<int>vals{ 1,7,5,4 };
	vector<int>wei{ 1,5,4,3 };
	assert(knapsack(vals, wei, 7) == 9);
	cout << knapsack2(vals, wei, 7) << endl;
	vals = { 65,35,245,195,65,150,275,155,120,320,75,40,200,100,220,99 };
	wei = { 20,8,60,55,40,70,85,25,30,65,75,10,95,50,40,10 };
	assert(knapsack(vals, wei, 130) == 695);
}

void main() {
	small_test();
	system("pause");
}