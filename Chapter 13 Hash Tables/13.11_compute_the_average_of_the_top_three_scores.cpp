// compute the average of the top three scores
#include <unordered_map>
#include <queue>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <assert.h>
#include <vector>
#include <sstream>
#include <random>

#include <functional>
using namespace std;

string best_av(ifstream& ist)
{
	unordered_map<string, priority_queue<int, vector<int>, greater<int>>>students{};
	string str{};
	string best_student{};
	double best_average{ -1 };
	while (getline(ist, str))
	{
		istringstream stream{ str };
		string student;
		int test;
		stream >> student >> test;
		students[student].emplace(test);
		if (students[student].size() > 3)students[student].pop();
	}
	for (auto& x : students)
	{
		if (x.second.size() == 3)
		{
			double avg{};
			while (!x.second.empty())
			{
				avg += x.second.top();
				x.second.pop();
			}
			avg /= 3;
			if (avg > best_average)
			{
				best_average = avg;
				best_student = x.first;
			}
		}
	}
	return best_student;
} // time O(n), space O(m) m - distinct students

string brute(ifstream& ist)
{
	unordered_map<string, vector<int>>students{};
	string str{};
	while (getline(ist, str))
	{
		istringstream stream{ str };
		string student;
		int test;
		stream >> student >> test;
		students[student].emplace_back(test);
	}
	string best_student{};
	double best_average{ -1 };
	for (auto& x : students)
	{
		if (x.second.size() >= 3)
		{
			sort(x.second.begin(), x.second.end());
			auto s = x.second.size();
			double avg = x.second[s - 1] + x.second[s - 2] + x.second[s - 3];
			avg /= 3;
			if (avg > best_average)
			{
				best_average = avg;
				best_student = x.first;
			}
		}
	}
	return best_student;
} // time O(nlogn); space O(n)

string rand_name(int size)
{
	mt19937 mt{ random_device{}() };
	string res(size, {});
	for (int i = 0; i < size; ++i)
	{
		res[i] = uniform_int_distribution<int>{ 'a','c' }(mt);
	}
	return res;
}

void main()
{
	mt19937 mt{ random_device{}() };
	for (int times = 0; times < 10; ++times)
	{
		ofstream of("st.txt");
		int lines = uniform_int_distribution<int>{ 1000,10000 }(mt);
		for (int i = 0; i < lines; ++i)
		{
			int test = uniform_int_distribution<int>{ 0,100 }(mt);
			of << rand_name(3) << " " << test << " \n";
		}
		of.close();
		ifstream ist("st.txt");
		auto res1 = best_av(ist);
		ist.clear();
		ist.seekg(0, ios::beg);
		auto res2 = brute(ist);
		assert(res1 == res2);
		ist.close();
		remove("st.txt");
	}
	system("pause");
}